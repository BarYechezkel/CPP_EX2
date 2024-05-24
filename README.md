# CPP_EX2 - Operators Overloading


## Author
-[Bar Yechezkel]
-Email: baryechezkel@gmail.com

## Overview

This library provides a `Graph` class representing an undirected or directed graph using an adjacency matrix. It includes various operators to manipulate and compare graphs, such as addition, subtraction, scalar multiplication, and subgraph checks.

## Class Definition

### `Graph`

The `Graph` class provides methods to construct a graph, load an adjacency matrix, print the graph, and perform various arithmetic and comparison operations.

### Member Variables

- `std::vector<std::vector<int>> matrix`: The adjacency matrix representing the graph.
- `bool isDirected`: Indicates whether the graph is directed.
- `int numOfEdges`: The number of edges in the graph.
- `bool withWeights`: Indicates whether the graph has weighted edges.
- `bool hasNegativeEdge`: Indicates whether the graph has negative edges.

### Constructors

- `Graph()`: Default constructor that initializes an empty graph.

### Methods

- `void loadGraph(std::vector<std::vector<int>> &adjacency_matrix)`: Loads the graph from the given adjacency matrix and sets properties like `isDirected`, `numOfEdges`, `withWeights`, and `hasNegativeEdge`.
- `std::string printGraph()`: Prints the adjacency matrix of the graph and returns it as a string.
- `const std::vector<std::vector<int>> getMatrix() const`: Returns the adjacency matrix.
- `bool getIsDirected() const`: Returns whether the graph is directed.
- `int getNumOfEdges() const`: Returns the number of edges in the graph.
- `bool getHasNegativeEdge() const`: Returns whether the graph has negative edges.
- `bool getWithWeights() const`: Returns whether the graph has weighted edges.

### Operator Overloading

- `Graph operator+(const Graph &g)`: Adds two graphs and returns the resulting graph.
- `Graph operator-(const Graph &g)`: Subtracts one graph from another and returns the resulting graph.
- `Graph &operator+=(const Graph &g)`: Adds another graph to this graph.
- `Graph &operator-=(const Graph &g)`: Subtracts another graph from this graph.
- `Graph &operator+()`: Unary plus operator.
- `Graph &operator-()`: Unary minus operator (negates the graph).
- `Graph operator++(int)`: Postfix increment operator (increases all edges by 1).
- `Graph &operator++()`: Prefix increment operator (increases all edges by 1).
- `Graph operator--(int)`: Postfix decrement operator (decreases all edges by 1).
- `Graph &operator--()`: Prefix decrement operator (decreases all edges by 1).
- `bool operator==(Graph &g)`: Checks if two graphs are equal.
- `bool operator<(Graph &g)`: Checks if this graph is a subgraph of another graph.
- `bool operator>(Graph &g)`: Checks if this graph is a supergraph of another graph.
- `bool operator<=(Graph &g)`: Checks if this graph is a subgraph or equal to another graph.
- `bool operator>=(Graph &g)`: Checks if this graph is a supergraph or equal to another graph.
- `Graph &operator*=(int scalar)`: Multiplies all edges of the graph by a scalar.
- `Graph operator*(int scalar)`: Multiplies all edges of the graph by a scalar and returns the resulting graph.
- `Graph operator*(Graph &g)`: Multiplies two graphs (matrix multiplication) and returns the resulting graph.

## Example Usage

### Creating and Loading a Graph

```cpp
#include "Graph.hpp"
#include <iostream>

using namespace ariel;
using namespace std;

int main() {
    // Create an empty graph
    Graph g;

    // Load graph with an adjacency matrix
    vector<vector<int>> adjacency_matrix = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g.loadGraph(adjacency_matrix);

    // Print the graph
    cout << g.printGraph() << endl;

    return 0;
}
