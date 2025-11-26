#include <stdexcept>
#include <string>
#include <iostream>
#include <cctype>
using namespace std;

template<typename T>
class linkedStack
{

public:
	//-------------------------------------BIG 3-----------------------------------------------
	linkedStack() = default;
	linkedStack(const linkedStack&) = delete;
	linkedStack& operator=(const linkedStack&) = delete;
	~linkedStack()
	{
		clearStack();
	}

	
	//--------------------------------------PUSH------------------------------------------------
	void push(const T& value)
	{
		tos = new node(value, tos);
	}
	//---------------------------------------POP----------------------------------------------
	T pop()
	{
		if (isEmpty())
			throw out_of_range("Stack is empty\n");

		node* temporary = tos;
		tos = temporary->next;

		T data = temporary->data;
		delete temporary;
		return data;
	}
	//-------------------------------TOP------EMPTY-----------------------------------------
	bool isEmpty() const
	{
		return tos == nullptr;
	}

	T top() const
	{
		if (isEmpty()) 
			throw out_of_range("Stack  is empty\n");
		return tos->data;
		
	}
	
	//-------------------------------SIZE-----------------------------------------------------
	int getSize() const
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

//-------------------------------------------------------------------------------------------------------------------------//
template<typename T>
class CompositeStack
{
private:
	linkedStack<T> stack1; // undo history
	linkedStack<T> stack2; // redo history


public:
	void push1(T& value)
	{
		stack1.push(value);
	}
	void push2(T& value)
	{
		stack2.push(value);
	}

	T pop1()
	{
		return stack1.pop();
	}
	T pop2()
	{
		return stack2.pop();
	}

	T peek1()
	{
		return stack1.top();
	}
	T peek2()
	{
		return stack2.top();
	}

	bool isEmpty1() {
		return stack1.isEmpty();
	}
	bool isEmpty2() {
		return stack2.isEmpty();
	}
};


class UndoRedoStringBuilder
{
private:
	string _s;
	CompositeStack<string> stacks;


public:
	void append(string& s)
	{
		stacks.push1(_s); //slaga se poslednata komanda  
		_s += s;
		while (!stacks.isEmpty2())
			stacks.pop2();
	}

	string getResult()
	{
		return this->_s;
	}

	void undo()
	{
		if (!stacks.isEmpty1())
		{
			stacks.push2(_s);
			_s = stacks.pop1();
		}
		throw std::out_of_range("cant undo\n");
	}
	void redo()
	{
		if (!stacks.isEmpty2())
		{
			stacks.push1(_s);
			stacks.pop2();
		}
		throw std::out_of_range("cant redo\n");
	}
};


int main()
{
	CompositeStack<int> s;
	int a = 1;
	int b = 2;


	s.push1(a);
	s.push2(b);

	std::cout << s.peek1() << " " << s.peek2() << std::endl;

	s.push1(b);
	s.push2(a);

	std::cout << s.peek1() << " " << s.peek2() << std::endl;

	std::cout << s.pop1() << " " << s.pop2() << std::endl;
	std::cout << s.peek1() << " " << s.peek2() << std::endl;
}
