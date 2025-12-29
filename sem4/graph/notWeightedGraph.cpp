#include <iostream>
#include <vector>
#include <queue>
#include <stdexcept>
#include <stack>

using namespace std;

//template <typename T>
class Graph 
{
private:

	int n;
	vector<vector<int>> adj;
	bool isOrientated;

public:

	Graph(int n, bool isOrientated)
		:n(n), isOrientated(isOrientated), adj(n, vector<int>())
	{}


//------------------------------ADD--------------------------------------------
	

	//addVertex ---> pravi slednoto:
	/*
		0:[1,2]
		1:[2]
		2:[3,4]
		3:[] <- dobavq nov podlist
	*/

	//u -> ind of the list u add things to
	//v -> ind of the list you add to the u
	void addEdge(int u, int v)
	{
		if (u >= adj.size() || v >= adj.size())
			throw out_of_range("No existing subVector\n");

		adj[u].push_back(v);
		
		
		if (!isOrientated)
			adj[v].push_back(u);
	}

	void addVertex()
	{
		// dobavq prazen list
		adj.push_back(std::vector<int>{});
	}

	void addMultipleVertices(int count)
	{
		for(int i = 0; i < count; i++)
			adj.push_back(std::vector<int>{});
	}


//--------------------------REMOVE----------------------------------------------

	void removeEdge(int u, int v)
	{
		if (u >= adj.size() || v >= adj.size())
			throw out_of_range("SubVector does not exist\n");

		adj[u].erase(
			remove(adj[u].begin(), adj[u].end(), v),
			adj[u].end()
		);

		if(isOrientated)
			adj[v].erase(
				remove(adj[v].begin(), adj[v].end(), u),
				adj[v].end()
			);

	}

	//v -> ind of the list you need to remove, this time from each other existing list
	void removeVertex(int v)
	{
		if (v >= adj.size())
			throw out_of_range("SubVector is not found\n");

		//one adjacency list
		for (auto &nbrs : adj)
		{
			//mind you, this is for each
				nbrs.erase(
					remove(nbrs.begin(), nbrs.end(), v),
					nbrs.end()
				);

				for (int& x : nbrs)
					if (x > v) --x;
		}
		adj.erase(adj.begin() + v);
	}



//------------------------------BFS------------------------------------
private:

	void bfs(int start)
	{
		cout << "Breadth first\n";
		queue<int> q;
		q.push(start);
		cout << "Level 0:" << endl;
		cout << start << endl;
		vector<bool> visited(adj.size(), false);
		visited[start] = true;
		int counter = 0;

		while (!q.empty())
		{
			int curr = q.front();
			q.pop();
			counter++;
			cout << "Level " << counter << "neighbours" << endl;
			for (int neighbour : adj[curr])
			{
				if (!visited[neighbour])
				{
					visited[neighbour] = true;
					cout << neighbour << endl;
				}
			}
		}
	}

	void dfs(int start)
	{
		cout << "Depth first\n";

		stack<int> st;
		vector<bool> visited(adj.size(), false);

		st.push(start);
		while (!st.empty())
		{
			int curr = st.top();
			st.pop();
			if (visited[curr])
				continue;

			visited[curr] = true;
			cout << curr << endl;
			for (int neighbour : adj[curr])
			{
				if (!visited[neighbour])
					st.push(neighbour);
			}
		}


		//maybe?
		auto isDisconnected = find(visited.begin(), visited.end(), false);
		if (isDisconnected != visited.end())
			cout << "you have reached an disconnected part of the graph, because it is oriented. Try another number\n";
	}


public:

	int shortestDistance(int start, int end)
	{
		if (start == end)
			return 0;

		struct vertexAndDistance
		{
			int vertex;
			int dist;
		};
		queue<vertexAndDistance> vertexQueue;

		vector<bool> visited(adj.size(), false);

		vertexQueue.push({ start, 0 });
		visited[start] = true;

		while (!vertexQueue.empty())
		{
			vertexAndDistance curr = vertexQueue.front();
			vertexQueue.pop();

			if (curr.vertex == end)
				return curr.dist;

			//explore neighbours
			for (int neighbour : adj[curr.vertex])
			{
				if (!visited[neighbour])
				{
					visited[neighbour] = true;
					vertexQueue.push({ neighbour, curr.dist + 1 });
				}
			}
		}
		return -1;
	}


//------------------------------OTHERS-------------------------------
	void printBreadthFirst(int start)
	{
		bfs(start);
	}
	void printDepthFirst(int start)
	{
		dfs(start);
	}

	void clear()
	{
		adj.clear();
	}
};

int main()
{
	Graph g1 = { 5, true};
	g1.addMultipleVertices(3);

	g1.addEdge(0, 1);
	g1.addEdge(0, 2);
	g1.addEdge(0, 4);
	g1.addEdge(0, 5);
	g1.addEdge(2, 3);
	g1.addEdge(2, 4);
	g1.addEdge(4, 6);
	g1.addEdge(5, 6);
	g1.addEdge(5, 7);
	g1.addEdge(6, 7);

	g1.printDepthFirst(5);


}
