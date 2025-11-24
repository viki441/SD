#include <iostream>
#include <vector>


using namespace std;

int validateInput()
{
	int input;
	while (true)
	{
		if (cin >> input && input >= 0)
			return input;

		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid input, try again: ";
	}
}

void buildArray(vector<int>& numbers, const int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << "Enter element " << i + 1 << endl;
		int elem = validateInput();
		bool valid = false;
		numbers.push_back(elem);
	}
}

void buildSubArrays(int start, const vector<int>& numbers, vector<vector<int>>& subarrs, vector<int>& curr, int sizeOfSub)
{
	if (curr.size() == sizeOfSub)
	{
		subarrs.push_back(curr);
		return;
	}
	for (int j = start; j < numbers.size(); j++)
	{
		curr.push_back(numbers[j]);
		buildSubArrays(j + 1, numbers, subarrs, curr, sizeOfSub);
		curr.pop_back();
	}
}

void buildKsizeSub(const vector<int>& numbers, vector<vector<int>>& subarrs, vector<int>& curr, int sizeOfSub)
{
	for (int i = 1; i < sizeOfSub; i++)
	{
		buildSubArrays(0, numbers,subarrs,curr,i);
	}
}

void printArray(const vector<vector<int>>& arr)
{
	for (int i = 0; i < arr.size(); ++i)
	{
		for (int j = 0; j < arr[i].size(); ++j)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

}

int main()
{
	cout << "Enter N: \n";
	int N = validateInput();
	vector<int> arr;
	buildArray(arr, N);

	vector<int> curr;
	vector<vector<int>> subarrs;

	buildKsizeSub(arr, subarrs, curr, N);
	buildSubArrays(0, arr, subarrs, curr, N);

	printArray(subarrs);

}
