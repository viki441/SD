#include "Graph.h"

Graph::Graph(int numVertices)
    : n(numVertices), adj(numVertices)
{
    for (int i = 0; i < n; i++)
        adj[i] = MyVector<Edge>();
}

void Graph::addVertex() {
    adj.push_back(MyVector<Edge>());
    n++;
}

void Graph::addMultipleVertices(int count) {
    for (int i = 0; i < count; i++)
        addVertex();
}

void Graph::addEdge(int u, int v, int w) {
    if (u < 0 || u >= n || v < 0 || v >= n)
        throw std::out_of_range("Vertex does not exist");

    adj[u].push_back(Edge(v, w));
    adj[v].push_back(Edge(u, w)); // undirected
}

void Graph::removeEdge(int u, int v) {
    if (u < 0 || u >= n || v < 0 || v >= n)
        throw std::out_of_range("Vertex does not exist");

    auto removeFrom = [](MyVector<Edge>& vec, int vertex) {
        MyVector<Edge> newVec;
        for (size_t i = 0; i < vec.size(); i++)
            if (vec[i].v != vertex)
                newVec.push_back(vec[i]);
        vec = std::move(newVec);
        };

    removeFrom(adj[u], v);
    removeFrom(adj[v], u);
}

void Graph::removeVertex(int u) {
    if (u < 0 || u >= n)
        throw std::out_of_range("Vertex does not exist");

    // Remove edges to u
    for (int i = 0; i < n; i++) {
        if (i == u) continue;
        MyVector<Edge> newVec;
        for (size_t j = 0; j < adj[i].size(); j++) {
            int v = adj[i][j].v;
            int w = adj[i][j].w;
            if (v == u) continue;
            if (v > u) v--;
            newVec.push_back(Edge(v, w));
        }
        adj[i] = std::move(newVec);
    }

    // Remove vertex itself
    for (int i = u; i + 1 < n; i++)
        adj[i] = std::move(adj[i + 1]);
    adj.pop_back();
    n--;
}

int Graph::verticesCount() const { return n; }

const MyVector<Graph::Edge>& Graph::getNeighbours(int vertex) const {
    if (vertex < 0 || vertex >= n)
        throw std::out_of_range("Vertex does not exist");
    return adj[vertex];
}

void Graph::clear() {
    adj.clear();
    n = 0;
}
