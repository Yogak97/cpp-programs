/*
Author : Yoganand Kanhed
Description : Factory Design Pattern ( Creational Design Pattern)

It also known as virtual constructor.A Factory Pattern or Factory Method Pattern says that just define
an interface or abstract class for creating an object but let the subclasses decide which class to instantiate.
In other words, subclasses are responsible to create the instance of the class.

*/

#include <iostream>

class Factory;
class Vehicle
{
protected:
    int price;
    std::string label;

public:
    virtual void setLableAndPx() = 0;
    virtual void assembleParts() = 0;
    virtual void showVehicle() = 0;
};

class Car : public Vehicle
{
private:
    Car() {}
    friend class Factory;

public:
    void setLableAndPx() override
    {
        label = "Car";
        price = 10;
    }

    void assembleParts() override
    {
        std::cout << "Car is assembled" << std::endl;
    }

    void showVehicle() override
    {
        std::cout << "Label :" << label << " Px:" << price << std::endl;
    }
};

class Bike : public Vehicle
{
private:
    Bike() {}
    friend class Factory;

public:
    void setLableAndPx() override
    {
        label = "Bike";
        price = 5;
    }

    void assembleParts() override
    {
        std::cout << "Bike is assembled" << std::endl;
    }
    void showVehicle() override
    {
        std::cout << "Label:" << label << "      Px:" << price << std::endl;
    }
};

class Factory
{

public:
    // this is only interface by which clients can now create the vehicle of various types.
    static Vehicle *createVehicle(std::string vehicleType)
    {
        Vehicle *vehicle = nullptr;

        if (vehicleType == "car")
            vehicle = new Car();
        else if (vehicleType == "bike")
            vehicle = new Bike();
        else
        {
            return vehicle; // nullptr
        }

        vehicle->assembleParts();
        vehicle->setLableAndPx();

        return vehicle;
    }
};

int main()
{
    // client code goes down here.
    // Here client don't really need to bother about the code change if new vehicle is added in the factory.

    Vehicle *vehicle = Factory::createVehicle("bike");
    if (vehicle != nullptr)
        vehicle->showVehicle();
    else
        std::cout << "Vehicle was NOT created successfully, wrong vehicle type!" << std::endl;

    delete vehicle;

    return 0;
}