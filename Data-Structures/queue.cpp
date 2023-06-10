#include<iostream>
#include<queue>
using namespace std;
#define SIZE 5
/*class queue
{
        int arr[SIZE];
        int front;
        int rear;
        int count;
    public:
    void enqueue(int );
    void dequeue();
    void showFront();
    void back();
    void showQueue();
    queue()
    {
        front = 0;
        rear =0;
        count =0;
    }
};
void queue::enqueue(int val)
{
    if(count<SIZE)
    {
        arr[rear%SIZE] = val;
        rear++;
        count++;
    }
    else
    {
        cout<<"Queue is full"<<endl;
    }
}
void queue::dequeue()
{
    if(count!=0)
    {
        cout<<"Popped :"<<arr[front%SIZE]<<endl;
        front++;
        count--;
    }
    else
    {
        cout<<"queue is empty"<<endl;
    }
}
void queue::showFront()
{
    if(count!=0)
        cout<<"front is :"<<arr[front%SIZE]<<endl;
    else
       cout<<"Queue is empty"<<endl; 
}
void queue::back()
{
    if(count!=0)
    {
        cout<<"rear is :"<<arr[(rear-1)%SIZE]<<endl;
    }   
    else
       cout<<"Queue is empty"<<endl; 
}
void queue::showQueue()
{
    int j = front;
    if(count ==0)
        cout<<"Queue is empty"<<endl;
    for(int i = 0 ; i<count; i++)
    {
        cout<<arr[j%SIZE]<<" ";
        j++;
    }
    cout<<endl;
}*/
int main()
{
    /*queue q1;
   // q1.showQueue();
   // q1.dequeue();
    q1.enqueue(2);
     q1.enqueue(3);
      q1.enqueue(4);
       q1.enqueue(5);
        q1.enqueue(6);
         q1.showQueue();
         // q1.dequeue();
         // q1.dequeue();
         // q1.enqueue(2);
         // q1.enqueue(10);
//q1.enqueue(11);
        //  q1.showQueue();
          // q1.dequeue();
            q1.dequeue();
          //   q1.dequeue();
              q1.showQueue();
            // q1.showFront();
            q1.enqueue(10);
              q1.back();
*/

    //STL

    queue<int> q1,q2;

    q1.push(2);
    q1.push(3);
    q1.swap(q2);

    cout<<q1.empty()<<endl;

    return 0;
}