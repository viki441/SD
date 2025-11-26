#include <stdexcept>
#include <iostream>

using namespace std;

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
int main()
{
	
}
