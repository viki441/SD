#pragma once

#include <stdexcept>
#include <vector>

using namespace std;
class Graph
{
public:
    Graph();

    int toId(int x, int y);
    void toXY(int id, int& x, int& y) ;

    bool isValidPos(int x, int y);
    bool isWalkable(int x, int y);

    void setWalkable(int x, int y, bool value);
    

    void findNeighbors(int id, vector<int>& out);
    void bfs(int startId, int targetId, vector<int>& prev);
   
    void clear();

private:
    const int ROWS = 15;
    const int COLS = 10;

    vector<bool> walkable;
};