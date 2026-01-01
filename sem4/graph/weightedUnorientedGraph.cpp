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
	vector<vector<pair<int, int>>> adj;


public:

	Graph(int n, bool isOrientated)
		:n(n), adj(n, vector<pair<int,int>>())
	{
	}


	//------------------------------ADD--------------------------------------------


	void addEdge(int u, int v, int w)
	{
		if (u >= adj.size() || v >= adj.size())
			throw out_of_range("No existing subVector\n");

		adj[u].push_back({ v, w });
		adj[v].push_back({ u, w });

	}

	void addVertex()
	{
		adj.push_back(std::vector<pair<int, int>>{});
	}

	void addMultipleVertices(int count)
	{
		for (int i = 0; i < count; i++)
			adj.push_back(std::vector<pair<int,int>>{});
	}


	//--------------------------REMOVE----------------------------------------------

	void removeEdge(int u, int v)
	{
		if (u >= adj.size() || v >= adj.size())
			throw out_of_range("SubVector does not exist\n");

		adj[u].erase(
			remove_if
			(
				adj[u].begin(), adj[u].end(), 
				[v](const pair<int, int>& p){return p.first == v; }
			),
			adj[u].end()
		);

		adj[v].erase(
			remove_if
			(
				adj[v].begin(), adj[v].end(),
				[u](const pair<int, int>& p) {return p.first == u; }
			),
			adj[v].end()
		);
		

	}

	//v -> ind of the list you need to remove, this time from each other existing list
	void removeVertex(int u)
	{
		if (u >= adj.size())
			throw out_of_range("SubVector is not found\n");

		for (auto& nbrs : adj)
		{
			nbrs.erase(
				remove_if
				(
					nbrs.begin(), nbrs.end(),
					[u](const pair<int, int>& p) {return p.first == u; }
				),
				nbrs.end()
			);

			for (pair<int, int>& p : nbrs)
				if (p.first > u) --p.first;
		}
		adj.erase(adj.begin() + u);
	}



	//------------------------------BFS------------------------------------
private:

	void bfs(int start)
	{
		cout << "Breadth first\n";
		queue<int> q;
		vector<bool> visited(adj.size(), false);

		cout << "Level 0:" << endl;
		cout << start << endl;


		q.push(start);
		visited[start] = true;
		int counter = 0;

		while (!q.empty())
		{
			int size = q.size();
			cout << "Level" << counter << endl;
			while (size--) // same as size != 0 combined with size-- afterwards
			{
				int u = q.front();
				q.pop();
				cout << u << endl;

				for (const pair<int, int>& edge: adj[u])
				{
					int v = edge.first;
					int w = edge.second;

					if (!visited[v])
					{
						visited[v] = true;
						q.push(v);
					}
				}
			}
			++counter;
		}

		auto isDisconnected = find(visited.begin(), visited.end(), false);
		if (isDisconnected != visited.end())
			cout << "Graph is not fully reachable from the chosen start vertex.\n";
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

			for (const pair<int, int>& edge : adj[curr])
			{
				int v = edge.first;

				if (!visited[v])
					st.push(v);
			}
		}


		auto isDisconnected = find(visited.begin(), visited.end(), false);
		if (isDisconnected != visited.end())
			cout << "Graph is not fully reachable from the chosen start vertex.\n";
	}


public:

	//za momenta ne mi vurshi rabota
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
			/*for (const pair<int, int>& neighbour : adj[curr.vertex])
			{
				if (!visited[neighbour])
				{
					visited[neighbour] = true;
					vertexQueue.push({ neighbour, curr.dist + 1 });
				}
			}*/
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
	Graph g1 = { 5, true };
	g1.addMultipleVertices(3);

	//g1.addEdge(0, 1);
	//g1.addEdge(0, 2);
	//g1.addEdge(0, 4);
	//g1.addEdge(0, 5);
	//g1.addEdge(2, 3);
	//g1.addEdge(2, 4);
	//g1.addEdge(4, 6);
	//g1.addEdge(5, 6);
	//g1.addEdge(5, 7);
	//g1.addEdge(6, 7);

	g1.printDepthFirst(5);


}
