#include "gtest/gtest.h"
#include "../src/directedWeightedGraph.cpp"
using namespace std;

TEST(GraphTest, AddNode) {
    DirectedWeightedGraph graph;
    graph.addNode(0);
    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(3);
    graph.addNode(4);

    EXPECT_TRUE(graph.isNodeExists(0));
    EXPECT_TRUE(graph.isNodeExists(1));
    EXPECT_TRUE(graph.isNodeExists(2));
    EXPECT_TRUE(graph.isNodeExists(3));
    EXPECT_TRUE(graph.isNodeExists(4));
}

TEST(GraphTest, AddEdge) {
    DirectedWeightedGraph graph;
    graph.addNode(0);
    graph.addNode(1);
    graph.addEdge(0, 1, 3);

    EXPECT_TRUE(graph.isEdgeExists(0, 1));
    EXPECT_FALSE(graph.isEdgeExists(1, 0));
}

TEST(GraphTest, SetWeight) {
    DirectedWeightedGraph graph;
    graph.addNode(1);
    graph.addNode(2);
    graph.addEdge(1, 2, 5);
    graph.setWeight(1, 2, 10);

    EXPECT_EQ(graph.getWeight(1, 2), 10);
    EXPECT_EQ(graph.getWeight(2, 1), numeric_limits<int>::max());
}

TEST(GraphTest, IsDirectedAcyclicGraph) {
    DirectedWeightedGraph graph;
    graph.addNode(0);
    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(3);
    graph.addNode(4);
    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 3, 7);
    graph.addEdge(0, 4, 8);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 4);
    graph.addEdge(3, 2, 2);
    graph.addEdge(4, 3, 3);

    EXPECT_TRUE(graph.isDirectedAcyclicGraph());

    // Add a cycle to make the graph cyclic
    graph.addEdge(3, 0, 2);

    EXPECT_FALSE(graph.isDirectedAcyclicGraph());
}

TEST(GraphTest, ShortestPath) {
    DirectedWeightedGraph graph;
    graph.addNode(0);
    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(3);
    graph.addNode(4);
    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 3, 7);
    graph.addEdge(0, 4, 8);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 4);
    graph.addEdge(3, 2, 2);
    graph.addEdge(4, 3, 3);

    vector<int> expectedPath = {0, 4};
    vector<int> shortestPath = graph.shortestPath(0, 4);

    EXPECT_EQ(shortestPath, expectedPath);

    vector<int> expectedPath2 = {0, 1, 2};
    vector<int> shortestPath2 = graph.shortestPath(0, 2);

    EXPECT_EQ(shortestPath2, expectedPath2);
}