#include "arrayBasedStack.h"
using namespace std;

int main()
{
	try 
	{
		arrayBasedStack<int> s(5);
        cout << "Is stack empty? " << s.isEmpty() << "\n";

        // Push some elements
        s.push(10);
        s.push(20);
        s.push(30);

        cout << "Top element: " << s.topElement() << "\n"; // 30
        cout << "Stack size: " << s.getSize() << "\n";

        // Pop elements
        cout << "Popped: " << s.pop() << "\n"; // 30
        cout << "New top: " << s.topElement() << "\n"; // 20

        // Clear the stack
        s.clearStack();
        cout << "After clear, is empty? " << s.isEmpty() << "\n";

    }
    catch (const exception& e) {
        cerr << "Exception: " << e.what() << "\n";
    
	}
}