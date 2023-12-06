/*
Author : Yoganand Kanhed
reference : https://en.cppreference.com/w/cpp/memory/unique_ptr

T * f = uptr.get() -> returns underlying object
T * f = uptr.release();  -> returns the managed object ptr and becomes nullptr iself.
void uptr.reset(T*) ; ->  p2 ptr is deleted and set with T*.
uptr->method();
*uptr.method();
*/

#include <iostream>
#include <memory>

template <class T>
class UniquePtr
{
private:
    T *_ptr = nullptr;

public:
    UniquePtr() : _ptr(nullptr) {}                      // default constructor
    explicit UniquePtr(T *ptr = nullptr) : _ptr(ptr) {} // paremeterised constructor
    ~UniquePtr()
    {
        std::cout << "Destructor called" << std::endl;
        reset();
    }                                                                   // destructor
    UniquePtr(const UniquePtr &right) = delete;                         // copy constructor to be deleted to maintain exclusive owenship and avoid double delete
    UniquePtr &operator=(const UniquePtr &right) = delete;              // copy assign constructor
    UniquePtr(UniquePtr<T> &&right) noexcept : _ptr(right.release()) {} // move constructor
    UniquePtr<T> &operator=(UniquePtr<T> &&right) noexcept              // move assign constructor
    {
        reset(right.release());
        return *this;
    }
    T *get() const { return _ptr; }
    T *operator->() const { return get(); }
    T &operator*() const { return *get(); }
    void swap(UniquePtr<T> &right) { std::swap(this->_ptr, right._ptr); }

    T *release()
    {
        T *newPtr = _ptr;
        _ptr = nullptr;
        return newPtr;
    }

    void reset(T *newPtr = nullptr)
    {
        auto oldPtr = release();
        _ptr = newPtr;
        if (oldPtr != nullptr)
            delete oldPtr;
    }
};

class sampleBase
{
private:
    int _x;

public:
    sampleBase() noexcept {};
    explicit sampleBase(int x) noexcept : _x(x) {}
    int getX() const noexcept
    {
        return _x;
    }
    void setX(int x) noexcept
    {
        _x = x;
    }
};

int main()
{
    // UniquePtr<int> ptr1(new int(10));
    // UniquePtr<int> ptr(std::move(ptr1));

    sampleBase *obj = new sampleBase(10);
    UniquePtr<sampleBase> ptr(obj);

    // ptr.~UniquePtr();
    // if (ptr.get() == nullptr)
    // {
    //     std::cout << "Underlying object is delete" << std::endl;
    // }

    // UniquePtr<sampleBase> ptr1(ptr);
    // if (ptr1.get() == nullptr)
    // {
    //     std::cout << "Underlying object is delete" << std::endl;
    // }

    // std::cout << ptr->getX() << std::endl;
    UniquePtr<sampleBase> ptr1 = std::move(ptr);
    // std::cout << ptr->getX() << std::endl;
    // std::cout << ptr1->getX() << std::endl;

    sampleBase *resource = ptr1.release();
    std::cout << resource->getX() << std::endl;
    // std::cout << ptr1->getX() << std::endl;
    ptr1.reset(resource);
    std::cout << resource->getX() << std::endl;
    std::cout << (*ptr1).getX() << std::endl;

    return 0;
}