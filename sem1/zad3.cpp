#include <iostream>
int findLength(const char* str)
{
    int counter = 0;
    while (*str != '\0')
    {
        counter++;
        str++;
    }
    return counter;
}
bool isPalindrom(const char* str, int start, int end)
{
    if (str[start] != str[end])
    {
        return false;
    }
    if (end - start <= 1)
    {
        return true;
    }
    isPalindrom(str, start + 1, end - 1);
    
}

int main()
{
    char str[100] = "abccba";
    int l = findLength(str);
    std::cout << isPalindrom(str, 0, l-1);
  
}
