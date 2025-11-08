#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept> 


//SORT NUMBER LIST-----------------------------------------------------------


//BUILD NUMBER LIST ---------------------------------------------------------
std::vector<int> buildNumbersList(int size)
{
    if (size <= 0)
        throw std::invalid_argument("Size must be positive number.\n");

    std::vector<int> arr(size);

    std::cout << "Enter " << size << " numbers\n";
    for (int i = 0; i < size; ++i)
        std::cin >> arr[i];
    return arr;
}

//SORTING THE MATRIX--------------------------------------------------------
std::vector<std::vector<int>> buildMatrix(int n, int m, const std::vector<int>& sortedList)
{
    if (n <= 0 || m <= 0)
        throw std::invalid_argument("Enter correct n and m\n");
    if (sortedList.size() != static_cast<size_t>(n * m))
        throw std::invalid_argument("Invalid size.\n");

    std::vector<std::vector<int>> matrix(n, std::vector<int>(m));


    int index = 0;
    for (int i = 0; i < n; ++i) 
        for (int j = 0; j < m; ++j) 
            matrix[i][j] = sortedList[index++];

    return matrix;
}


//SEARCH FOR K----------------------------------------------------------------
bool searchInMatrix(const std::vector<std::vector<int>>& matrix, int k)
{
    int n = matrix.size();

    if (n == 0) return false;

    int m = matrix[0].size();

    int row = 0;
    int col = m - 1;

    while (row < n && col >= 0)
    {
        if (matrix[row][col] == k)
            return true;
        else if (matrix[row][col] > k)
            col--;
        else
            row++;
    }

    return false;
}


void printMatrix(const std::vector<std::vector<int>>& matrix)
{
    std::cout << "The matrix is:\n";
    for (const auto& row : matrix)
    {
        for (int val : row)
            std::cout << val << "\t";
        std::cout << "\n";
    }
}

int main()
{
    try
    {
        int n, m;
        std::cout << "Enter N and M: ";
        std::cin >> n >> m;

        std::vector<int> numbers = buildNumbersList(n * m);
        std::sort(numbers.begin(), numbers.end());

        std::vector<std::vector<int>> matrix = buildMatrix(n, m, numbers);

        printMatrix(matrix);

        int k;
        std::cout << "Enter number K: ";
        std::cin >> k;

        bool found = searchInMatrix(matrix, k);

        if (found)
            std::cout << "The number " << k << " is part of matrix.\n";
        else
            std::cout << "The number " << k << " is NOT in the matrix.\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
