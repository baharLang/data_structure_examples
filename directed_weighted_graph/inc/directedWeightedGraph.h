#ifndef DIRECTED_WEIGHTED_GRAPH_H
#define DIRECTED_WEIGHTED_GRAPH_H

#include <vector>
#include <unordered_map>
#include <stack>
#include <limits>

using namespace std;

struct Edge {
    int destination;
    int weight;
};

class DirectedWeightedGraph  {
private:
    unordered_map<int, vector<Edge>> adjacencyList;
    void topologicalSortUtil(int node, vector<bool>& visited, stack<int>& stack);

public:
    void addNode(int node);
    void addEdge(int source, int destination, int weight);
    void setWeight(int source, int destination, int weight);
    bool isNodeExists(int node);
    bool isEdgeExists(int source, int destination);
    int getWeight(int source, int destination);
    bool isDirectedAcyclicGraph();
    vector<int> topologicalSort();
    vector<int> shortestPath(int source, int destination);
};

#endif