//https://github.com/Teodor1379/Data-Structures-and-Programming/blob/main/Informatics/2025-2026/Seminars/Group%203/Week%2003/README.md
/*
Създайте програма, която прочита от стандартния вход символен низ, съдържащ единствено ( и ). 
Балансиран символен низ наричаме такъв низ, в който на всяка ( съответства точно една ) и в едно такова съответствие 
( предшества ) по позиции. На стандартния изход изведете дали въведения символен низ е балансиран, като булев резултат.
*/
#include <stdexcept>
#include <string>
#include <iostream>
using namespace std;

template<typename T>
class linkedStack
{

public:
	//--------------------------------------PUSH------------------------------------------------
	void push(const T& value) // dobavqne na element PREDI segashniq tos
	{
		tos = new node(value, tos);
	}
	//---------------------------------------POP----------------------------------------------
	T pop()
	{
		if (tos != nullptr)
		{
			node* temporary = tos; 
			tos = temporary->next; 

			T data = temporary->data;
			delete temporary;
			return data;

		}
		throw std::out_of_range("error");
	}
	//-------------------------------TOP------EMPTY-----------------------------------------
	bool isEmpty()
	{
		return tos == nullptr;
	}
	T top() // tuk se vzima ne addresa za tos, a koq stoinost (data) e pri kutiikata kum koqto sochi lista
	{
		if (tos != nullptr) return tos->data;
		throw std::out_of_range("Error");
	}
	//-------------------------------SIZE-----------------------------------------------------
	int getSize()
	{
		int counter = 0;
		node* runner = tos;
		while (runner != nullptr)
		{
			counter++;
			runner = runner->next;
		}
		return counter;
	}
	//-------------------------------CLEAR---------------------------------------------------
	bool clearStack()
	{
		if (isEmpty())
			return false;

		while (!isEmpty())
			pop();

		return true;
	}

private:
	struct node
	{
		T data;
		node* next;

		node(const T& d, node* n = nullptr)
			:data(d), next(n)
		{}
	};
	node* tos = nullptr;

	
};

bool isCorrect(const string& text, linkedStack<char>& stack)
{
	for (char c : text)
	{
		if(c == '(' || c == '[' || c == '{')
			stack.push(c);

		else
		{
			if (stack.isEmpty())
				return false;

			char top = stack.top();

			if ((top == '(' && c == ')') ||
				(top == '[' && c == ']') ||
				(top == '{' && c == '}'))
			{
				stack.pop();
			}
			else
				return false;
		}
	}
	return stack.isEmpty();
		
}
int main()
{
	string text = "({[{{}]})";
	linkedStack<char> stack;
	cout << isCorrect(text, stack);

}

