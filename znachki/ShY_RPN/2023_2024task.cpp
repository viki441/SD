#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>
#include <list>
#include <stdexcept>

using namespace std;
int applyOperation(const int first, const int second, const char op)
{
	switch (op)
	{
	case '+':
		return first + second;
	case '-':
		return first - second;
	case '*':
		return first * second;
	case '/':
		if (second == 0) throw logic_error("Can't divide by 0\n");
		return first / second;
	case '%':
		if (second == 0) throw logic_error("Divide by zero");
		return first % second;
	case '&':
		return first & second;
	case '|':
		return first | second;
	case '^':
		return first ^ second;
	default:
		throw invalid_argument("Invalid symbol\n");
	}
}

int evaluateExpression(const string& text)
{
	stack<int> stack;
	for (size_t i = 0; i < text.size(); i++)
	{
		char ch = text[i];
		if(isspace(ch))
			continue;

		//if number
		else if ( i < text.size() && isdigit(ch))
		{
			string number;
			while (isdigit(text[i]))
			{
				number.push_back(text[i]);
				i++;	
			}
			i--;
			stack.push(stoi(number));
		}

		//if true/false
		else if (text.compare(i, 4, "true") == 0)
		{
			stack.push(1);
			i += 3;
		}
		else if (text.compare(i, 5, "false") == 0)
		{
			stack.push(0);
			i += 4;
		}

		//if else
		else 
		{
			if (stack.size() < 2)
				throw invalid_argument("invalid symbol led to incorrect notation\n");

			int second = stack.top();
			stack.pop();
			int first = stack.top();
			stack.pop();

			stack.push(applyOperation(first, second, ch));
		}

	}

	if (stack.size() != 1)
		throw logic_error("Error in arguments\n");

	return stack.top();
	
}


int main()
{
	string text;

	while (getline(cin, text))
	{
    if (text == "exit")
		  break;
		try
		{
			cout << "Expression was: " << evaluateExpression(text) << endl;
		}
		catch (...)
		{
			cout << "error\n";
		}
	}
}
