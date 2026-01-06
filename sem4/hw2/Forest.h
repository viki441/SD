#pragma once
#include "Graph.h"
#include "BinaryTree.h"
#include "MyVector.h"
#include "ArrayBasedQueue.h"

class Forest 
{
private:
    Graph graph;
    MyVector<BinaryTree> trees;

public:
    Forest() {};
    void addTree(const BinaryTree& tree);
    BinaryTree& getTree(int index);
    bool computeTotalApplesAndTime(int& totalApples, int& totalTime);

    Graph& getGraph() 
    { 
        return graph;
    }
};
