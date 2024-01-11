/*
Author : Yoganand Kanhed
Descripton : Max Heap Implementation
*/

#include <iostream>
#include <vector>
using namespace std;

class Heap
{
private:
    vector<int> heap;

public:
    void heapify(int index, int size); // downAdjust useful in extracting Max
    void insert(int element);
    void extractMax();
    void percolateUp(int ind); // upAdjust() from last index to root to maintain the heap structure (useful in insert())
    void displayHeap();
    void incrementKey(int index, int key);
    void decrementKey(int index, int key);
    void MaxHeadSort();
    void buildHeap(vector<int> vec);
};

void Heap::buildHeap(vector<int> vec)
{
    heap = vec;
    for (int i = (heap.size() / 2) - 1; i >= 0; i--)
    {
        heapify(i, heap.size());
    }
}

void Heap::insert(int element)
{
    heap.push_back(element);
    percolateUp(heap.size() - 1);
}

void Heap::percolateUp(int ind)
{
    int index = ind;
    while (index > 0 && heap[(index - 1) / 2] < heap[index])
    {
        swap(heap[(index - 1) / 2], heap[index]);
        index = (index - 1) / 2;
    }
}

void Heap::displayHeap()
{
    for (auto element : heap)
        cout << element << "  ";
    cout << endl;
}

void Heap::extractMax()
{
    if (!heap.empty())
    {
        int maxElement = heap[0];
        cout << "Max element :" << maxElement << " Extracted." << endl;
        swap(heap[0], heap[heap.size() - 1]);
        heap.pop_back();
        heapify(0, heap.size());
    }
}

void Heap::heapify(int index, int size)
{
    if (!heap.empty())
    {
        int parentIndex = index;

        // here there are two conditios when heapify which up to down adjust will stop.
        // 1. when the index is actual a leaf index
        // 2. when index is > than both left and right child.
        while (1)
        {
            int leftChildIndex = 2 * parentIndex + 1;
            int rightChildIndex = 2 * parentIndex + 2;
            int LargestIndex = parentIndex;

            if (leftChildIndex < size && heap[leftChildIndex] > heap[LargestIndex])
            {
                LargestIndex = leftChildIndex;
            }

            if (rightChildIndex < size && heap[rightChildIndex] > heap[LargestIndex])
            {
                LargestIndex = rightChildIndex;
            }

            if (parentIndex == LargestIndex)
                break;

            swap(heap[LargestIndex], heap[parentIndex]);
            parentIndex = LargestIndex;
        }
    }
}

void Heap::incrementKey(int index, int key)
{
    if (heap[index] > key)
    {
        cout << "invalid Op" << endl;
        return;
    }

    if (index < heap.size() && index > 0)
    {
        heap[index] = key;
        percolateUp(index);
    }
    else
    {
        cout << "Invalid index" << endl;
    }
}

void Heap::decrementKey(int index, int key)
{
    if (heap[index] < key)
    {
        cout << "invalid Op" << endl;
        return;
    }

    if (index < heap.size() && index > 0)
    {
        heap[index] = key;
        heapify(index, heap.size());
    }
    else
    {
        cout << "Invalid index" << endl;
    }
}

void Heap::MaxHeadSort()
{
    for (int i = heap.size() - 1; i > 0; i--)
    {
        swap(heap[0], heap[i]);
        heapify(0, i); // here heapify until less than N-1, N-2 and so on
    }
}

int main()
{

    Heap h1;
    // h1.insert(9);
    // h1.insert(8);
    // h1.insert(7);
    // h1.insert(5);
    // h1.insert(4);
    // h1.insert(3);
    // h1.insert(2);
    // h1.insert(10);
    // h1.insert(10);
    // h1.displayHeap();

    // h1.insert(9);
    // h1.displayHeap();
    // h1.decrementKey(1, 1);
    // h1.extractMax();
    // h1.displayHeap();
    // h1.incrementKey(3, 10);
    // h1.displayHeap();
    // h1.incrementKey(5, 12);
    h1.buildHeap({4, 7, 5, 9, 10, 12});
    // h1.MaxHeadSort();
    h1.displayHeap();
    return 0;
}