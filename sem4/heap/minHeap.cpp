#include <algorithm>
#include <stdexcept>
#include <iostream>
#include "MinHeap.h"

using namespace std;

MinHeap::MinHeap()
	:isValid(true)
{
}
	
void MinHeap::siftDown(int n)
{
	int size = heap.size();// because some parents may not have all 2 children
	//n is the index of the last parent
	while (true)
	{
		//notice we work mainly with the indexes
		int parent = n;
		int left = n * 2 + 1;
		int right = n * 2 + 2;

		if (left < size && heap[left] < heap[parent])
			parent = left;

		if (right < size && heap[right] < heap[parent])
			parent = right;

		if (parent == n)
			break;
			
		swap(heap[n], heap[parent]);

		n = parent; // "sift-down"
	
	}

}

void MinHeap::siftUp(int n) // is child
{	
	while (n > 0)
	{
		int parent = (n - 1) / 2;

		if (heap[n] >= heap[parent])
			break;
		
		swap(heap[parent], heap[n]);
	
		n = parent; // "sift-up"
	}
}


void MinHeap::heapify()
{
	if (isEmpty()) throw runtime_error("can heapify an empty heap");

	if (!isValid)
	{
		for (int i = heap.size() / 2 - 1; i >= 0; i--)
		{
			siftDown(i);
		}
		
	}
	isValid = true;
}

bool MinHeap::isEmpty()
{
	return heap.size();
}

void MinHeap::insertConst(int n)
{
	heap.push_back(n);
	//isValid = false;
	siftUp(heap.size() - 1);
}

int MinHeap::extractMin()
{
	if (isEmpty()) throw runtime_error("heap is empty");

	int min = heap[0];

	swap(heap[0], heap.back());
	heap.pop_back();

	if (!isEmpty()) heapify();

	return min;

}

int MinHeap::getMin()
{
	if (heap.empty())
		throw runtime_error("em");
	if(!isValid)
		heapify();

	return heap[0];
}


int main()
{
    MinHeap h;

    h.insertConst(5);
    h.insertConst(3);
    h.insertConst(10);
    h.insertConst(1);

    std::cout << h.extractMin() << std::endl; // 1
    std::cout << h.extractMin() << std::endl; // 3
}
