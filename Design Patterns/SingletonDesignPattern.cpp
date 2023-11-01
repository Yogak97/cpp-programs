/*
Author : Yoganand Kanhed
Description : Singleton Design Pattern (Creational Design Pattern -> Best ways to Create Objects)
Ensures that a class has only one instance and provides a global point of access to it.
It's often used for logging, driver objects, caching, thread pools, and database connections.
Read more here : https://www.codeproject.com/Articles/1921/Singleton-Pattern-its-implementation-with-C
*/

#include <iostream>

class Singleton
{
private:
    // Private constructor to prevent instantiation from outside the class.
    Singleton() {}

    // Private static instance of the class.
    static Singleton *instance;

public:
    // Public method to access the singleton instance.
    static Singleton *getInstance()
    {
        // If the instance doesn't exist, create one.
        if (instance == nullptr)
        {
            instance = new Singleton();
        }
        return instance;
    }

    // Example method of the Singleton class.
    void showMessage()
    {
        std::cout << "Hello, I am a Singleton!" << std::endl;
    }
};

// Initializing the static instance to nullptr.
Singleton *Singleton::instance = nullptr;

int main()
{
    // Get the Singleton instance.
    Singleton *singletonInstance1 = Singleton::getInstance();
    singletonInstance1->showMessage(); // Output: Hello, I am a Singleton!

    // Attempt to create another instance (it will return the existing instance).
    Singleton *singletonInstance2 = Singleton::getInstance();

    // Check if both instances point to the same memory address.
    if (singletonInstance1 == singletonInstance2)
    {
        std::cout << "Both instances are the same. Singleton pattern is working." << std::endl;
    }
    else
    {
        std::cout << "Error: Singleton pattern is violated." << std::endl;
    }

    // Note: It's important to delete the instance when it's no longer needed.
    // However, in a real-world scenario, you might use smart pointers or other memory management techniques.
    delete singletonInstance1;

    return 0;
}
