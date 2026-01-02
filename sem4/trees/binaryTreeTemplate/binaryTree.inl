#pragma once
#include "BinaryTree.h"


//-----------------Node-----------------
template<typename T>
BinaryTree<T>::Node::Node(const T& value) : data(value), left(nullptr), right(nullptr) {}

//-----------------Constructors & Big-6-----------------
template<typename T>
BinaryTree<T>::BinaryTree() : root(nullptr), treeSize(0) {}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& other) : root(clone(other.root)), treeSize(other.treeSize) {}

template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree& other) {
    if (this != &other) {
        clear(root);
        root = clone(other.root);
        treeSize = other.treeSize;
    }
    return *this;
}

template<typename T>
BinaryTree<T>::BinaryTree(BinaryTree&& other) noexcept : root(other.root), treeSize(other.treeSize) {
    other.root = nullptr; other.treeSize = 0;
}

template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(BinaryTree&& other) noexcept {
    if (this != &other) {
        clear(root);
        root = other.root;
        treeSize = other.treeSize;
        other.root = nullptr; other.treeSize = 0;
    }
    return *this;
}

template<typename T>
BinaryTree<T>::~BinaryTree() { clear(root); }

//-----------------Public Methods-----------------
template<typename T>
void BinaryTree<T>::insert(const T& value) { insertRec(root, value); }

template<typename T>
bool BinaryTree<T>::contains(const T& value) const { return containsRec(root, value); }

template<typename T>
bool BinaryTree<T>::remove(const T& value) { return removeRec(root, value); }

template<typename T>
bool BinaryTree<T>::isEmpty() const { return root == nullptr; }

template<typename T>
size_t BinaryTree<T>::getSize() const { return treeSize; }

template<typename T>
void BinaryTree<T>::printInOrder() const { printRec(root); std::cout << std::endl; }

template<typename T>
int BinaryTree<T>::getHeight() const { return findHeight(root); }

template<typename T>
int BinaryTree<T>::getDiameter() const { int dia = 0; findDiameter(root, dia); return dia; }

template<typename T>
int BinaryTree<T>::getLeafCount() const { return countLeaves(root); }

//-----------------Private Helpers-----------------
template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::clone(Node* node) const {
    if (!node) return nullptr;
    Node* newNode = new Node(node->data);
    newNode->left = clone(node->left);
    newNode->right = clone(node->right);
    return newNode;
}

template<typename T>
void BinaryTree<T>::clear(Node*& node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
    node = nullptr;
}

template<typename T>
void BinaryTree<T>::insertRec(Node*& node, const T& value) {
    if (!node) { node = new Node(value); ++treeSize; return; }
    if (value < node->data) insertRec(node->left, value);
    else if (value > node->data) insertRec(node->right, value);
}

template<typename T>
bool BinaryTree<T>::containsRec(Node* node, const T& value) const {
    if (!node) return false;
    if (value == node->data) return true;
    if (value < node->data) return containsRec(node->left, value);
    return containsRec(node->right, value);
}

template<typename T>
bool BinaryTree<T>::removeRec(Node*& node, const T& value) {
    if (!node) return false;

    if (value < node->data) return removeRec(node->left, value);
    if (value > node->data) return removeRec(node->right, value);

    Node* toDelete = node;
    if (!node->left) node = node->right;
    else if (!node->right) node = node->left;
    else {
        Node* minRight = extractMin(node->right);
        minRight->left = node->left;
        minRight->right = node->right;
        node = minRight;
    }

    delete toDelete;
    --treeSize;
    return true;
}

template<typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::extractMin(Node*& node) {
    if (!node->left) {
        Node* minNode = node;
        node = node->right;
        return minNode;
    }
    return extractMin(node->left);
}

template<typename T>
void BinaryTree<T>::printRec(Node* node) const {
    if (!node) return;
    printRec(node->left);
    std::cout << node->data << " ";
    printRec(node->right);
}

template<typename T>
int BinaryTree<T>::findHeight(Node* node) const {
    if (!node) return 0;
    return 1 + std::max(findHeight(node->left), findHeight(node->right));
}

template<typename T>
int BinaryTree<T>::findDiameter(Node* node, int& diameter) const {
    if (!node) return 0;
    int lh = findDiameter(node->left, diameter);
    int rh = findDiameter(node->right, diameter);
    diameter = std::max(diameter, lh + rh);
    return 1 + std::max(lh, rh);
}

template<typename T>
int BinaryTree<T>::countLeaves(Node* node) const {
    if (!node) return 0;
    if (!node->left && !node->right) return 1;
    return countLeaves(node->left) + countLeaves(node->right);
}


