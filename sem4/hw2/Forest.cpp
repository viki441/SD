#include "Forest.h"

void Forest::addTree(const BinaryTree& tree) 
{
    trees.push_back(tree);
    graph.addVertex();
}

BinaryTree& Forest::getTree(int index) 
{
    if (index < 0 || index >= (int)trees.size())
        throw std::out_of_range("Tree index invalid");
    return trees[index];
}

bool Forest::computeTotalApplesAndTime(int& totalApples, int& totalTime) 
{
    if (graph.verticesCount() == 0) 
        return false;

    totalApples = 0;
    totalTime = 0;

    int n = graph.verticesCount();
    MyVector<bool> visited(n, false);

    ArrayBasedQueue<int> q;
    q.enqueue(0);
    visited[0] = true;

    while (!q.isEmpty()) 
    {
        int u = q.dequeue();
        int apples, time;
        
        countApplesAndTime(trees[u], apples, time);
        totalApples += apples;
        totalTime += time;

        const auto& neighbours = graph.getNeighbours(u);

        for (size_t i = 0; i < neighbours.size(); i++) 
        {
            int v = neighbours[i].v;
            if (!visited[v]){
                visited[v] = true;
                q.enqueue(v);
            }
        }
    }
    return true;
}
