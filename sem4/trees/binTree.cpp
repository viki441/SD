#include <iostream>

using namespace std;

template <typename T> 
class BinTree
{
private:

	struct Node
	{
		T data;
		Node* left;
		Node* right;
		
		Node(const T& value)
			:data(value), left(nullptr), right(nullptr)
		{}
	};

	Node* root = nullptr;
	size_t treeSize = 0;

public:
	//-----------------------------BIG6----------------------------------------------------------------
	BinTree()
		:root(nullptr), treeSize(0)
	{}

	BinTree(const BinTree* other)
		:root(nullptr), treeSize(0)
	{
		root = clone(other.root);
		treeSize = other.treeSize;
	}
	BinTree& operator=(const BinTree& other) 
	{
		if (this == &other) //protection against self assignment
			return *this;

		Node* newRoot = clone(other.root);
		clear(root);
		root = newRoot;
		treeSize = other.treeSize;

		return *this;
	}

	BinTree (BinTree&& other) noexcept
		:root(other.root), treeSize(other.treeSize)
	{
		other.root = nullptr;
		other.treeSize = 0;
	}
	BinTree& operator=(BinTree&& other) noexcept
	{
		if (this != &other)
		{
			clear(root);
			root = other.root;
			treeSize = other.treeSize;
			other.root = nullptr;
			other.treeSize = 0;
		}
		return *this;
	}

	~BinTree()
	{
		clear(root);
	}

	//---------------------------EMPTY------------------------------------------------
	bool isEmpty() const
	{
		return root == nullptr;
	}

	//---------------------------GETSIZE----------------------------------------------
	const size_t getSize() const
	{
		return treeSize;
	}

	//-------------------------ICR PUBLIC---------------------------------------------
	//ask for the naming 'init'
	void insert(const T& value)
	{
		insertRec(root, value);
	}

	bool contains(const T& value) const
	{
		return containsRec(root, value);
	}

	bool remove(Node*& root, const T& value)
	{
		return removeRec(root, value);
	}

	//-------------------------ADDITIONAL--------------------------------------------------
	void printInOrder() const
	{
		printRec(root);
		cout << endl;
	}

	const Node* getRoot() const
	{
		return root;
	}

	int getHeight()
	{
		return findHeight(root);
	}

	int getDepth()
	{
		return findDepth(root);
	}

	//-----------------------DYNAMIC IN THE TREE WAY----------------------------------
private:
	Node* clone(Node* root) //also known as copyFrom
	{
		if (!root)
			return nullptr;
		return new Node(root->data, clone(root->left), clone(root->right));
	}
	void clear(Node*& root)
	{
		if (!root)
			return;

		clear(root->left);
		clear(root->right);
		delete root;
		root = nullptr;
	}




	//-------------------------ICR PRIVATE-----------------------------------------------
private:
	void insertRec(Node*& root, const T& value)
	{
		if (!root)
		{
			root = new Node(value);
			treeSize++;
			return;
		}

		if (root->data > value)
			insertRec(root->left, value);
		else if (value > root->data)
			insertRec(root->right, value);

		return;
	}
	void insertIterative(const T& value)
	{
		if (!root)
		{
			root = new Node(value);
			treeSize++;
			return;
		}

		Node* curr = root;
		Node* parent = nullptr;

		while (curr)
		{
			parent = curr;

			if (curr->data > value)
				curr = curr->left;
			else if (value > curr->data)
				curr = curr->right;
			else
				return;
		}

		if (parent->data > value)
			parent->left = new Node(value);
		else
			parent->right = new Node(value);

		treeSize++;
	}


	bool containsRec(Node* root, const T& value)
	{
		if (!root)
			return false;

		if (root->data == value)
			return true;

		else if (root->data > value)
			containsRec(root->left, value);
		else
			containsRec(root->right, value);

	}
	bool containsIterative(const T& value)
	{
		Node* curr = root;
		while (curr)
		{
			if (curr->data == value)
				return true;
			else if (curr->data > value)
				curr = curr->left;
			else
				curr = curr->right;
		}
		return false;
	}

	bool removeRec(Node*& root, const T& value)
	{
		if (!root)
			return false;

		if (root->data > value)
			removeRec(root->left, value);

		else if(root->data < value)
			removeRec(root->right, value);
	
		//leaf, klon ili root
		else
		{
			Node* toDelete = root;

			//1. no left child
			if (!root->left)
				root = root->right;

			//2. no right child
			else if (!root->right)
				root = root->left;

			//3 both children
			else
			{
				Node* minRight = extractMin(root->right);
				minRight->left = root->left;
				minRight->right = root->right;
				root = minRight;
			}

			delete toDelete;
			--treeSize;
			return true;

		}
	}


	//----------------ADDITIONAL AND HELPERS-------------------------
	void printRec(Node* root) const
	{
		if (!root)
			return;
		printRec(root->left);
		cout << root->data << endl;
		printRec(root->right);

	}

	Node* extractMin(Node*& root)
	{
		if (!root)
			return nullptr;

		if (!root->left) // we find the minimum
		{
			Node* minNode = root;
			root = root->right;
			return minNode;
		}

		return extractMin(root->left);

	}

	int findHeight(Node*& root)
	{
		if (!root)
			return 0;

		int leftTree = findHeight(root->left);
		int rightTree = findHeight(root->right);

		return 1 + max(leftTree, rightTree);
	}

	int findDepth(Node*& root)
	{
		if (!root)
			return 0;
		return findHeight(root) - 1;
	}
	
	void findPath(Node*& root, const T& data)
	{
		
	}

};

int findDepth(const BinTree<int>& tree)
{
	int counter = 0;
	return counter;
}




int main()
{
	BinTree<int> t;
	t.insert(8);
	t.insert(3);
	t.insert(10);
	t.insert(1);
	t.insert(6);
	t.insert(14);
	t.printInOrder();
	cout << endl << t.getDepth() << endl << t.getHeight();	
}
