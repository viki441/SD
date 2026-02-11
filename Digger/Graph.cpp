#include "Graph.h"
#include <queue>
#include <iostream>

//IMPLICIT

Graph::Graph()
    :walkable(ROWS* COLS, 0)
{}

int Graph::toId(int x, int y)
{
    return y * COLS + x;
}

void Graph::toXY(int id, int& x, int& y)
{
    x = id % COLS;
    y = id / COLS;
}

bool Graph::isValidPos(int x, int y)
{
    return x >= 0 && x < COLS && y >= 0 && y < ROWS;

}


bool Graph::isWalkable(int x, int y) 
{


    return walkable[toId(x, y)];
}


void Graph::setWalkable(int x, int y, bool value)
{
    walkable[toId(x, y)] = value;
}

void Graph::findNeighbors(int id, vector<int>& out) 
{
    out.clear();

    int x,y;
    toXY(id, x, y);

    const int dx[4] = { -1,1,0,0 };
    const int dy[4] = { 0,0,-1,1 };

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (isValidPos(nx, ny) && isWalkable(nx, ny))
            out.push_back(toId(nx, ny));
    }

}


void Graph::bfs(int startId, int targetId, vector<int>& prev) 
{
    prev.assign(COLS * ROWS, 1);

    queue<int> q;
    q.push(startId);
    prev[startId] = startId;

    vector<int> neighbors;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        if (u == targetId)
            return;

        findNeighbors(u, neighbors);
        for (int v : neighbors)
        {
            if (prev[v] == -1)
            {
                prev[v] = u;
                q.push(v);
            }
        }

    }

    
}

void Graph::clear() 
{
    walkable.clear();
}