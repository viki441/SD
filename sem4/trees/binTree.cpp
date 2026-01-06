#include <iostream>
/*Implementation + zadachi*/
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
		{
		}
	};

	Node* root = nullptr;
	size_t treeSize = 0;

public:
	//-----------------------------BIG6----------------------------------------------------------------
	BinTree()
		:root(nullptr), treeSize(0)
	{
	}

	BinTree(const BinTree& other)
		:root(clone(other.root)), treeSize(other.size)
	{}

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

	BinTree(BinTree&& other) noexcept
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

	//--------------------------ZADACHI----------------------------------------
	//1
	bool getPathToNumber(const int number)
	{
		return findPath(number, 0, root);
	}
	//2
	int getLeafCount()
	{
		findLeafCount(root);
	}
	//3
	T getCommonRoot(const T& n1, const T& n2)
	{
		return findCommonRoot(root, n1, n2)->data;
	}
	//4
	int getDiameter()
	{
		return findDiameter(root, 0);
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
			return containsRec(root->left, value);
		else
			return containsRec(root->right, value);

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
			return removeRec(root->left, value);

		else if (root->data < value)
			return removeRec(root->right, value);

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

	//----------------------------ZADACHI-------------------------------------
	//1
	bool findPath(int number, int sum, Node* node)
	{

		if (!node)
			return false;

		std::cout << "Visiting node " << node->data
			<< " (current sum=" << sum << ")\n";

		sum += node->data;

		if (!node->left && !node->right)
		{
			std::cout << "Leaf reached. Final sum=" << sum << "\n";
			return (sum == number);
		}


		return findPath(number, sum, node->left) || findPath(number, sum, node->right);

	}
	//2
	int findLeafCount(Node* node)
	{
		if (!node)
			return 0;

		if (!node->left && !node->right)
			return node->data;

		return findLeafCount(node->left) + findLeafCount(node->right);


	}
	//3
	Node* findCommonRoot(Node* node, const T& n1, const T& n2)
	{
		if (!node)
			return nullptr;

		if (node->data == n1 || node->data == n2)
			return node;

		Node* left = findCommonRoot(node->left, n1, n2);
		Node* right = findCommonRoot(node->right, n1, n2);

		//if n1 is on one side and n2 is on the other side
		if (left && right)
			return node;

		return left ? left : right;

	}
	//4
	
	int findDiameter(Node* node, int& diameter)
	{
		if (!node)
			return 0;
		int leftHeight = findDiameter(node->left, diameter);
		int rightHeight = findDiameter(node->right, diameter);

		diameter = max(diameter, leftHeight + rightHeight);
		return 1 + max(leftHeight, rightHeight);


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
	t.insert(10);
	t.insert(5);

	t.insert(2);
	t.insert(3);
	t.insert(20);
	t.insert(25);
	t.insert(21);


	cout << t.getPathToNumber(4) << endl;
	cout << t.getCommonRoot(2, 3) << endl;

	cout << t.getDepth() << endl;

}
