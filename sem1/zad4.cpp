#include <iostream>
int factorial(int n)
{
    if (n == 1)
    {
        return 1;
    }
    n *= factorial(n - 1);
}
void sumOfPermutations(const int* arr)
{
    while (*arr)
    {
        std::cout << factorial(*arr) << " ";
        arr++;
    }
}

int main()
{
    int arr[5] = { 5,3,9,3,4 };
    sumOfPermutations(arr);
  
}

