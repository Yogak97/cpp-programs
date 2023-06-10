// Author:Yoganand Kanhed

#include <iostream>
#include <cstring>
using namespace std;

class String
{
private:
    char *res;
    unsigned int len;

public:
    String()
    {
        res = nullptr;
        len = 0;
    }

    String(const char *s)
    {
        len = strlen(s);
        res = new char[len + 1];
        strcpy(res, s);
        cout << "String is constructed" << endl;
    }

    String(const String &s) // copy constructor
    {
        res = new char[s.len + 1];
        strcpy(res, s.res);
        cout << "Copy constructor called" << endl;
    }

    String(String &&s) // Move constructor
    {
        len = s.len;
        res = s.res;
        s.res = nullptr;
        cout << "Move constructor called" << endl;
    }

    String &operator=(const String &s)
    {
        if (this != &s)
        {
            delete[] res;
            len = s.len;
            res = new char[s.len + 1];
            strcpy(res, s.res);
        }

        return *this;
        cout << "Cpy assign constructor called" << endl;
    }

    friend istream &operator>>(istream &in, String &s);
    friend ostream &operator<<(ostream &out, const String &s);

    ~String()
    {
        if (res)
        {
            delete res;
        }
    }
};

istream &operator>>(istream &in, String &s)
{
    s.res = new char[1000];
    in >> s.res;
    s.len = strlen(s.res);
    return in;
}

ostream &operator<<(ostream &out, const String &s)
{
    out << s.res;
    return out;
}

int main()
{

    /// from users point of view

    // String s1;             // default constructor
    // String s2 = "Yoganand";  //parametrized constructor
    // String s2("Yoganand"); // paremeterized constructor
    // String sin;

    // // cout << "Enter String" << endl;
    // // cin >> sin;
    // // cout << "output:" << endl;
    // // cout << sin;
    // String s3 = s2; // copy constructor
    // // cout << s2 << endl;
    // // cout << s3 << endl;
    // String s4;
    // s1 = s4 = s3; // copy assign constructor
    // cout << s4 << endl;
    String s2 = "Yoganand"; // parametrized constructor
    // String s1 = std::move(s2);

    // cout << "s2:" << s2 << endl;

    // cout << "s1:" << s1 << endl;
    return 0;
}