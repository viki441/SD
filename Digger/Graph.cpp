#include "Graph.h"
#include <queue>
#include <iostream>

Graph::Graph()
    : adj(ROWS, vector<int>(ROWS, 0))
{ 
}

void Graph::addVertex()
{
    adj.push_back(vector<int>(ROWS, 0));
}

void Graph::addMultipleVertices(int count)
{
    for (int i = 0; i < count; i++)
        addVertex();
}

void Graph::addEdge(int u, int v, int type)
{
    //type is special for a game, so only 0 means no connection, another number is still a connection
    size_t adjSize = verticesCount() / 2;

    if(isEdgeConnected(u,v)) return;

    if (u < 0 || u >= adjSize || v < 0 || v >= adjSize)
        throw std::out_of_range("Vertex does not exist");

    adj[u][v] = type;
    adj[v][u] = type;
}

bool Graph::isEdgeConnected(int u, int v)
{
    return adj[u][v];    
}

void Graph::removeEdge(int u, int v)
{
    size_t adjSize = verticesCount() / 2;
    if (u < 0 || u >= adjSize || v < 0 || v >= adjSize)
        throw out_of_range("Vertex does not exist");

    adj[u][v] = 0;
    adj[v][u] = 0;

}


void Graph::removeVertex(int u)
{
    //help
}

const int Graph::verticesCount() const
{
    return adj.size();
}

void Graph::bfs(int start)
{
    queue<int> q;
    vector<bool> visited(adj.size(), false);

    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
        int n = q.front();
        q.pop();

        for (int neighbour : adj[n])
        {
            if (!visited[neighbour])
            {
                visited[neighbour] = true;
                q.push(neighbour);

            }
        }
    }
    auto isDisconnected = find(visited.begin(), visited.end(), false);
    if (isDisconnected != visited.end())
        cout << "Graph contains disconnected vertecies\n";
    
}

void Graph::clear() 
{
    adj.clear();
}