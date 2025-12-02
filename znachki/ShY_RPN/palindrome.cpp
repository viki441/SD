#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>
#include <list>
#include <stdexcept>

using namespace std;
char toLower(const char ch)
{
	return ch - 'A' + 'a';
}


bool isPalindrome(const string& text)
{
	stack<char> stack;
	for (char ch : text)
	{
		if (islower(ch))
			stack.push(ch);

		else if (isupper(ch))
		{
			char top = stack.top();
			if (toLower(ch) == top)
				stack.pop();

			else
				throw invalid_argument("Invalid structure of string\n");
		}

		else
			throw invalid_argument("Invalid character is string\n");

	}
	if (stack.empty())
		return true;
	return false;
}


int main()
{
	string text = "ghjkKJH";
	cout << boolalpha << isPalindrome(text);
}
