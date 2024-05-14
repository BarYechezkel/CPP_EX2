
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#include <iostream>
#include "Graph.hpp"
#include <string>
using namespace std;

namespace ariel
{
    class Algorithms
    {
   
public:
/*
get graph and return 1 if the graph is connected, 0 if its not
*/
static int isConnected(Graph &g);

/*
get graph, start point, end point 
*/
static string shortestPath(Graph &g,int start,int end);

/*
return 1 if the graph contains cycle and print it, 0 if its not
*/ 
static int isContainsCycle(Graph &g);

/*
return 1 if the graph is bipartite The algorithm
print the partition of the graph, return 0 if its not bipartite.
*/
static string isBipartite(Graph &g);

/*
return true if the graph contains negative cycle, false if its not
*/
static bool negativeCycle(Graph &g);
};


}
#endif