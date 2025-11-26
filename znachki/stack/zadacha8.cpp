/*
Създайте програма, която изчислява аритметичен израз, записан в инфиксен запис, въведен от стандартния вход като символен низ. 
Аритметичният израз съдържа цели числа и бинарните операции +, -, *, / със стандартната им семантика. На стандартния изход 
изведете резултата от изчислението на аритметичния израз, запазвайки приоритета на операциите.
*/
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


template <typename T>
class queue
{
public:
	queue() = default;
	queue(const queue&) = delete;
	queue& operator=(const queue&) = delete;
	~queue()
	{
		while (!isEmpty())
			pop();
	}

	T pop()
	{
		if (front == nullptr)
			throw std::underflow_error("Cannot pop from empty queue");

		queueNode* temp = front;
		
		T value = temp->data;

		front = front->next;
		if (front == nullptr)   
			end = nullptr;

		delete temp;
		return value;
	}

	void push(const T& d)
	{
		queueNode* newNode = new queueNode(d);

		if (end == nullptr) {
			front = end = newNode;
		}
		else {
			end->next = newNode;
			end = newNode;
		}
	}

	bool isEmpty()
	{
		return front == nullptr;
	}

	int getSize()
	{
		queueNode* looper = front;
		int counter = 0;
		while (looper != nullptr)
		{
			looper = looper->next;
			counter++;
		}
		return counter;
	}

	T peek()
	{
		if (front == nullptr)
			throw out_of_range("Queue empty");

		return front->data;
	}


private:
	struct queueNode
	{
		T data;
		queueNode* next;
		queueNode(const T& d, queueNode* n = nullptr)
			: data(d), next(n)
		{}
	};

	queueNode* front = nullptr; // to be poped
	queueNode* end = nullptr; // just added
};

int precedence(char op)
{
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	return 0;
}
int applyOp(int a, int b, char op) 
{
	switch (op)
	{
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/':
		if (b == 0)
			throw logic_error("Division by zero");
		return a / b;
	}
	throw logic_error("Unknown operator");
}
void infixToPRN(const string& text, queue<string>& output)
{
	
	linkedStack<char> ops;

	for (size_t i = 0; i < text.size(); )
	{
		char c = text[i];

		if (isspace(c))
		{
			i++;
			continue;
		}

		if (isdigit(c))
		{
			string num;
			while (i < text.size() && isdigit(text[i]))
			{
				num += text[i];
				i++;
			}
			output.push(num);
			continue;
		}

		//---------------------------negative numbers-------------------------------------
		if (c == '-' && (i == 0 || text[i - 1] == '(' || strchr("+-*/", text[i - 1])))
		{
			string num = "-";
			i++;
			while (i < text.size() && isdigit(text[i]))
			{
				num += text[i];
				i++;
			}

			output.push(num);
			continue;
		}

		//----------------------------parentheses--------------------------
		if (c == '(')
		{
			ops.push(c);
			i++;
			continue;
		}
		if (c == ')')
		{
			while (!ops.isEmpty() && ops.top() != '(' && precedence(ops.top()) >= precedence(c))
				output.push(string(1, ops.pop()));

			ops.pop();
			i++;
			continue;
		}
		//-------------------------------operators-----------------------------------
		if (strchr("+-*/", c))
		{
			while (!ops.isEmpty() && precedence(ops.top()) >= precedence(c))
				output.push(string(1, ops.pop()));

			ops.push(c);
			i++;
			continue;
		}
		throw logic_error("Invalid input\n");
	}

	//dump remaining operators
	while (!ops.isEmpty())
		output.push(string(1, ops.pop()));

}
int evalRPN(queue<string>& rpn)
{
	linkedStack<int> st;

	while (!rpn.isEmpty())
	{
		string token = rpn.pop();

		//-------------number----------------
		if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-'))
		{
			st.push(stoi(token));
			continue;
		}

		//--------------operator----------------
		int b = st.pop();
		int a = st.pop();

		st.push(applyOp(a, b, token[0]));
	}

	return st.pop();
}

int calculate(const string& text)
{
	queue<string> output;
	infixToPRN(text, output);
	return evalRPN(output);
}

int main()
{
	string text = "2+3-0*4/2";
	
	cout << calculate(text);
}

