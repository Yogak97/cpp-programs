/*
Author : Yoganand Kanhed
Problem statement :
Write a program which takes 3 inputs (command line)

1. a string
2. char count (integer)
3. thread count - no of Threads (integer)


Each thread then should start printing the chars in the string
sequentially in the following format:
eg:
> LockFreeThreading ABCDEFGHIJ 3 4

outPut:
Using 4 threads to print ABCDEFGHIJ alternatively in set of 3 chars
Thread1 : ABC
Thread2 : DEF
Thread3 : GHI
Thread4 : JAB
THread1 : CDE
Thread2 : FGH
Thread3 : IJA
*/

#include <iostream>
#include <charconv>
#include <cstring>
#include <vector>
#include <thread>
#include <atomic>
#include <functional>

std::atomic<uint32_t> threadTurn = 0;
std::size_t currIndex = 0;

void printChars(const std::string &stringInput, std::size_t charCount, uint32_t myTurn, uint32_t threadCount)
{
    while (true)
    {
        while (threadTurn.load(std::memory_order_acquire) != myTurn)
        {
        }

        std::cout << "Thread" << myTurn + 1 << ":";
        auto index = currIndex;
        for (std::size_t i = 0; i < charCount; i++)
        {
            std::cout << stringInput[index++];
            index = (index == stringInput.length()) ? 0 : index;
        }

        std::cout << std::endl;
        currIndex = index;

        uint32_t nextTurn = myTurn + 1;
        nextTurn = (nextTurn == threadCount) ? 0 : nextTurn;
        threadTurn.store(nextTurn, std::memory_order_release);
    }
}

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        std::cerr << "Command Usage: program string charCount threadCount" << std::endl;
        exit(1);
    }

    std::string stringInput(argv[1]);
    std::size_t charCount = 0;

    // C++17 Feature
    if (auto [ptr, ec] = std::from_chars(argv[2], argv[2] + std::strlen(argv[2]), charCount, 10); ec != std::errc())
    {
        std::cerr << "Unable to parse the char to integer. Error:" << std::make_error_code(ec).message() << std::endl;
        exit(1);
    }

    uint32_t threadCount = 0;
    if (auto [ptr, ec] = std::from_chars(argv[3], argv[3] + std::strlen(argv[3]), threadCount, 10); ec != std::errc())
    {
        std::cerr << "Unable to parse the char to integer. Error:" << std::make_error_code(ec).message() << std::endl;
        exit(1);
    }

    if (threadCount < 1)
    {
        std::cerr << "Thread count should be greater than 0. " << std::endl;
        exit(1);
    }

    std::vector<std::thread> threads;
    for (size_t i = 0; i < threadCount; i++)
    {
        // threads.emplace_back(
        //     [myTurn = i, charCount = charCount, threadCount = threadCount, &stringInput]()
        //     {
        //         printChars(stringInput, charCount, myTurn, threadCount);
        //     });
        // emplace_back constructs the object here inplace and provides the arguments passed it to the constructor of std::thread
        threads.emplace_back(
            &printChars, stringInput, charCount, i, threadCount);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100000));
    for (auto &thread : threads)
    {
        thread.join();
    }

    return 0;
}