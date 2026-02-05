#pragma once
#include <vector>

using namespace std;

class MinHeap
{

public:
	MinHeap();
	void insertConst(int n); // vika siftUp

	int extractMin(); // vika heapify

	int getMin();
	bool isEmpty();

private:
	vector<int> heap;
	bool isValid;

	void siftUp(int n); // raboti bez dopulnitelen for & func
	void siftDown(int n);


	void heapify(); // vika siftDown

	//MERGE - insertConst + sift_up


};