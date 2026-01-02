#pragma once
#include <iostream>
#include <algorithm>
#include <stdexcept>

template<typename T>
class BinaryTree {
private:
    struct Node {
        T data;
        Node* left = nullptr;
        Node* right = nullptr;

        Node(const T& value);
    };

    Node* root;
    size_t treeSize;

public:
    // Big-6
    BinaryTree();
    BinaryTree(const BinaryTree& other);
    BinaryTree& operator=(const BinaryTree& other);
    BinaryTree(BinaryTree&& other) noexcept;
    BinaryTree& operator=(BinaryTree&& other) noexcept;
    ~BinaryTree();

    // Core operations
    void insert(const T& value);
    bool contains(const T& value) const;
    bool remove(const T& value);

    bool isEmpty() const;
    size_t getSize() const;
    void printInOrder() const;

    int getHeight() const;
    int getDiameter() const;
    int getLeafCount() const;

private:
    // Helper functions
    Node* clone(Node* node) const;
    void clear(Node*& node);

    void insertRec(Node*& node, const T& value);
    bool containsRec(Node* node, const T& value) const;
    bool removeRec(Node*& node, const T& value);
    Node* extractMin(Node*& node);

    void printRec(Node* node) const;
    int findHeight(Node* node) const;
    int findDiameter(Node* node, int& diameter) const;
    int countLeaves(Node* node) const;
};

#include "BinaryTree.inl"
