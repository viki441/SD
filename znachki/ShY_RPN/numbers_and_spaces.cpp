#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>
#include <list>

using namespace std;
double applyOperation(char op, double first, double second)
{
    switch (op)
    {
    case '+': return first + second;
    case '-': return first - second;
    case '*': return first * second;
    case '/': return first / second;
    default:
        throw std::exception("...");
    }
}

// We reuse this function from the previous task
double evalReversePolish(const vector<string>& str)
{
    std::stack<double> st;
    for (const string& token : str)
    {
        if (std::isdigit(token[0]) || (token.size() > 1 && token[0] == '.'))
        {
            st.push(stod(token));
        }
        else
        {
            if (st.size() < 2)
            {
                throw std::exception("...");
            }

            double second = st.top();
            st.pop();
            double first = st.top();
            st.pop();

            st.push(applyOperation(token[0], first, second));
        }
    }

    if (st.size() != 1)
    {
        throw std::exception("...");
    }

    return st.top();
}

unsigned int getOperationPriority(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;

    case '*':
    case '/':
        return 2;

    case '(':
        return 0;

    default:
        throw std::exception("...");
    }
}

bool isPreceeding(char priorityOp, char op)
{
    return getOperationPriority(priorityOp) >= getOperationPriority(op);
}

double evaluateExpression(const std::string& str)
{

    std::stack<char> operations;
    vector<string> resultReversePolishNotaion;

    for (size_t i = 0; i < str.size(); i++)
    {
        char ch = str[i];

        if (isspace(ch))
        {
            continue;
        }
        else if (ch == '(')
        {
            operations.push(ch);
        }
        else if (ch == ')')
        {
            while (!operations.empty() && operations.top() != '(')
            {
                resultReversePolishNotaion.push_back(string(1,operations.top()));
                operations.pop();
            }

            if (operations.empty())
                throw std::exception("...");

            operations.pop();
        }
        else if (isdigit(ch) || (ch == '.' && i + 1 < str.size() && isdigit(str[i + 1])))
        {
            string numberStr;
            while (i < str.size() && (isdigit(str[i]) || str[i] == '.'))
            {
                numberStr.push_back(str[i]);
                i++;
            }
            i--;
            resultReversePolishNotaion.push_back(numberStr);
        }
        else
        {
            while (!operations.empty() && isPreceeding(operations.top(), ch))
            {
                resultReversePolishNotaion.push_back(string(1,operations.top()));
                operations.pop();
            }

            operations.push(ch);
        }
    }

    while (!operations.empty())
    {
        resultReversePolishNotaion.push_back(string(1,operations.top()));
        operations.pop();
    }
    return evalReversePolish(resultReversePolishNotaion);
}

int main()
{
    std::cout << evaluateExpression("(3.4 * 4.5  + 007 - 9)  /2");
}
