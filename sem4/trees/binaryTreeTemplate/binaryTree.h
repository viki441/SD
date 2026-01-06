#pragma once
#include "MyString.h"
#include <stdexcept>

class BinaryTree 
{

public:
    BinaryTree();
    BinaryTree(const BinaryTree& other);
    BinaryTree& operator=(const BinaryTree& other);
    BinaryTree(BinaryTree&& other) noexcept;
    BinaryTree& operator=(BinaryTree&& other) noexcept;
    ~BinaryTree();

    void readFromString(const MyString& s);

    friend void countApplesAndTime(const BinaryTree& tree, int& apples, int& time);

private:

    struct Node
    {
        int data;
        Node* left;
        Node* right;
        Node(int val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root;
    size_t treeSize;



public:
    Node* getRoot() const { return root; }


private:

    Node* parseNode(const MyString& s, size_t& pos);
    void skipWhiteSpaces(const MyString& s, size_t& pos);
    Node* clone(Node* node) const;
    void clear(Node*& node);
    size_t countNodes(Node* node) const;
};


