#include "Algorithms.hpp"
#include "Graph.hpp"
#include <queue>
#include <limits>
#include <algorithm>
#include <stack>
using namespace ariel;
using namespace std;

const int INF = std::numeric_limits<int>::max();

int is_Connected(Graph &g);

bool BFS(Graph &g, int start, int end, vector<int> &path);
void dijsktra(Graph &g, int start, int end, vector<int> &path);
void bellmanFord(Graph &g, int start, int end, vector<int> &path);

bool DFS(Graph g, int v, vector<bool> &visited, vector<int> &path, vector<bool> &recStack, int parent, int &end);
void printCyclePath(const vector<int> &path, int end);
bool isCyclic(Graph &g);

bool hasNegativeCycle(Graph &graph, int src);

bool isBipartiteUtil(vector<vector<int>> &matrix, int src, vector<int> &color);

int Algorithms::isConnected(Graph &g)
{
    if (is_Connected(g) == 1)
    {
        // cout << "The graph is connected" << endl;
        return 1;
    }
    // cout << "The graph is not connected" << endl;
    return 0;
}

string Algorithms::shortestPath(Graph &g, int start, int end)
{
    if (start < 0 || start >= g.getMatrix().size() || end < 0 || end >= g.getMatrix().size()) // if the start or end vertex is invalid
    {
        // cout << "Invalid source or destination vertex" << endl;
        return "-1";
    }
    vector<int> path; // vector to store the shortest path
    path.clear();
    if (negativeCycle(g)) // if the graph contains negative cycle
    {
        // cout << "The graph contains negative cycle" << endl;
        return "-1";
    }

    if (g.getWithWeights() == false) // if the graph is without weights we use BFS algorithm
    {
        // cout<<"withWhights: "<< g.getWithWhights()<<endl;
        // cout<< "shortestPath using BFS"<<endl;
        BFS(g, start, end, path);
    }

    if (!g.getHasNegativeEdge()) // if the graph is without negative edges we use dijsktra algorithm
    {
        // cout<<"hasNegativeEdge: "<< g.getHasNegativeEdge()<<endl;
        // cout<< "shortestPath using dijsktra"<<endl;
        dijsktra(g, start, end, path);
    }

    if (g.getHasNegativeEdge()) // if the graph has negative edges we use bellman_ford algorithm
    {
        // cout<<"hasNegativeEdge: "<< g.getHasNegativeEdge()<<endl;
        // cout<< "shortestPath using bellman_ford"<<endl;
        bellmanFord(g, start, end, path);
    }
    string result;
    if (path.size() == 0)
    {
        // No path exists from start to end
        return "-1";
    }
    else
    {
        // cout << "The shortest path from " << start << " to " << end << " is: ";
        for (size_t i = 0; i < path.size() - 1; i++)
        {
            result += to_string(path[i]) + "->";
        }
        result += to_string(path[path.size() - 1]);
    }
    // cout << result << endl;
    return result;
}

int Algorithms::isContainsCycle(Graph &g)
{
    if (isCyclic(g))
    {
        // if the graph contains cycle we print the path in the function "isCyclic"
        return 1;
    }
    else
    {
        // cout << "The graph does not contain a cycle" << endl;
        return 0;
    }

    return 0;
}

string Algorithms::isBipartite(Graph &g)
{
    std::vector<std::vector<int>> matrix = g.getMatrix();
    size_t n = matrix.size();
    vector<int> color(n, -1); // -1 represents uncolored
    string result = "The graph is bipartite: A={";

    for (size_t i = 0; i < n; ++i)
    {
        if (color[i] == -1)
        { // If vertex is uncolored, it means it is not visited yet
            if (isBipartiteUtil(matrix, i, color) == false)
            {
                // If the graph is not bipartite, return false
                return "0";
            }
        }
    }
    // If graph is bipartite, divide vertices into two sets based on color
    vector<int> setA, setB;
    for (size_t i = 0; i < n; ++i)
    {
        if (color[i] == 0)
            setA.push_back(i);
        else
            setB.push_back(i);
    }

    for (size_t i = 0; i < setA.size(); ++i)
    {
        result += to_string(setA[i]);
        if (i != setA.size() - 1)
        {
            result += ", ";
        }
    }
    result += "}, B={";

    for (size_t i = 0; i < setB.size(); ++i)
    {
        result += to_string(setB[i]);
        if (i != setB.size() - 1)
        {
            result += ", ";
        }
    }
    result += "}";
    return result;
}

bool Algorithms::negativeCycle(Graph &g)
{
    for (size_t i = 0; i < g.getMatrix().size(); i++)
    {
        for (size_t j = 0; j < g.getMatrix().size(); j++)
        {
            if (g.getMatrix()[i][j] < 0)
            {
                if (hasNegativeCycle(g, i))
                {
                    // cout << "The graph contains negative cycle" << endl;
                    return true;
                }
            }
        }
    }
    return false;
}

int is_Connected(Graph &g)
{
    vector<int> path;
    // If the graph is directed, check connectivity between all pairs of vertices using BFS
    if (g.getIsDirected() == true)
    {
        for (int i = 0; i < g.getMatrix().size(); i++)
        {
            for (int j = 0; j < g.getMatrix().size(); j++)
            {
                if (BFS(g, i, j, path) == true)
                {
                    // cout << "The graph is connected" << endl;
                    return 1;
                }
            }
        }
        //  cout << "The graph is not connected" << endl;
        return 0;
    }
    // If the graph is undirected, check connectivity between two arbitrary vertices (0 and 1) using BFS
    else if (g.getIsDirected() == false)
    {
        if (BFS(g, 0, 1, path) == false)
        {
            // cout << "The graph is not connected" << endl;
            return 0;
        }
        else
        {
            // cout << "The graph is connected" << endl;
            return 1;
        }
        return 0;
    }
    return 0;
}

// Use for shorest path for a graph without weights and for isConnected function
bool BFS(Graph &g, int start, int end, vector<int> &path)
{
    const vector<vector<int>> &matrix = g.getMatrix();
    size_t n = matrix.size(); // Number of vertices in the graph

    vector<bool> visited(n, false); // Array to store visited vertices
    queue<int> q;                   // Queue to store vertices to visit
    vector<int> parent(n, -1);      // Array to store parent vertices in the shortest path tree

    visited[(size_t)start] = true; // Mark the start vertex as visited
    q.push(start);                 // Add the start vertex to the queue

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (size_t v = 0; v < n; v++)
        {
            if (matrix[(size_t)u][v] != 0 && !visited[v])
            {
                visited[v] = true;
                parent[v] = u;
                q.push(v);

                // Use for shortest path algorithm - graph without weights
                if (v == end) // Check if we reached the end vertex
                {
                    // Reconstruct the shortest path from end to start using parent array into vector path
                    int current = end;
                    while (current != start)
                    {
                        path.push_back(current);
                        current = parent[(size_t)current];
                    }
                    path.push_back(start);
                    reverse(path.begin(), path.end()); // Reverse to get path from start to end
                }
            }
        }
    }
    // Use for isConnected function
    //   check if all the vertices are visited
    for (size_t i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            return false;
        }
    }
    return true;
}

// Use for shorest path for a graph with weights and non negative edges
void dijsktra(Graph &g, int start, int end, vector<int> &path)
{
    const vector<vector<int>> &matrix = g.getMatrix();
    size_t n = matrix.size(); // Number of vertices in the graph

    const int INF = std::numeric_limits<int>::max(); // Define infinity for distance

    vector<int> dist(n, INF);  // Array to store shortest distances from src to each vertex
    vector<int> parent(n, -1); // Array to store parent vertices in the shortest path tree

    dist[(size_t)start] = 0;    // Distance from start to itself is 0
    parent[(size_t)start] = -1; // Parent of start is null
    // Create a priority queue to store vertices based on their distances
    priority_queue<int, vector<int>, greater<int>> pq;
    pq.push(start);

    while (!pq.empty())
    {
        int u = pq.top();
        pq.pop();

        for (size_t v = 0; v < n; v++)
        {
            if (matrix[(size_t)u][v] != 0)
            {
                int edge_weight = matrix[(size_t)u][v];
                int new_dist = dist[(size_t)u] + edge_weight;

                if (new_dist < dist[v])
                {
                    dist[v] = new_dist;
                    parent[v] = u;
                    pq.push(v);
                }
            }
        }
    }

    // Reconstruct the shortest path from end to start using the parent vector
    if (dist[(size_t)end] == INF)
    {
        // No path exists from start to end
        path.clear();
        return;
    }

    path.clear();
    int current = end;

    while (parent[(size_t)current] != -1)
    {
        path.push_back(current);
        current = parent[(size_t)current];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
}

// Function to perform Bellman-Ford algorithm and find the shortest path to a specified end vertex
void bellmanFord(Graph &graph, int src, int end, vector<int> &path)
{
    const vector<vector<int>> &matrix = graph.getMatrix();
    size_t n = matrix.size(); // Number of vertices in the graph

    const int INF = numeric_limits<int>::max(); // Define infinity for distance

    vector<int> dist(n, INF);  // Array to store shortest distances from src to each vertex
    vector<int> parent(n, -1); // Array to store parent vertices in the shortest path tree

    dist[(size_t)src] = 0; // Distance from src to itself is 0

    // Relax edges up to n - 1 times
    for (size_t count = 0; count < n - 1; count++)
    {
        for (size_t u = 0; u < n; u++)
        {
            for (size_t v = 0; v < n; v++)
            {
                if (matrix[u][v] != 0 && dist[u] != INF && dist[u] + matrix[u][v] < dist[v])
                {
                    dist[v] = dist[u] + matrix[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    // Reconstruct the shortest path from end to src using the parent vector
    if (dist[(size_t)end] == INF)
    {
        // No path exists from src to end
        path.clear();
        return;
    }

    path.clear();
    int current = end;
    path.push_back(end);
    while (current != src)
    {
        path.push_back(current);
        current = parent[(size_t)current];
    }
    path.push_back(src);
    reverse(path.begin(), path.end());
    path.pop_back();
}
// Function to detect cycles in the graph and print the cycle path
bool isCyclic(Graph &g)
{
    size_t n = g.getMatrix().size();
    vector<bool> visited(n, false);
    vector<bool> recStack(n, false);
    vector<int> path;
    int end = -1;
    bool cycle = false;

    for (size_t i = 0; i < n; ++i)
    {
        if (!visited[i])
        {

            if (DFS(g, i, visited, path, recStack, -1, end)) // use DFS algorithm to check if the graph contains cycle
            {
                cycle = true; // Cycle detected
            }
        }
    }
    if (cycle)
    {
        // Print the cycle path
        cout << "Cycle detected: ";
        bool found = false;
        for (int v : path)
        {
            if (v == end)
            {
                found = true;
            }
            if (found)
            {
                cout << v << "->";
            }
        }
        cout << end << endl;
    }

    return cycle; // No cycle found in the entire graph
}

// Function to perform DFS traversal and detect cycles in the graph
bool DFS(Graph g, int v, vector<bool> &visited, vector<int> &path, vector<bool> &recStack, int parent, int &end)
{
    visited[(size_t)v] = true;
    recStack[(size_t)v] = true;
    path.push_back(v);

    for (size_t i = 0; i < g.getMatrix().size(); ++i)
    {
        if (g.getMatrix()[(size_t)v][i] != 0)
        {
            if (!visited[i])
            {
                // Recursive DFS call
                if (DFS(g, i, visited, path, recStack, v, end))
                    return true;
            }
            else if (recStack[i] && i != parent)
            {
                end = i;
                // Cycle detected
                return true;
            }
        }
    }

    // Backtrack: Remove the vertex from the path and recursion stack
    path.pop_back();
    recStack[(size_t)v] = false;
    return false;
}

// this function is used to check if the graph is bipartite or not using BFS traversal
// The algorithm colors the vertices with two colors in such a way that
// no two adjacent vertices have the same color
// If the graph is bipartite, the function returns true
// Otherwise, it returns false
bool isBipartiteUtil(vector<vector<int>> &matrix, int src, vector<int> &color)
{
    queue<int> q;
    q.push(src);
    color[(size_t)src] = 0; // Color the source vertex with 0 (set A)

    // Perform BFS traversal
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (size_t v = 0; v < matrix[(size_t)u].size(); ++v)
        {
            if (matrix[(size_t)u][v] != 0)
            {
                if (color[v] == -1)
                {
                    // Color the adjacent vertex with a different color
                    color[v] = 1 - color[(size_t)u]; // if color[u] is 0, color[v] is 1, if color[u] is 1, color[v] is 0
                    q.push(v);
                }
                // If adjacent vertices have the same color, graph is not bipartite
                else if (color[v] == color[(size_t)u])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

// Function to check if the graph contains a negative cycle using Bellman-Ford algorithm
bool hasNegativeCycle(Graph &graph, int src)
{
    {
        const vector<vector<int>> &matrix = graph.getMatrix();
        size_t n = matrix.size(); // Number of vertices in the graph

        vector<int> dist(n, INF);  // Array to store shortest distances from src to each vertex
        vector<int> parent(n, -1); // Array to store parent vertices in the shortest path tree

        dist[(size_t)src] = 0; // Distance from src to itself is 0

        // Relax edges repeatedly to find shortest paths
        for (size_t count = 0; count < n - 1; count++)
        {
            for (size_t u = 0; u < n; u++)
            {
                for (size_t v = 0; v < n; v++)
                {
                    if (matrix[u][v] != 0 && dist[u] != INF && dist[u] + matrix[u][v] < dist[v])
                    {
                        dist[v] = dist[u] + matrix[u][v];
                        parent[v] = u;
                    }
                }
            }
        }

        // Check for negative cycles using an additional iteration
        for (size_t u = 0; u < n; u++)
        {
            for (size_t v = 0; v < n; v++)
            {
                if (matrix[u][v] != 0 && dist[u] != INF && dist[u] + matrix[u][v] < dist[v])
                {
                    // Negative cycle detected
                    return true;
                }
            }
        }
        return false;
    }
}
