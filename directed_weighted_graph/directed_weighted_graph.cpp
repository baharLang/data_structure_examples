#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

class Node 
{
public:
    int value;
    vector<pair<Node*, int>> edges;

    Node(int val) : value(val) {}

    void addEdge(Node* node, int weight) 
    {
        edges.emplace_back(node, weight);
    }
};

class Graph 
{
public:
    vector<Node*> nodes;

    void addNode(int value) 
    {
        nodes.push_back(new Node(value));
    }

    bool isCyclicUtil(Node* node, vector<bool>& visited, vector<bool>& recursionStack) 
    {
        visited[node->value] = true;
        recursionStack[node->value] = true;

        for (const auto& edge : node->edges) 
        {
            Node* neighbor = edge.first;
            if (!visited[neighbor->value]) 
            {
                if (isCyclicUtil(neighbor, visited, recursionStack)) 
                {
                    return true;
                }
            }
            else if (recursionStack[neighbor->value]) 
            {
                return true;
            }
        }

        recursionStack[node->value] = false;
        return false;
    }

    // The method that checks whether the graph acyclic or not.
    bool isDirectedAcyclicGraph() 
    {
        vector<bool> visited(nodes.size(), false);
        vector<bool> recursionStack(nodes.size(), false);

        for (Node* node : nodes) 
        {
            if (!visited[node->value]) 
            {
                if (isCyclicUtil(node, visited, recursionStack)) 
                {
                    return false;
                }
            }
        }

        return true;
    }

    // The method that finds the shortest path.
    void shortestPath(int startNodeValue) 
    {
        vector<int> distance(nodes.size(), numeric_limits<int>::max());
        vector<bool> visited(nodes.size(), false);

        auto compare = [](const pair<int, Node*>& a, const pair<int, Node*>& b) { return a.first > b.first; };
        priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, decltype(compare)> pq(compare);

        Node* startNode = NULL;
        for (Node* node : nodes) 
        {
            if (node->value == startNodeValue) 
            {
                startNode = node;
                distance[node->value] = 0;
                break;
            }
        }

        if (startNode == NULL) 
        {
            cout << "Start node not found!" << endl;
            return;
        }

        pq.push(make_pair(0, startNode));

        while (!pq.empty()) 
        {
            Node* currentNode = pq.top().second;
            pq.pop();

            if (visited[currentNode->value]) 
            {
                continue;
            }

            visited[currentNode->value] = true;

            for (const auto& edge : currentNode->edges) 
            {
                Node* neighbor = edge.first;
                int weight = edge.second;

                if (!visited[neighbor->value] && distance[currentNode->value] + weight < distance[neighbor->value]) 
                {
                    distance[neighbor->value] = distance[currentNode->value] + weight;
                    pq.push(make_pair(distance[neighbor->value], neighbor));
                }
            }
        }

        // Print shortest path distances
        cout << "Shortest path distances from node " << startNodeValue << ":" << endl;
        for (int i = 0; i < distance.size(); ++i) 
        {
            cout << "Node " << i << ": " << distance[i] << endl;
        }
    }
};

int main() 
{
    // Create a graph
    Graph graph;

    // Add nodes
    graph.addNode(0);
    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(3);
    graph.addNode(4);

    // Add edges
    //addEdge(node, weight)
    graph.nodes[0]->addEdge(graph.nodes[1], 3);
    graph.nodes[0]->addEdge(graph.nodes[3], 7);
    graph.nodes[0]->addEdge(graph.nodes[4], 8);
    graph.nodes[1]->addEdge(graph.nodes[2], 1);
    graph.nodes[1]->addEdge(graph.nodes[3], 4);
    graph.nodes[3]->addEdge(graph.nodes[2], 2);
    graph.nodes[4]->addEdge(graph.nodes[3], 3);

    // Check if the graph is a directed acyclic graph
    bool isDag = graph.isDirectedAcyclicGraph();
    cout << "Is the graph a directed acyclic graph? " << (isDag ? "Yes" : "No") << endl;

    // Find shortest paths using Dijkstra's algorithm
    int startNodeValue = 0;
    graph.shortestPath(startNodeValue);

    return 0;
}