#include <iostream>
#include <vector>

using namespace std;


vector<int> buildMatrix(const int size)
{
	vector<int> matrix;
	matrix.reserve(size);

	for (int i = 0; i < size; i++)
	{
		int el;
		cout << "Enter 0 or 1:\n";
		cin >> el;

		if (el < 0 || el > 1)
		{
			i--;
			cout << "Enter a correct number!\n";
			continue;
		}
		matrix.push_back(el);
	}
	return matrix;
}


vector<int> longestEqual01Subarray(const vector<int>& arr) 
{
	int n = arr.size();
	int offset = n;  

	vector<int> firstIndex(2 * n + 3, -1);

	int prefix = 0; 

	firstIndex[offset] = -2;

	int bestLen = 0;
	int bestStart = -1;

	for (int i = 0; i < n; i++) 
	{
		prefix += (arr[i] == 0 ? -1 : 1);

		int idx = prefix + offset;


		if (idx < 0 || idx >= firstIndex.size())
			continue;

		if (firstIndex[idx] != -1) 
		{

			int start = (firstIndex[idx] == -2 ? 0 : firstIndex[idx] + 1);
			int length = i - start + 1;

			if (length > bestLen) {
				bestLen = length;
				bestStart = start;
			}
		}
		else {
			firstIndex[idx] = i;
		}
	}

	if (bestLen == 0) return {};

	return vector<int>(arr.begin() + bestStart, arr.begin() + bestStart + bestLen);
}
int main()
{
	int N;
	cout << "Enter N:\n";
	cin >> N;

	vector<int> matrix;
	matrix = buildMatrix(N);


	vector<int> result = longestEqual01Subarray(matrix);


	if (result.empty()) 
		cout << "No subarray with equal number of 0s and 1s.\n";
	
	else {
		cout << "Longest subarray with equal number of 0s and 1s:\n";
		for (int x : result) 
			cout << x << " ";
		cout << endl;
	}
}

