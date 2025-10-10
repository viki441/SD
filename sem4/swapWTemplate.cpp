#include <iostream>
template<typename T>
class A 
{
private: 
	T val1;
	T val2;


public:
	A(T val1, T val2) :val1(val1), val2(val2) {};

	void swap()
	{
		T temp = this->val1;
		this->val1 = this->val2;
		this->val2 = temp;
	}
	void printInfo()
	{
		std::cout << "val1: " << val1 << std::endl;
		std::cout << "val2: " << val2 << std::endl;
	}

};
int main()
{
	A<int> a(11,1);
	a.printInfo();
	a.swap();
	a.printInfo();

}
