#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <vector>
#include <iostream>
#include <string>
namespace ariel
{

    class Graph
    {
    private:
        std::vector<std::vector<int>> matrix;
        bool isDirected;
        bool hasNegativeEdge;
        bool withWeights;
        int numOfEdges;

    public:
        Graph();
        /*
        operator overloading for the output stream
        print the graph matrix
        */
        friend std::ostream &operator<<(std::ostream &os, Graph &graph)
        {
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
        /*
        Method to load graph from adjacency matrix
        also set the graph properties and check if the graph is valid
         */
        void loadGraph(std::vector<std::vector<int>> &adjacency_matrix);

        /*
       Method to print the graph , Should print the matrix of the graph: [0, 1, 0], [1, 0, 1], [0, 1, 0]
        */
        std::string printGraph();

        /*
        Method to get the adjacency matrix
        */
        const std::vector<std::vector<int>> getMatrix() const;

        /*
        Method to get if the graph is directed
        */
        bool getIsDirected();
        /*
        Method to get the number of edges
        */
        int getNumOfEdges();

        /*
        Method to get if the graph has a negative edge
        */
        bool getHasNegativeEdge();
        /*
        Method to get if the graph has a weighted edge
        */
        bool getWithWeights();

        //=====================================================================================================================
        //                                     Arithmetic Operators Overloading
        //=====================================================================================================================

        /*
        Operator overloading for the addition of two graphs
        we will get new graph
        maybe edges will be added
        new_g = g1+g2
        */
        Graph operator+(const Graph &g);

        /*
        Operator overloading for the subtraction of two graphs
        we will get new graph
        maybe edges will removed, we can get negative edges
        */
        Graph operator-(const Graph &g);

        /*
        Operator += performs a subtraction opertion to the graph that we get as a parameter.
        g1+=g2
        */
        Graph& operator+=(const Graph &g);

        /*
        Operator -= performs a add opertion to the graph that we get as a parameter.
        g1-=g2
        */
        Graph& operator-=(const Graph &g);

        /*
        Operator overloading for the unary plus
        +g
        */
        Graph& operator+();

        /*
        operator overloading for the unary minus
        uses the *= operator to multiply the graph by -1
        -g
        */
        Graph operator-();

        /*
        Operator overloading for the postfix increment
         g++
        */
        Graph operator++(int); // g++ postfix increment

        /*
        Operator overloading for the prefix increment
        ++g
        */
        Graph &operator++(); // ++g prefix increment

        /*
        Operator overloading for the postfix decrement
         g--
        */
        Graph operator--(int); // g--postfix decrement

        /*
        operator overloading for the prefix decrement
         --g
        */
        Graph &operator--(); // --g prefix decrement

         /*
        opretor overloading for the multiplication of a graph by a scalar, the opertion work on the graph itself
        this *= scalar
        */
        Graph& operator*=(int scalar);

        /*
        opretor overloading for the multiplication of a graph by a scalar, the opertion work on new graph
        g_new = g * scalar
        */                            
        Graph operator*(int scalar);

        /*
        opretor overloading for the multiplication of two graphs, the opertion work on new graph
        g_new = g1 * g2
        */
        Graph operator*(Graph &g);

        Graph operator*=(Graph &g);



//=====================================================================================================================
//                                     Comparison Operators Overloading
//=====================================================================================================================
        /*
        Operator overloading to check equality of two graphs
        uses the < > operators to check if the graphs are equal
        */
        bool operator==(Graph &g);

        /*
        operator overloading to check if one graph is contained in the other
        this < g
        */
        bool operator<(Graph &g);

        /*
        operator overloading to check if one graph is contained in the other
        this > g
        uses the < operator
        */
        bool operator>(Graph &g);

        /*
        operator overloading to check if one graph is contained in the other or the graphs are equal
        this <= g
        uses the < , == operators
        */
        bool operator<=(Graph &g);
        
        /*
        operator overloading to check if one graph is contained in the other or the graphs are equal
        this >= g
        uses the > , == operators
        */
        bool operator>=(Graph &g);

       
    };
}
#endif
