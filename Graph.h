#pragma once
#include "MyVector.h"
#include "ArrayBasedQueue.h"
#include "ArrayBasedStack.h"
#include <stdexcept>

class Graph {
public:
    struct Edge {
        int v;
        int w;
        Edge() : v(-1), w(0) {} // default constructor for MyVector
        Edge(int vertex, int weight) : v(vertex), w(weight) {}
    };

private:
    MyVector<MyVector<Edge>> adj;
    int n;

public:
    Graph(int numVertices = 0);

    void addVertex();
    void addMultipleVertices(int count);
    void addEdge(int u, int v, int w);
    void removeEdge(int u, int v);
    void removeVertex(int u);

    int verticesCount() const;
    const MyVector<Edge>& getNeighbours(int vertex) const;

    void clear();
};
