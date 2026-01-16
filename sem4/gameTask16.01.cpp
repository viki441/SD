#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <stdexcept>

/*
UNFINISHED
*/


using namespace std;
//tipove tiles
enum class TileType 
{
    MONSTER = 0, BLESSING, ITEM, PLAYER, WALL, ROAD
};

// vertex id this edge points to
struct Entity 
{
    int id; 
};


struct HashNode 
{
    TileType key; //what the "bucket is labled" 
    std::vector<Entity> value; // values
    HashNode* next; // ->[new bucket]

    HashNode(TileType k, Entity e)
        : key(k), value{ e }, next(nullptr) {
    }
};

class HashMap 
{
private:

    static constexpr size_t BUCKET_COUNT = 50;
    HashNode* buckets[BUCKET_COUNT]{};

public:
    HashMap() = default;

    ~HashMap() { clear(); }

    HashMap(const HashMap&) = delete;
    HashMap& operator=(const HashMap&) = delete;


    //MOVE
    HashMap(HashMap&& other) noexcept 
    {
        for (size_t i = 0; i < BUCKET_COUNT; ++i) 
        {
            buckets[i] = other.buckets[i];
            other.buckets[i] = nullptr;
        }
    }
    HashMap& operator=(HashMap&& other) noexcept 
    {
        if (this != &other) 
        {
            clear();
            for (size_t i = 0; i < BUCKET_COUNT; ++i) 
            {
                buckets[i] = other.buckets[i];
                other.buckets[i] = nullptr;
            }
        }
        return *this;
    }

    void clear() 
    {
        for (auto& head : buckets) 
        {
            while (head) 
            {
                HashNode* tmp = head;
                head = head->next;
                delete tmp;
            }
        }
    }

    size_t hash(TileType key) const 
    {
        return static_cast<size_t>(key) % BUCKET_COUNT;
    }

    void insert(TileType key, Entity e) 
    {
        size_t idx = hash(key);
        HashNode* node = buckets[idx];

        while (node) 
        {
            if (node->key == key) 
            {
                node->value.push_back(e);
                return;
            }
            node = node->next;
        }

        auto* newNode = new HashNode(key, e);
        newNode->next = buckets[idx];
        buckets[idx] = newNode;
    }

    std::vector<Entity>* find(TileType key) 
    {
        size_t idx = hash(key);
        HashNode* node = buckets[idx];
        while (node) 
        {
            if (node->key == key) return &node->value;
            node = node->next;
        }
        return nullptr;
    }

    //remove entity pointing to vertexId under key
    bool remove(TileType key, int vertexId) 
    {
        size_t idx = hash(key);
        HashNode* node = buckets[idx];
        HashNode* prev = nullptr;

        while (node) 
        {
            if (node->key == key) 
            {
                auto& vec = node->value;
                vec.erase(std::remove_if(vec.begin(), vec.end(),
                    [vertexId](const Entity& e) { return e.id == vertexId; }),
                    vec.end());

                if (vec.empty()) 
                {
                    if (prev) prev->next = node->next;
                    else buckets[idx] = node->next;
                    delete node;
                }
                return true;
            }
            prev = node;
            node = node->next;
        }
        return false;
    }

    
    void remapAfterVertexRemoval(int v) 
    {
        for (size_t i = 0; i < BUCKET_COUNT; ++i) 
        {
            HashNode* node = buckets[i];
            HashNode* prev = nullptr;

            while (node) 
            {
                auto& vec = node->value;

                // Remove entities pointing to v
                vec.erase(std::remove_if(vec.begin(), vec.end(),
                    [v](const Entity& e) { return e.id == v; }),
                    vec.end());

                // Decrement ids greater than v
                for (auto& e : vec) if (e.id > v) --e.id;

                // If vector became empty, remove node
                HashNode* nextNode = node->next;
                if (vec.empty()) {
                    if (prev) prev->next = nextNode;
                    else buckets[i] = nextNode;
                    delete node;
                }
                else {
                    prev = node;
                }

                node = nextNode;
            }
        }
    }

    std::vector<int> allNeighbors() const {
        std::vector<int> neighbors;
        for (size_t i = 0; i < BUCKET_COUNT; ++i) {
            HashNode* node = buckets[i];
            while (node) {
                for (const auto& e : node->value)
                    neighbors.push_back(e.id);
                node = node->next;
            }
        }
        return neighbors;
    }
};

class Graph 
{
private:
    std::vector<HashMap> adj;
    int currPos = 0;

public:

    //-----------------------------------------GRAPH RELATED IMPL
    Graph(int nodes = 0) : adj(nodes) {}
    
    void addVertex() { adj.emplace_back(); }

    void addMultipleVertices(int count) {
        for (int i = 0; i < count; ++i)
            adj.emplace_back();
    }

    void addEdge(int u, TileType type, int v) {
        if (u >= adj.size() || v >= adj.size())
            throw std::out_of_range("Vertex out of range");
        adj[u].insert(type, Entity{ v });
        adj[v].insert(type, Entity{ u }); 
    }

    TileType getTileType(int t)
    {
        switch (t)
        {
        case 0: return TileType::MONSTER; break;
        case 1: return TileType::BLESSING; break;
        case 2: return TileType::ITEM; break;
        case 3: return TileType::PLAYER; break;
        case 4: return TileType::WALL; break;
        case 5: return TileType::ROAD; break;

        default:
            throw invalid_argument("invalid type\n");
        }
    }

    void buildGraph(int size)
    {
        cout << "TABLE OF TILES:\n  MONSTER = 0, BLESSING = 1, ITEM = 2, PLAYER = 3, WALL = 4, ROAD = 5\n";
        for (int i = 0; i < size; i++)
        {
            cout << "Enter vertex index, type of tile and ind of vertex to be connected to.\n";
            int u, t, v;
            TileType tp = getTileType(t);
            addEdge(u, tp, v);
        }
    }
   
    void removeEdge(int u, int v, TileType type) {
        if (u >= adj.size() || v >= adj.size())
            throw std::out_of_range("Vertex out of range");
        adj[u].remove(type, v);
        adj[v].remove(type, u);
    }

    void removeVertex(int v) {
        if (v >= adj.size())
            throw std::out_of_range("Vertex not found");
        for (auto& map : adj)
            map.remapAfterVertexRemoval(v);
        adj.erase(adj.begin() + v);
    }

    //TileType



    void bfs(int start) const 
    {
        if (start >= adj.size())
            throw std::out_of_range("Start vertex out of range");

        std::vector<bool> visited(adj.size(), false);
        std::queue<int> q;
        visited[start] = true;
        q.push(start);

        while (!q.empty()) 
        {
            int u = q.front(); 
            q.pop();
            
            TileType tp = getTileType(u);
           // if( ==  )



            std::cout << "Visiting: " << u << std::endl;
            for (int v : adj[u].allNeighbors()) 
            {
                if (!visited[v]) 
                {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    int size() const { return adj.size(); }

    void findNearestItems()
    {
        cout << "Three shortest distances to some of the parts\n";
        bfs(currPos);

    }
};

int main() 
{
    Graph g;
    cout << "Enter map size: MAX SIZE: 50 nxn\n";
    int size;
    cin >> size;
    g.addMultipleVertices(size);
    g.buildGraph(size);


    g.findNearestItems();
    


 
}
