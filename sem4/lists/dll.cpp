#include <iostream>
#include <stdexcept>

using namespace std;

template < typename T>
class DLL
{

private:
	struct Node
	{
		T data;
		Node* next;
		Node* prev;

		Node(const T& d, Node* n = nullptr, Node* p = nullptr)
			:data(d), next(n), prev(p)
		{
		}
	};
	Node* head;
	Node* tail;
	size_t size;


public:
	//----------------------------------BIG6-------------------------------------------------
	DLL()
		:head(nullptr), tail(nullptr), size(0)
	{
	}

	DLL(const DLL& other)
		:head(nullptr), tail(nullptr), size(0)
	{
		copyFrom(other);
	}
	DLL& operator=(const DLL& other)

	{
		if (this != &other)
		{
			clear();
			copyFrom(other);
		}
		return *this;

	}

	DLL(DLL& other) noexcept
		:head(other.head), tail(other.tail), size(other.size)
	{
		other.head = other.tail = nullptr;
		other.size = 0;
	}
	DLL& operator=(DLL&& other) noexcept
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

	~DLL()
	{
		clear();
	}

	//------------------------------------EMPTY------------------------------------------------
	const bool isEmpty() const
	{
		return size == 0;
	}

	//----------------------------------PUSH METHODS---------------------------------------------
	void pushFront(const T& value)
	{
		Node* newNode = new Node(value, head, nullptr);

		if (head)
			head->prev = newNode;

		else
			tail = newNode;

		head = newNode;
		size++;


	}
	void pushBack(const T& value)
	{
		Node* newNode = new Node{ value, nullptr, tail};

		if (tail)
			tail->next = newNode;

		else
			head = newNode;

		tail = newNode;
		size++;

	}
	//DONT USE
	void push(const T& value, const Node* prev)
	{
		Node* newNode = new Node(value, nullptr, nullptr);
		//if no
		if (isEmpty())
		{
			head = tail = newNode;
			size++;
			return;
		}

		//if first
		if (head == tail)
		{
			newNode->prev = head;
			head->next = newNode;
			tail = head;
			head = newNode;
			size++;
			return;
		}

		//if ok
		newNode->next = prev->next;
		prev->next->prev = newNode;

		newNode->prev = prev;
		size++;
	}


	//-----------------------------------POP METHODS----------------------------------------------
	T& popFront()
	{
		if (isEmpty())
			throw underflow_error("Can't delete from empty list\n");


		Node* temp = head;
		head = head->prev;

		if (head) head->prev = nullptr;
		else tail = nullptr;

		T data = temp->data;
		delete temp;
		size--;
		return data;
	}


	T& popBack()
	{
		if (isEmpty())
			throw underflow_error("Can't delete from empty list\n");

		Node* temp = tail;
		tail = tail->prev;
		if (tail)
			tail->next = nullptr;
		else
			head = nullptr;

		T data = temp->val;
		delete temp;
		size--;
		return data;
	}


	T pop(Node* prev)//->next
	{
		if (isEmpty())
			throw underflow_error("Can't delete from empty list\n");

		if (!prev->next) 
			throw invalid_argument("Invalid prev pointer\n");



		//you are deleting the head
		if (!prev->next->next)
		{
			T oldData = head->data;
			Node* temp = prev->next;
			head = prev;
			head->next = nullptr;
			delete temp;

			size--;
			return oldData;
		}

		//"pop sled"
		Node* temp = prev->next;
		T oldData = temp->data;

		prev->next = temp->next;
		temp->next->prev = temp->prev;
		size--;
		delete temp;
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

		//fast 
		if (head->data == value) return true;
		if (tail->data == value) return true;



		Node* curr = head;
		while (curr->data != value && !curr)
			curr = curr->next;
		if (!curr)
			return false;
		return true;
	}

	//-------------------------------------CONCAT-------------------------------------------------
	void concatLists(DLL& other)
	{
		if (other.isEmpty())
			return;

		if (isEmpty())
		{
			this->head = other.head;
			this->tail = other.tail;
		}
		else
		{
			this->tail->next = other.head;
			other.head->prev = this->tail;

			this->tail = other.tail;
		}
		size += other.size;

		//free the other
		other.head = other.tail = nullptr;
		other.size = 0;
	}

	//-------------------------------------FILTER-------------------------------------------------
	template <typename Func>
	void filter(Func func)
	{
		Node* curr = head;

		while (curr)
		{
			Node* nextNode = curr->next;

			if (!func(curr->data))
			{
				Node* temp = curr;
				
				//if first
				if (curr == head)
				{
					popFront();
				}	
				//if end
				else if(curr == tail)
				{
					popBack();
				}
				else
				{
					curr->prev->next = curr->next;
					curr->next->prev = curr->prev;
					delete curr;
					size--;
				}

				curr = nextNode;
			}
		}
	}


	//------------------------------------COMBINE-------------------------------------------------
	void combine(DLL& other)
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
		while (tail && tail->next)
			tail = tail->next;
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
		Node* curr = other.head;

		while (curr)
		{
			pushBack(curr->data);
			curr = curr->next;
		}
	}


	//-------------------------------------MERGE------------------------------------------------------
	Node* merge(Node* a, Node* b)
	{
		if (!a) return b;
		if (!b) return a;

		if (a->data <= b->data)
		{
			a->next = merge(a->next, b);
			a->next->prev = a;
			a->prev = nullptr;
			return a;
		}

		else
		{
			b->next = merge(a, b->next);
			b->next->prev = b;
			b->prev = nullptr;
			return b;
		}
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
		mid->prev = nullptr;

		Node* left = mergeSort(node);
		Node* right = mergeSort(mid);

		return merge(left, right);
	}

};

int main()
{
	DLL<int> list;
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