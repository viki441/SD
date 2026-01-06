#include "BinaryTree.h"
#include <cctype>
#include <functional>

BinaryTree::BinaryTree() 
    : root(nullptr), treeSize(0) 
{}

BinaryTree::BinaryTree(const BinaryTree& other) 
    : root(clone(other.root)), treeSize(other.treeSize) 
{}

BinaryTree& BinaryTree::operator=(const BinaryTree& other) 
{
    if (this != &other) 
    {
        clear(root);
        root = clone(other.root);
        treeSize = other.treeSize;
    }
    return *this;
}

BinaryTree::BinaryTree(BinaryTree&& other) noexcept 
    : root(other.root), treeSize(other.treeSize) 
{
    other.root = nullptr;
    other.treeSize = 0;
}
BinaryTree& BinaryTree::operator=(BinaryTree&& other) noexcept 
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
BinaryTree::~BinaryTree() 
{
    clear(root); 
}





void BinaryTree::readFromString(const MyString& s) 
{
    size_t pos = 0;
    root = parseNode(s, pos);
    treeSize = countNodes(root);
}

BinaryTree::Node* BinaryTree::parseNode(const MyString& s, size_t& pos) 
{
    skipWhiteSpaces(s, pos);
    if (pos >= s.getSize()) 
        throw std::runtime_error("Unexpected end of input");

    if (s[pos] == 'x' || s[pos] == 'X') 
    {
        ++pos;
        return nullptr; 
    }
    if (s[pos] != '(')
        throw std::runtime_error("Expected '('");
    
    ++pos;
    skipWhiteSpaces(s, pos);

    bool negative = false;
    if (s[pos] == '-') 
    {
        negative = true; 
        ++pos; 
    }

    if (pos >= s.getSize() || !isdigit(s[pos]))
        throw std::runtime_error("Expected number");

    int value = 0;
    while (pos < s.getSize() && isdigit(s[pos])) 
    {
        value = value * 10 + (s[pos] - '0');
        ++pos; 
    }
    if (negative)
        value = -value;

    skipWhiteSpaces(s, pos);
    Node* left = parseNode(s, pos);
    skipWhiteSpaces(s, pos);
    Node* right = parseNode(s, pos);
    skipWhiteSpaces(s, pos);

    if (pos >= s.getSize() || s[pos] != ')') 
        throw std::runtime_error("Expected ')'");

    ++pos;

    Node* node = new Node(value);
    node->left = left;
    node->right = right;
    return node;
}

void BinaryTree::skipWhiteSpaces(const MyString& s, size_t& pos) 
{
    while (pos < s.getSize() && s[pos] == ' ')
        ++pos;
}



BinaryTree::Node* BinaryTree::clone(Node* node) const 
{
    if (!node) 
        return nullptr;
    Node* newNode = new Node(node->data);
    newNode->left = clone(node->left);
    newNode->right = clone(node->right);
    return newNode;
}


void BinaryTree::clear(Node*& node) 
{
    if (!node)
        return;
    clear(node->left);
    clear(node->right);
    delete node;
    node = nullptr;
}

size_t BinaryTree::countNodes(Node* node) const 
{
    if (!node) 
        return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

void countApplesAndTime(const BinaryTree& tree, int& apples, int& time)
{
    apples = 0;
    time = 0;

    std::function<void(BinaryTree::Node*, int&)> dfs = [&](BinaryTree::Node* node, int& localTime)
        {
            if (!node) 
                return;

            if (node->data > 0)
                apples += 1;

            if (node->left)
            {
                localTime += 1;
                dfs(node->left, localTime);
                localTime += 1;
            }
            if (node->right)
            {
                localTime += 1;
                dfs(node->right, localTime);
                localTime += 1;
            }
        };

    dfs(tree.root, time);
}
