#include <iostream>
#include <stdexcept>

using namespace std;

template < typename T>
class LinkedList
{

private:
	struct Node
	{
		T data;
		Node* next;

		Node(const T& d, Node* n = nullptr)
			:data(d), next(n)
		{}
	};
	Node* head;
	Node* tail;
	size_t size;


public:
	//----------------------------------BIG6-------------------------------------------------
	LinkedList()
		:head(nullptr), tail(nullptr), size(0)
	{}

	LinkedList(const LinkedList& other)
		:head(nullptr), tail(nullptr), size(0)
	{
		copyFrom(other);
	}
	LinkedList& operator=(const LinkedList& other)

	{
		if (this != &other)
		{
			clear();
			copyFrom(other);
		}
		return *this;

	}

	LinkedList(LinkedList& other) noexcept
		:head(other.head), tail(other.tail), size(other.size)
	{
		other.head = other.tail = nullptr;
		other.size = 0;
	}
	LinkedList& operator=(LinkedList&& other) noexcept
	{
		if (this != &other)
		{
			clear();
			head = other.head;
			tail = other.tail;
			size = other.size;
			other.head = other.tail = nullptr;
			other.size = 0;
		}
		return *this;
	}

	~LinkedList()
	{
		clear();
	}

	//------------------------------------EMPTY------------------------------------------------
	const bool isEmpty() const
	{
		return head == nullptr && tail == nullptr;
	}

	//----------------------------------PUSH METHODS---------------------------------------------
	void pushFront(const T& value) 
	{
		Node* newNode = new Node(value, head);
		head = newNode;
		if (!tail)
			tail = newNode;
		size++;
		
	}
	void pushBack(const T& value)
	{

		Node* newNode = new Node{ value, nullptr };

		//if the list is empty
		if (!head)
		{
			head = tail = newNode;
			size++;
			return;
		}

		//if there is a list
		tail->next = newNode;
		tail = newNode;
		size++;
	}
	//DONT USE
	void push(const T& value, const Node* prev)
	{
		Node* newNode = new Node(value, nullptr);
		//if no
		if (isEmpty())
		{
			head = tail = newNode;
			size++;
			return;
		}

		//if first
		if (prev == nullptr)
		{
			newNode->next = head;
			head = newNode;
			size++;
			return;
		}

		//if ok
		newNode->next = prev->next;
		prev->next = newNode;
		size++;

		//if last
		if (prev == tail)
			tail = newNode;
	}


	//-----------------------------------POP METHODS----------------------------------------------
	T& popFront()
	{
		if (isEmpty())
			throw underflow_error("Can't delete from empty list\n");

		Node* old = head;
		T oldData = old->data;

		head = head->next;
		delete old;

		if (!head)
			tail = nullptr;

		size--;
		return oldData;
		
	}
	//DONT USE
	T& popBack()
	{
		if(isEmpty())
			throw underflow_error("Can't delete from empty list\n");

		Node* old = tail;
		T oldData = old->data;

		//if one element
		if (head == tail)
		{
			head = nullptr;
			tail = nullptr;
			delete old;
			size--;
			return oldData;
		}

		Node* prev = head;
		while (prev->next != tail)
			prev = prev->next;

		prev->next = nullptr;
		tail = prev;
		delete old;
		size--;
		return oldData;

	}
	T pop(Node* prev)
	{
		if (isEmpty())
			throw underflow_error("Can't delete from empty list\n");

		if (!prev || !prev->next)
			throw invalid_argument("Invalid prev pointer\n");
	
		Node* old = prev->next;
		T oldData = old->data;
		
	
		prev->next = old->next;

		if(old == tail)
		{
			tail = prev;
		}
		size--;
		delete old;
		return oldData;
		
	}

	//------------------------------------GETTERS-------------------------------------------------
	const T getFront() const
	{
		return head->data;
	}
	const T getBack() const
	{
		return tail->data;
	}
	const size_t getSize() const
	{
		return size;
	}

	//-------------------------------------FIND---------------------------------------------------
	bool find(const T& value)
	{
		if (isEmpty())
			return false;
		else if (head == tail)
			return value == head->data;

		Node* curr = head;
		while (curr->data != value && !curr)
			curr = curr->next;
		if (!curr)
			return false;
		return true;
	}

	//-------------------------------------CONCAT-------------------------------------------------
	void concatLists(LinkedList& other)
	{
		if (!other.head)
			return;

		if (!this->head)
		{
			this->head = other.head;
			this->tail = other.tail;
		}
		else
		{
			this->tail->next = other.head;
			this->tail = other.tail;
		}
		
		other.head = other.tail = nullptr;
			
	}

	//-------------------------------------FILTER-------------------------------------------------
	template <typename Func>
	void filter(Func func)
	{
		Node* curr = head;
		Node* prev = nullptr;
			
		while (curr)
		{
			if (!func(curr->data))
			{
				Node* temp = curr;
				if (prev)
					prev->next = curr->next;
				else
					head = curr->next;

				if (curr == tail)
					tail = prev;

				curr = curr->next;
				delete temp;
			}
			else
			{
				prev = curr;
				curr = curr->next;

			}
		}
	}


	//------------------------------------COMBINE-------------------------------------------------
	void combine(LinkedList& other)
	{
		//concat and filter
		concatLists(other);
		sort();
	}


	//-------------------------------------PRINT--------------------------------------------------
	void printList() const
	{
		if (isEmpty())
		{
			cout << "Empty list\n";
			return;
		}
			
		Node* curr = head;
		while (curr)
		{
			cout << curr->data << " ";
			curr = curr->next;
		}
		cout << endl;
	}

	//--------------------------------------SORT---------------------------------------------------
	void sort()
	{
		head = mergeSort(head);

		//fix tail
		tail = head;
		if (tail)
		{
			while (tail->next)
				tail = tail->next;
		}
	}



private:
	//------------------------------------DYNAMIC-------------------------------------------------
	void clear()
	{
		while (!isEmpty())
			popFront();
	}
	void copyFrom(const Node* other)
	{
		if (!other.head)
		{
			head = tail = nullptr;
			return;
		}

		head = new Node(other.head->data, nullptr );

		Node* currNew = head;
		Node* currOld = other.head->next;

		while (currOld)
		{
			currNew->next = new Node( currOld->data, nullptr );
			currNew = currNew->next;
			currOld = currOld->next;
		}
		tail = currNew;
	}


	//-------------------------------------MERGE------------------------------------------------------
	Node* merge(Node* a, Node* b)
	{
		if (!a) return b;
		if (!b) return a;

		Node* result = nullptr;
		if (a->data <= b->data)
		{
			result = a;
			result->next = merge(a->next, b);
		}

		else
		{
			result = b;
			result->next = merge(a, b->next);
		}
		return result;
	}	
	Node* mergeSort(Node* node)
	{
		if (!node || !node->next)
			return node;

		Node* slow = node;
		Node* fast = node->next;

		while (fast && fast->next)
		{
			slow = slow->next;
			fast = fast->next->next;
		}

		Node* mid = slow->next;
		slow->next = nullptr;

		Node* left = mergeSort(node);
		Node* right = mergeSort(mid);

		return merge(left, right);
	}

};

int main()
{
	LinkedList<int> list;
	list.pushFront(3);
	list.pushBack(4);
	list.pushFront(1);
	list.pushBack(0);
	//list.printList();
	//cout << list.getFront() << endl << list.getBack() << endl;
	//list.popFront();
	//list.printList();

	//list.filter([](int x) {return x % 2 == 0; });
	
	
	list.sort();
	list.printList();


}
