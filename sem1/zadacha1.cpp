
#include <iostream>

template <typename T>
void swapByPointer(T *lhs, T *rhs)
{
    T swap = *lhs;
    *lhs = *rhs;
    *rhs = swap;
 
}

template<typename T>
void swapByReference(T& lhs, T& rhs)
{ 
    T swap = lhs;
    lhs = rhs;
    rhs = swap;

}
int main()
{
    int a = 8;
    int b = 0;
    
    swapByPointer<int>(&a,&b);
    swapByReference<int>(a,b);

}

