/*
Author : ykanhed
Desc : Asynchronous Server program
1. Tcp/Ip Server which accept new connection asynchronously
2. Read message from clients asynchronously and upd multicast to member clients.
*/

#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <vector>
#include <string.h>
#include <mutex>
#define cBUFFER_SIZE 1024
#if BOOST_VERSION >= 107000
#define GET_IO_SERVICE(s) ((boost::asio::io_context &)(s).get_executor().context())
#else
#define GET_IO_SERVICE(s) ((s).get_io_service())
#endif

using boost::asio::ip::tcp;
using boost::asio::ip::udp;

const std::string MULTICAST_ADDR = "225.0.0.37";
const unsigned short MUTICAST_UDP_PORT = 5678;
#define cBUFFER_SIZE 1024

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket) : TCP_SOCKET(std::move(socket))
    {
    }

    void start()
    {
        asyncWriteToClient();
        // asyncReadFromClient();
    }

private:
    void asyncReadFromClient()
    {
        // std::cout << "Reading data" << std::endl;
        auto self(shared_from_this());
        TCP_SOCKET.async_read_some(boost::asio::buffer(cBUFFER, cBUFFER_SIZE),
                                   [this, self](boost::system::error_code ec, std::size_t length)
                                   {
                                       if (!ec)
                                       {
                                           sendUdpMulticastMsg(std::string(cBUFFER));
                                           asyncWriteToClient();
                                           std::cout << "Msg from client :" << cBUFFER << std::endl;
                                           memset(cBUFFER, 0, length);
                                       }
                                   });
    }

    void asyncWriteToClient(/*std::size_t length*/)
    {
        auto self(shared_from_this());
        boost::asio::async_write(TCP_SOCKET, boost::asio::buffer("ACK", 3),
                                 [this, self](boost::system::error_code ec, std::size_t /*length*/)
                                 {
                                     if (!ec)
                                     {
                                         asyncReadFromClient();
                                     }
                                 });
    }

    void sendUdpMulticastMsg(const std::string &message)
    {
        udp::socket UDP_SOCKET(GET_IO_SERVICE(TCP_SOCKET), udp::v4());
        UDP_SOCKET.set_option(boost::asio::ip::udp::socket::reuse_address(true));
        UDP_SOCKET.set_option(boost::asio::ip::multicast::join_group(boost::asio::ip::address::from_string(MULTICAST_ADDR)));
        UDP_SOCKET.send_to(boost::asio::buffer(message), udp::endpoint(boost::asio::ip::address::from_string(MULTICAST_ADDR), MUTICAST_UDP_PORT));
    }

    tcp::socket TCP_SOCKET;
    char cBUFFER[cBUFFER_SIZE];
};

class Server
{
public:
    Server(boost::asio::io_service &io_service, short port) : io_service_(io_service), acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
    {
        asyncAcceptConn();
    }

private:
    void asyncAcceptConn()
    {
        acceptor_.async_accept(
            [this](boost::system::error_code ec, tcp::socket socket)
            {
                if (!ec)
                {
                    auto session = std::make_shared<Session>(std::move(socket));
                    session->start();
                }
                asyncAcceptConn();
            });
    }

    boost::asio::io_service &io_service_;
    tcp::acceptor acceptor_;
};

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Please Provide TCP Port as 1st Argument. Usage command <port>\n";
            return 1;
        }

        boost::asio::io_service io_service;
        Server server(io_service, std::atoi(argv[1]));

        std::vector<std::thread> threads;
        std::mutex mutex;
        for (int i = 0; i < std::thread::hardware_concurrency() / 2; ++i)
        {
            threads.emplace_back([&io_service, &mutex]()
                                 {
                std::unique_lock<std::mutex> lock(mutex);
                std::cout << "Thread with Id " << std::this_thread::get_id() << " started.\n";
                lock.unlock();
                io_service.run(); });
        }

        for (auto &thread : threads)
        {
            thread.join();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
