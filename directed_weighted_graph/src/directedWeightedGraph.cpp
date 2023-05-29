#include "../inc/directedWeightedGraph.h"
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>

using namespace std;

/**
 *  This function adds a node to the graph. 
 */
void DirectedWeightedGraph::addNode(int node) 
{
    adjacencyList[node] = vector<Edge>();
}

/**
 *  This function creates an edge between the source and the destination. 
*/
void DirectedWeightedGraph::addEdge(int source, int destination, int weight) 
{
    if (!isNodeExists(source) || !isNodeExists(destination))
    {
        return;
    }

    Edge edge;
    edge.destination = destination;
    edge.weight = weight;

    adjacencyList[source].push_back(edge);
}

/**
 *  This function updates the weight of the edge. 
*/
void DirectedWeightedGraph::setWeight(int source, int destination, int weight)
{
    if (!isNodeExists(source) || !isNodeExists(destination))
    {
        return;
    }

    for (auto& edge : adjacencyList[source]) 
    {
        if (edge.destination == destination) 
        {
            edge.weight = weight;
            break;
        }
    }
}

/**
 *  This function checks if node exists or not. 
*/
bool DirectedWeightedGraph::isNodeExists(int node) 
{
    return adjacencyList.find(node) != adjacencyList.end();
}

/**
 *  This function checks if there is an edge between nodes. 
*/
bool DirectedWeightedGraph::isEdgeExists(int source, int destination) 
{
    if (!isNodeExists(source))
    {
        return false;
    }

    for (const auto& edge : adjacencyList[source]) 
    {
        if (edge.destination == destination)
        {
            return true;
        }
    }

    return false;
}

/**
 *  This function returns the weight between nodes. 
*/
int DirectedWeightedGraph::getWeight(int source, int destination) 
{
    if (!isEdgeExists(source, destination))
    {
        return numeric_limits<int>::max();
    }

    for (const auto& edge : adjacencyList[source]) 
    {
        if (edge.destination == destination)
        {
            return edge.weight;
        }
    }

    return numeric_limits<int>::max();
}

/**
 *  This function checks whether a directed graph is acyclic or not. 
*/
bool DirectedWeightedGraph::isDirectedAcyclicGraph() 
{
    vector<int> inDegree(adjacencyList.size(), 0);

    // Calculate in-degrees of all nodes
    for (const auto& pair : adjacencyList) 
    {
        int node = pair.first;
        for (const auto& edge : pair.second) 
        {
            int destination = edge.destination;
            inDegree[destination]++;
        }
    }

    // Find nodes with in-degree 0
    queue<int> zeroInDegreeNodes;
    for (const auto& pair : adjacencyList) 
    {
        int node = pair.first;
        if (inDegree[node] == 0)
        {
            zeroInDegreeNodes.push(node);
        }
    }

    int visitedCount = 0;
    while (!zeroInDegreeNodes.empty()) 
    {
        int node = zeroInDegreeNodes.front();
        zeroInDegreeNodes.pop();
        visitedCount++;

        for (const auto& edge : adjacencyList[node]) 
        {
            int destination = edge.destination;
            inDegree[destination]--;
            if (inDegree[destination] == 0)
            {
                zeroInDegreeNodes.push(destination);
            }
        }
    }

    return visitedCount == adjacencyList.size();
}

/**
 *  This function performs a topological sort on a directed graph. 
*/
vector<int> DirectedWeightedGraph::topologicalSort() 
{
    vector<int> result;
    vector<bool> visited(adjacencyList.size(), false);
    stack<int> stack;

    // Perform DFS starting from each unvisited node
    for (const auto& pair : adjacencyList) 
    {
        int node = pair.first;
        if (!visited[node])
        {
            topologicalSortUtil(node, visited, stack);
        }
    }

    // Pop elements from stack to get the topological sort order
    while (!stack.empty()) 
    {
        result.push_back(stack.top());
        stack.pop();
    }

    return result;
}

/**
 *  This function performs a dept-first search and construct the topological order of the graph. 
*/
void DirectedWeightedGraph::topologicalSortUtil(int node, vector<bool>& visited, stack<int>& stack) 
{
    visited[node] = true;

    for (const auto& edge : adjacencyList[node]) 
    {
        int destination = edge.destination;
        if (!visited[destination])
        {
            topologicalSortUtil(destination, visited, stack);
        }
    }

    stack.push(node);
}

/**
 *  This function calculates the shortest path between the given nodes.
*/
vector<int> DirectedWeightedGraph::shortestPath(int source, int destination) 
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> distance(adjacencyList.size(), numeric_limits<int>::max());
    vector<int> parent(adjacencyList.size(), -1);

    pq.push(make_pair(0, source));
    distance[source] = 0;

    while (!pq.empty()) 
    {
        int u = pq.top().second;
        pq.pop();

        for (const auto& edge : adjacencyList[u]) 
        {
            int v = edge.destination;
            int weight = edge.weight;

            if (distance[v] > distance[u] + weight) 
            {
                distance[v] = distance[u] + weight;
                parent[v] = u;
                pq.push(make_pair(distance[v], v));
            }
        }
    }

    // Reconstruct the shortest path
    vector<int> path;
    int current = destination;
    while (current != -1) 
    {
        path.push_back(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end());

    return path;
}

