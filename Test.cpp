#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;
using namespace ariel;


TEST_CASE("Test graph addition")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
}

TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};
    CHECK(g4.printGraph() == "[0, 0, 2]\n[1, 0, 1]\n[1, 0, 0]");
}

TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1}};
    CHECK_THROWS(g2.loadGraph(weightedGraph));
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
}


    TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2; // Does not matter
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1}};
    CHECK_THROWS(g2.loadGraph(weightedGraph));
    ariel::Graph g5;
    vector<vector<int>> zeroGraph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g5.loadGraph(zeroGraph);
    ariel::Graph g6 = -g5;
    ariel::Graph g3; // Does not matter
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0}};
    g3.loadGraph(graph3);

    CHECK_THROWS(g5 * g3);
    CHECK_THROWS(g1 * g3);

    // Addition of two graphs with different dimensions
    ariel::Graph g8;
    vector<vector<int>> graph4 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g8.loadGraph(graph4);
    CHECK_THROWS(g1 + g8);
}
TEST_CASE("Addition + unary operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = +g1;
    CHECK(g2.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");
}

TEST_CASE("Addition + binary operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");

    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g4.loadGraph(graph4);
    ariel::Graph g5;
    vector<vector<int>> weightedGraph5 = {
        {0, 1, 1, 1, 1},
        {1, 0, 2, 1, 1},
        {1, 2, 0, 1, 1},
        {1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0}};
    g5.loadGraph(weightedGraph5);
    ariel::Graph g6 = g4 + g5;
    CHECK(g6.printGraph() == "[0, 2, 1, 1, 2]\n[2, 0, 3, 1, 1]\n[1, 3, 0, 2, 1]\n[1, 1, 2, 0, 2]\n[2, 1, 1, 2, 0]");
    ariel::Graph g7;
    vector<vector<int>> graph7 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g7.loadGraph(graph7);

    ariel::Graph g8;
    vector<vector<int>> zeroGraph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g8.loadGraph(zeroGraph);

    ariel::Graph g9 = g7 + g8;
    CHECK(g9.printGraph() == "[0, 1, 0]\n[1, 0, 1]\n[0, 1, 0]");

    ariel::Graph g10;
    vector<vector<int>> graph10 = {
        {0, 1},
        {1, 0}};
    g10.loadGraph(graph10);

    ariel::Graph g11;
    vector<vector<int>> graph11 = {
        {0, 1},
        {1, 0}};
    g11.loadGraph(graph11);

    ariel::Graph g12 = g10 + g11;

    CHECK(g12.printGraph() == "[0, 2]\n[2, 0]");
}
TEST_CASE("Addition - binary operator")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 - g2;
    CHECK(g3.printGraph() == "[0, 0, -1]\n[0, 0, -1]\n[-1, -1, 0]");

    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g4.loadGraph(graph4);
    ariel::Graph g5;
    vector<vector<int>> weightedGraph5 = {
        {0, 1, 1, 1, 1},
        {1, 0, 2, 1, 1},
        {1, 2, 0, 1, 1},
        {1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0}};
    g5.loadGraph(weightedGraph5);
    ariel::Graph g6 = g4 - g5;
    CHECK(g6.printGraph() == "[0, 0, -1, -1, 0]\n[0, 0, -1, -1, -1]\n[-1, -1, 0, 0, -1]\n[-1, -1, 0, 0, 0]\n[0, -1, -1, 0, 0]");
}

TEST_CASE("rediction - unary operator")
{
    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g3.loadGraph(graph3);
    ariel::Graph g4 = -g3;
    CHECK(g4.printGraph() == "[0, -1, 0]\n[-1, 0, -1]\n[0, -1, 0]");

    ariel::Graph g5;
    vector<vector<int>> graph5 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g5.loadGraph(graph5);
    ariel::Graph g6 = -g5;
    CHECK(g6.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");
}

TEST_CASE("Addition g++ and ++g unary operator")
{
    // g++
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    vector<vector<int>> expectedGraph = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};

    ariel::Graph g2 = g1++;

    CHECK(g2.getMatrix() == graph);
    CHECK(g1.getMatrix() == expectedGraph);

    //++g
    ariel::Graph g3 = ++g1;
    vector<vector<int>> expectedGraph2 = {
        {0, 3, 0},
        {3, 0, 3},
        {0, 3, 0}};
    CHECK(g3.getMatrix() == expectedGraph2);
}
TEST_CASE("redection g-- and --g unary operator")
{
    // g--
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    vector<vector<int>> expectedGraph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};

    ariel::Graph g2 = g1--;

    CHECK(g2.getMatrix() == graph);
    CHECK(g1.getMatrix() == expectedGraph);
    g1--;
    CHECK(g1.getMatrix() == expectedGraph); // 0 not change to -1
    //--g
    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 7, 5, 7},
        {7, 0, 7, 5},
        {5, 7, 0, 7},
        {7, 5, 7, 0}};
    g4.loadGraph(graph4);
    ariel::Graph g5;
    g5 = --g4;
    vector<vector<int>> graph5 = {
        {0, 6, 4, 6},
        {6, 0, 6, 4},
        {4, 6, 0, 6},
        {6, 4, 6, 0}};
    CHECK(g5.getMatrix() == graph5);
    CHECK(g4.getMatrix() == graph5);
}

TEST_CASE("Addition +=")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);

    g1 += g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g1.getMatrix() == expectedGraph);
    g1 += -g1;

    vector<vector<int>> expectedGraph3 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    CHECK(g1.getMatrix() == expectedGraph3);
}
TEST_CASE("redction -=")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);

    g1 -= g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, -1},
        {0, 0, -1},
        {-1, -1, 0}};
    CHECK(g1.getMatrix() == expectedGraph);
    g1 += -g1;
    vector<vector<int>> expectedGraph3 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    CHECK(g1.getMatrix() == expectedGraph3);
}
TEST_CASE("multiplication *")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 1000},
        {1, 0, 1},
        {10000, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph1);
    ariel::Graph g3 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 1000, 1},
        {0, 0, 0},
        {1, 10000, 0}};
    CHECK(g3.getMatrix() == expectedGraph);
    ariel::Graph g4;
}
TEST_CASE("multiplication * scalr")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 20},
        {1, 0, 1},
        {-5, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    g2 = g1 * 2;

    vector<vector<int>> expectedGraph = {
        {0, 2, 40},
        {2, 0, 2},
        {-10, 2, 0}};
    CHECK(g2.getMatrix() == expectedGraph);

    g2 = g1 * 0;
    vector<vector<int>> expectedGraph2 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    CHECK(g2.getMatrix() == expectedGraph2);
}
TEST_CASE("multiplication *=  graph and scalar")
{
    ariel::Graph g10;
    vector<vector<int>> graph10 = {
        {0, 1},
        {1, 0}};
    g10.loadGraph(graph10);

    ariel::Graph g11;
    vector<vector<int>> graph11 = {
        {0, 1},
        {1, 0}};
    g11.loadGraph(graph11);
    g10 *= g11;
    vector<vector<int>> expectedGraph = {
        {0, 0},
        {0, 0}};
    CHECK(g10.getMatrix() == expectedGraph);
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 20},
        {1, 0, 1},
        {-5, 1, 0}};
    g1.loadGraph(graph);
    g1 *= 2;
    vector<vector<int>> expectedGraph2 = {
        {0, 2, 40},
        {2, 0, 2},
        {-10, 2, 0}};
    CHECK(g1.getMatrix() == expectedGraph2);
}
TEST_CASE("Comparisons ==  > < >= <=")
{
    ariel::Graph g10;
    vector<vector<int>> graph10 = {
        {0, 1},
        {1, 0}};
    g10.loadGraph(graph10);

    ariel::Graph g11;
    vector<vector<int>> graph11 = {
        {0, 2},
        {1, 0}};
    g11.loadGraph(graph11);
    CHECK((g10 == g11) == true);
    CHECK((g10 < g11) == false);
    CHECK((g10 > g11) == false);
    CHECK((g10 >= g11) == true);
    CHECK((g10 <= g11) == true);

    ariel::Graph g5;
    vector<vector<int>> graph5 = {
        {0, 6, 4, 6},
        {6, 0, 6, 4},
        {4, 6, 0, 6},
        {6, 4, 6, 0}};
    g5.loadGraph(graph5);

    ariel::Graph g6;
    vector<vector<int>> graph6 = {
        {0, 6},
        {6, 0}};
    g6.loadGraph(graph6);
    CHECK((g5 > g6) == true);
    CHECK((g5 < g6) == false);
    CHECK((g5 >= g6) == true);
    CHECK((g5 == g6) == false);
    CHECK_FALSE((g5 <= g6) == true);
}