#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <vector>
#include <iostream>
#include <string>
namespace ariel{

class Graph
{
private:
    std::vector<std::vector<int>> matrix;
    bool isDirected;
    bool hasNegativeEdge;
    bool withWeights;
    int numOfEdges;
public:
    // constructor
    Graph();

    void loadGraph( std::vector<std::vector<int>> &adjacency_matrix);
    void printGraph();
    std::vector<std::vector<int>> getMatrix();
    bool getIsDirected();
    int getNumOfEdges();
    bool getHasNegativeEdge();
    bool getWithWeights();
    
};
}
#endif
