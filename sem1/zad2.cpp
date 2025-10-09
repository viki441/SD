
#include <iostream>
#include <fstream>
namespace FILES
{
    const char NAME[100] = "C:\\Users\\vikik\\Desktop\\example.txt";
}
int findLenght()
{
    std::ifstream file(FILES::NAME);
    if (!file.is_open())
    {
        return 0;
    }
    char ch = file.get();
    int length = ch - '0';
    file.close();
    return length;
}

char* extractString(const int length)
{
    std::ifstream file(FILES::NAME);
    if (!file.is_open())
    {
        return 0;
    }
    char* newStr = new char[length + 1];
    file.get();
    file.read(newStr, length);
    newStr[length] = '\0';
    return newStr;
    
    
}
int main()
{
    int length = findLenght();
    std::cout << extractString(length);
  
}

