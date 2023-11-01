/*
Author : Yoganand Kanhed
Description : Observer Design Pattern ( Behavioral Pattern)
The Observer pattern is a behavioral design pattern where an object, known as the subject,
maintains a list of its dependents, called observers, and notifies them of any state changes,
typically by calling one of their methods.
This pattern is often used to implement distributed event handling systems.
Read more here : https://www.codeproject.com/Articles/47948/The-Observer-Design-Pattern
*/
// This example demonstrates the Observer pattern where the observers
//(observer1 and observer2) are notified when the subject's data changes.

#include <iostream>
#include <vector>
#include <bits/stdc++.h>

// Observer abstract base class
class Observer
{
public:
    virtual void update(int data) = 0;
};

class ConcreteObserver : public Observer
{
public:
    void update(int data) override
    {
        std::cout << "Received update with data: " << data << std::endl;
    }
};

class Subject
{
private:
    int data;
    std::vector<Observer *> observers;

public:
    void addObserver(Observer *observer)
    {
        observers.push_back(observer);
    }

    void removeObserver(Observer *observer)
    {
        // Find and remove the observer from the vector
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end())
        {
            observers.erase(it);
            std::cout << "Observed removed" << std::endl;
        }
    }

    void setData(int newData)
    {
        data = newData;
        notifyObservers();
    }

    void notifyObservers()
    {
        for (Observer *observer : observers)
        {
            observer->update(data);
        }
    }
};

int main()
{
    Subject subject;
    ConcreteObserver observer1;
    ConcreteObserver observer2;
    ConcreteObserver observer3;

    // Add observers to the subject
    subject.addObserver(&observer1);
    subject.addObserver(&observer2);
    subject.addObserver(&observer3);

    // Set new data in the subject, observers will be notified
    subject.setData(10);

    subject.removeObserver(&observer3);
    subject.setData(12);

    return 0;
}
