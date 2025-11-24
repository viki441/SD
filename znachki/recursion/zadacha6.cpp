#include <iostream>
#include <vector>
#include <limits>// for std::numeric_limits, for validation of input

/*understanding of first sub task - permutations of all distinct numbers only*/

using namespace std;

//////////////////////////SORT///////////////////////////////
template<typename T>
void mySwap(T& a, T& b)
{
	T temp = a;
	a = b; 
	b = temp;
}

int partition(vector<int>& numbers, int start, int end)
{
	int pivot = numbers[end];
	int i = start - 1;

	for (int j = start; j <= end; j++)
	{
		if (numbers[j] < pivot)
		{
			i++;
			mySwap(numbers[i], numbers[j]);
		}
	}

	mySwap(numbers[i + 1], numbers[end]);
	return i + 1;
}

void quickSort(vector<int>& numbers, int start, int end)
{
	if (start < end)
	{
		int partitionReturn = partition(numbers, start, end);


		quickSort(numbers, start, partitionReturn - 1);
		quickSort(numbers, partitionReturn + 1, end);
	}
}

////////////////////////VALIDATE////////////////////////////////
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

vector<int> stripDuplicatesFromNumbers(vector<int> numbers)
{
	quickSort(numbers, 0, numbers.size() - 1);
	//or just sort(numbers.begin(), numbers.end());

	vector<int> result;
	for (size_t i = 0; i < numbers.size(); ++i) {
		if (i == 0 || numbers[i] != numbers[i - 1])
			result.push_back(numbers[i]);
	}
	return result;
}

///////////////////////COMPUTE////////////////////////////////////

//no duplicates, no K constraint
void buildPermutations(int start, vector<vector<int>>& permutations, vector<int>& numbers)
{

	if (start == numbers.size()) // if only one element in numbers
	{
		permutations.push_back(numbers);
		return;
	}

	for (int j = start; j < numbers.size(); j++)
	{
		mySwap(numbers[start], numbers[j]);
		buildPermutations(start + 1, permutations, numbers);
		mySwap(numbers[start], numbers[j]);
	}


}

//K elements in subarray, assuming all diplicated numbers fall each time
void buildVariations(int start, vector<int>& numbers, vector<vector<int>>& variations, int K)
{
	if (K == start)
	{
		variations.push_back(vector<int>(numbers.begin(), numbers.begin() + K));
		return;
	}

	for (int j = start; j < numbers.size(); j++)
	{
		mySwap(numbers[start], numbers[j]);
		buildVariations(start + 1, numbers, variations, K);
		mySwap(numbers[start], numbers[j]);
	}

}

//K elements in subarray, assuming all diplicated numbers fall each time
void buildCombinations(int start, vector<int>& numbers, vector<int>& curr, vector<vector<int>>& combinations, int K)
{
	if(curr.size() == K)
	{
		combinations.push_back(curr);
		return;
	}

	for (int j = start; j < numbers.size(); j++)
	{
		curr.push_back(numbers[j]);
		buildCombinations(j + 1, numbers, curr, combinations, K);
		curr.pop_back();
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

	cout << "Enter N:\n";
	int N = validateInput();

	cout << "Enter K:\n";
	int K = validateInput();

	vector<int> numbers;
	buildArray(numbers, N);
	vector<int> noDuplicateNumbers = stripDuplicatesFromNumbers(numbers);

	//PERMUTATIONS
	vector<vector<int>> permutations;
	buildPermutations(0, permutations, noDuplicateNumbers);

	//VARIATIONS
	vector<vector<int>> variations;
	buildVariations(0, noDuplicateNumbers, variations, K);


	//COMBINATIONS
	vector<int> curr;
	vector<vector<int>> combinations; //where 1 2 is same as 2 1
	buildCombinations(0, noDuplicateNumbers, curr, combinations, K);


	//print
	cout << "Permutations\n";
	printArray(permutations);
	cout << "Variations\n";
	printArray(variations);
	cout << "Combinations\n";
	printArray(combinations);

	
}
