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
    friend std::ostream &operator<<(std::ostream &os,  Graph &graph){
        graph.printGraph();

        for (size_t i = 0; i < graph.matrix.size(); i++)
        {
            for (size_t j = 0; j < graph.matrix[(size_t)i].size(); j++)
            {
                os << graph.matrix[i][(size_t)j] << " ";
            }
            os << std::endl;
        }
        return os;
    }


    void loadGraph( std::vector<std::vector<int>> &adjacency_matrix);
    void printGraph();
    const std::vector<std::vector<int>> getMatrix() const;
    bool getIsDirected();
    int getNumOfEdges();
    bool getHasNegativeEdge();
    bool getWithWeights();


    Graph operator+(const Graph &g);
    Graph operator-(const Graph &g);
    Graph& operator+=(const Graph &g);
    Graph& operator-=(const Graph &g);
    Graph& operator+();
    Graph& operator-();

//    g++;
//    x = y++
//    x= y;
//     y = y+1;
    Graph operator++(int); // g++ postfix increment

    Graph& operator++(); // ++g prefix increment


    Graph operator--(); // prefix decrement

    Graph operator--(int); // postfix decrement



//    ++g;
//    x= ++y;
//    x = y;   


    Graph& operator*(int scalar);


    // friend Graph operator*(Graph &g1, Graph &g2);

    // //Graph operator*(Graph &g);
    // Graph operator/=(int scalar);
    // Graph operator*=(int scalar);


    
};
}
#endif
