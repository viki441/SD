#include <iostream>
#include <vector>

using namespace std;
///////////////////////////////INSERTION SORT///////////////////////
void insertionSort(vector<int>& list, int n)
{
	for (int i = 0; i < n; ++i)
	{
		int key = list[i];
		int j = i - 1;
		
		while (j >= 0 && list[j] > key)
		{
			list[j + 1] = list[i];
			j--;
		}
		list[j + 1] = key;
	}
}


///////////////////////////////SHAKER SORT/////////////////////////
void shakerSort(vector<int>& list)
{
	bool swapped = true;
	int start = 0;
	int end = list.size() - 1;
	 
	while (swapped)
	{
		swapped = false;

		for (int i = start; i < end; i++)
		{
			if (list[i] > list[i + 1])
			{
				swap(list[i], list[i + 1]);
				swapped = true;
			}
		}
		if (!swapped)
			break;

		swapped = false;
		--end;

		for (int i = end - 1; i >= start; --i)
		{
			if (list[i] > list[i + 1])
			{
				swap(list[i], list[i + 1]);
				swapped = true;
			}
		}
		++start;
	}
}

////////////////////////////BUBBLE SORT////////////////////////////
void bubbleSort(vector<int>& list)
{
	int n = list.size();
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (list[j] > list[j + 1])
				swap(list[j], list[j + 1]);
		}
		
	}
}

////////////////////////////SELECTION SORT//////////////////////////
void selectionSort(vector<int>& list)
{
	int n = list.size();

	for (int i = 0; i < n - 1; i++)
	{
		int minInd = i;

		for (int j = i + 1; j < n - 1; j++)
		{
			if(list[j] < list[minInd])
			{
				minInd = j;
			}
		}

		swap(list[i], list[minInd]);

	}

}

//////////////////////////////////MERGE SORT////////////////////////
void merge(vector<int>& list, int left, int mid, int right)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;

	vector<int> l(n1), r(n2);

	for (int i = 0; i < n1; i++)
		l[i] = list[left + i];

	for (int i = 0; i < n2; i++)
		r[i] = list[mid + i + 1];

	int i = 0;
	int j = 0;
	int k = left;

	while (i < n1 && j < n2)
	{
		if (l[i] < r[j])
		{
			list[k] = l[i];
			i++;
		}
		else
		{
			list[k] = r[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		list[k] = l[i];
		i++;
		k++;
	}


	while (j < n2)
	{
		list[k] = r[j];
		j++;
		k++;
	}
}
void mergeSort(vector<int>& list, int left, int right)
{
	if (left >= right)
	{
		return;
	}

	int mid = left + (right - left) / 2;
	mergeSort(list, left, mid);
	mergeSort(list, mid + 1, right);
	merge(list, left, mid, right);
}


///////////////////////////HEAP SORT MAX//////////////////////////////
void heapify(vector<int>& list, int n, int i)
{
	int largest = i;
	int leftchild = i * 2 + 1;
	int rightchild = i * 2 + 2;

	if (n > leftchild && list[leftchild] > list[largest])
		largest = leftchild;

	if (rightchild < n && list[rightchild] > list[largest])
		largest = rightchild;

	if (largest != i)
	{
		swap(list[i], list[largest]);
		heapify(list, n, largest);
	}
}
void heapSort(vector<int>& list, int toRemove)
{
	int n = list.size();
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapify(list, n, i);
	}
	for (int i = 0; i < list.size(); i++)
	{
		swap(list[0], list[i]);
		heapify(list, i, 0);
	}
}


///////////////////QUICK SORT//////////////////////////////////////
int partition(vector<int>& list, int low, int high)
{
	int pivot = list[high];

	int i = low - 1;
	for (int j = low; j < high - 1; j++)
	{
		if (list[j] <= pivot)
		{
			i++;
			swap(list[i], list[j]);
		}
	}
	swap(list[i + 1], list[high]);
	return (i + 1);
}
void quickSort(vector<int>& list, int low, int high)
{
	if (low < high)
	{
		int pi = partition(list, low, high);

		quickSort(list, low, pi - 1);
		quickSort(list, pi + 1, high);
	}
}

int main()
{

	vector<int> list = { 1,3,4,6,8,4,7,9,3,89,3,4,675,6,2323,7,2,9,0,3 };
	
	quickSort(list, 0, list.size()-1);

	int toRemove = 4;
	heapSort(list, toRemove);

	mergeSort(list, 0, list.size() - 1);

	selectionSort(list);

	bubbleSort(list);

	shakerSort(list);

}