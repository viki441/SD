#pragma once
#include "MyVector.h"
#include "ArrayBasedQueue.h"
#include <stdexcept>

class Graph 
{
public:
    Graph(int numVertices = 0);

    void addVertex();
    void addMultipleVertices(int count);
    void addEdge(int u, int v, int w);
    void removeEdge(int u, int v);
    void removeVertex(int u);
    int verticesCount() const;
    void clear();

private:
    struct Edge
    {
        int v;
        int w;
        Edge() : v(-1), w(0) {}
        Edge(int vertex, int weight) : v(vertex), w(weight) {}
    };
    MyVector<MyVector<Edge>> adj;


public: 
    const MyVector<Edge>& getNeighbours(int vertex) const;
};
