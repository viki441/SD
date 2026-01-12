#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>

using namespace std;


class MinHeap 
{
	vector<int> heap;
	bool isValid;


	void siftDown(int n)
	{
		int smallest = n;
		int left = n * 2 + 1;
		int right = n * 2 + 2;

		if (left < heap.size() && heap[left] < heap[smallest])
			smallest = left;

		if (right < heap.size() && heap[right] < heap[smallest])
			smallest = right;

		if (smallest != n) {
			swap(heap[n], heap[smallest]);
			siftDown(smallest);
		}
	}


	void buildHeap()
	{
		for (int i = heap.size() / 2 - 1; i >= 0; i--)
		{
			siftDown(i);
		}
	}

	void ensureHeap()
	{
		if (!isValid)
		{
			buildHeap();
			isValid = true;
		}
	}

public:
	void insertConstSpeed(int n)
	{
		heap.push_back(n);
		isValid = false;
	}

	int extractMin()
	{
		if (heap.empty()) throw runtime_error(" ");

		ensureHeap();

		int min = heap[0];
		swap(heap[0], heap.back());
		heap.pop_back();

		if (!heap.empty()) siftDown(0);

		return min;

	}

	int getMin()
	{
		if(heap.empty())
			throw runtime_error(" ");
		ensureHeap();
		return heap[0];
	}


};

int main() {
    MinHeap h;

    h.insertConstSpeed(5);
    h.insertConstSpeed(3);
    h.insertConstSpeed(10);
    h.insertConstSpeed(1);

    std::cout << h.extractMin() << std::endl; // 1
    std::cout << h.extractMin() << std::endl; // 3
}
