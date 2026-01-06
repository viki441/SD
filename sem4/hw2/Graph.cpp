#include "Graph.h"



Graph::Graph(int numVertices)
    :  adj(numVertices)
{
    for (int i = 0; i < numVertices; i++)
        adj[i] = MyVector<Edge>();
}

void Graph::addVertex() 
{
    adj.push_back(MyVector<Edge>());
}

void Graph::addMultipleVertices(int count) 
{
    for (int i = 0; i < count; i++)
        addVertex();
}

void Graph::addEdge(int u, int v, int w) 
{
    size_t adjSize = verticesCount() / 2;

    if (u < 0 || u >= adjSize || v < 0 || v >= adjSize)
        throw std::out_of_range("Vertex does not exist");

    adj[u].push_back(Edge(v, w));
    adj[v].push_back(Edge(u, w));
}

void Graph::removeEdge(int u, int v) 
{
    size_t adjSize = verticesCount() / 2;
    if (u < 0 || u >= adjSize || v < 0 || v >= adjSize)
        throw std::out_of_range("Vertex does not exist");

    auto removeFrom = [](MyVector<Edge>& vec, int vertex) 
        {
        MyVector<Edge> newVec;
        for (size_t i = 0; i < vec.size(); i++)
            if (vec[i].v != vertex)
                newVec.push_back(vec[i]);
        vec = std::move(newVec);
        };

    removeFrom(adj[u], v);
    removeFrom(adj[v], u);
}



void Graph::removeVertex(int u) 
{
    size_t adjSize = verticesCount() / 2;
    if (u < 0 || u >= adjSize)
        throw std::out_of_range("Vertex does not exist");

    for (int i = 0; i < adjSize; i++) 
    {
        if (i == u) 
            continue;
        MyVector<Edge> newVec;
        for (size_t j = 0; j < adj[i].size(); j++) 
        {
            int v = adj[i][j].v;
            int w = adj[i][j].w;
            if (v == u) 
                continue;
            if (v > u) 
                v--;
            newVec.push_back(Edge(v, w));
        }
        adj[i] = std::move(newVec);
    }
    adjSize = verticesCount();
    for (int i = u; i + 1 < adjSize; i++)
        adj[i] = std::move(adj[i + 1]);
    adj.pop_back();
}

int Graph::verticesCount() const 
{ 
    return adj.size(); 
}



const MyVector<Graph::Edge>& Graph::getNeighbours(int vertex) const 
{
    if (vertex < 0 || vertex >= verticesCount())
        throw std::out_of_range("Vertex does not exist");
    return adj[vertex];
}


void Graph::clear() 
{
    adj.clear();
}
