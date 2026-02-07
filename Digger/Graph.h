#pragma once

#include <stdexcept>
#include <vector>

using namespace std;
class Graph
{
public:
    Graph();

    void addVertex();
    void addMultipleVertices(int count);

    void addEdge(int u, int v, int type);
    bool isEdgeConnected(int u, int v);



    void removeEdge(int u, int v);
    void removeVertex(int u);

    void bfs(int start);
    const int verticesCount() const;
    void clear();

private:
    const int ROWS = 15;
    const int COLS = 10;

    vector<vector<int>> adj;

public:
   
};