#include<iostream>
using namespace std;
#define SIZE 30
class stack
{
    int top;
    int arr[SIZE];
    public:
        void pop();
        void push(int);
        int size();
        void ShowTop();
        void showStack();
        stack()
        {
            top = -1;
        }
};


void stack ::push(int val)
{
    if(top<SIZE)
    {
        arr[top+1] = val;
        top++;
    }    
    else
        cout<<"Can not perform push operation. Capacity reached. stack overflow"<<endl;
}

void stack::pop()
{
    if(top!=-1)
    {
        cout<<arr[top]<<" Popped"<<endl;
        top--;
    }
    else
    cout<<"Cant perform pop(). stack is empty."<<endl;
}

void stack::showStack()
{
    if(top!=1)
    {
        for(int i=0 ; i<=top ; i++)
        {
            cout<<arr[i]<< "    ";
        }

        cout<<endl;
    }
    else
        cout<<"stack is empty"<<endl;
}

int stack::size()
{
    if(top==-1)
    return 0;
    else
    return top+1;
}

void stack::ShowTop()
{
    if(top!=-1)
       {
           cout<<"Top is :"<<arr[top]<<endl;
       }
    else
        {
            cout<<"stack is empty."<<endl;
        }
}
int main()
{
    stack s1;
   // s1.push(1);
   // s1.push(5);
   // s1.push(3);
   // s1.push(11);
   // s1.push(10);
    //s1.push(-1);
    s1.push(-7);

    s1.showStack();
    s1.pop();
    s1.showStack();
    s1.ShowTop();
    int size = s1.size();
    cout<<"\nSize is:"<<size<<endl;

    return 0;
}