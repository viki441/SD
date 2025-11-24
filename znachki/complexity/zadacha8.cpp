#include <iostream>
#include <vector>

template <typename T>
void swap(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

int partition(std::vector<int>& array, int start, int end)
{
	int pivot = array[end];
	int i = start - 1;

	for (int j = start; j <= end; j++)
	{
		if (array[j] < pivot)
		{
			i++;
			swap(array[i], array[j]);
		}
	}

	swap(array[i + 1], array[end]);
	return i + 1;
}


void quickSort(std::vector<int>& array, int start, int end)
{
	if (start < end)
	{
		int partitionReturn = partition(array, start, end);

		quickSort(array, start, partitionReturn - 1);
		quickSort(array, partitionReturn + 1, end);

	}
}

std::vector<std::vector<int>> findTriplets( std::vector<int> array)
{
	std::vector<std::vector<int>> results;
	quickSort(array, 0, array.size() - 1);
	//the idea is to lower to task from finding the sum of three to finding the sum of two elements

	for (size_t i = 0; i < array.size() - 2; ++i)
	{	

		//we need to take one iterator i, and then make 2 more
		//both of them are going to start at opposite sites of the remaining array
		//and will 'shrink' it
		int j = i + 1;
		int k = array.size() - 1;

		while (j < k)
		{
			int total = array[i] + array[j] + array[k];

			/*if (i > 0)
				continue;*/

			if (total > 0) // if total is > 0 that means the number at the end of the array is too big, so we bring k closer to j, so we can get a smaller number
				k--;

			else if (total < 0) //same logic from the other side
				j++;

			else
			{
				results.push_back({ array[i], array[j], array[k] });
				j++;


				while (j < k && array[j] == array[j - 1])
					j++;
			}
		}

		
	}
	return results;
}

int findProperIndex(const int element, const std::vector<int>& array)
{
	for (size_t i = 0; i < array.size(); ++i)
	{
		if (array[i] == element) return i;
	}
	return -1;
}

void buildVector(std::vector<int>& array, int size)
{
	int el;
	std::cout << "Enter numbers for the array: \n";
	for (int i = 0; i < size; ++i)
	{
		std::cin >> el;
		array.push_back(el);
	}
}


void printResults(std::vector<int> array, std::vector<std::vector<int>> results)
{
	if (results.size() <= 0)
	{
		std::cout << "No combos\n";
		return;
	}
	for (int i = 0; i < results.size(); ++i)
	{
		std::cout << "Combination " << i + 1 << std::endl;

		for (int j = 0; j < results[i].size(); ++j)
		{
			std::cout << "( " << results[i][j] << ", index: " << findProperIndex(results[i][j], array) << " ),";
		}
		std::cout << std::endl;
	}
};
int main()
{
	//assuming array has different non-repeating numbers from - "Създайте програма, която прочита число N от стандартния вход и след това прочита N !!различни числа."
	int n;
	std::cout << "Pick a number: \n";
	std::cin >> n;
	
	//using raw pointers may make the program slightly faster, but vector is safer
	std::vector<int> array;
	buildVector(array, n);
	

	std::vector<std::vector<int>> results;

	if (array.size() > 2)
	{
		results = findTriplets(array);//copy in findTriplets, so i still have the right indexes
		printResults(array, results);
	}
	else
	{
		std::cout << "Array is too small for triplets";
	}

}

