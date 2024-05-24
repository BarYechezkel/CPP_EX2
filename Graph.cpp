#include "Graph.hpp"
using namespace ariel;
#include <iostream>
using namespace std;

// Constructor implementation
Graph::Graph()
{
    // print the graph [0, 1, 0], [1, 0, 1], [0, 1, 0]
    int size = this->matrix.size();
    for (int i = 0; i < size; i++)
    {
        std::vector<int> row;
        cout << "row: " << i << endl;
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {
                row.push_back(0);
            }
            else
            {
                row.push_back(1);
            }
        }
        this->matrix.push_back(row);
    }
}

// Method to load graph from adjacency matrix
void Graph::loadGraph(std::vector<std::vector<int>> &adjacency_matrix)
{
    this->isDirected = false;
    this->numOfEdges = 0;
    this->withWeights = false;
    this->hasNegativeEdge = false;

    if (adjacency_matrix.empty())
    {
        // If the matrix is empty, the graph is empty
        throw std::invalid_argument("The matrix is empty");
    }

    for (size_t i = 0; i < adjacency_matrix.size(); i++)
    {
        if (adjacency_matrix.size() != adjacency_matrix[i].size())
        {
            // If the matrix is not square, it is not a valid adjacency matrix
            throw std::invalid_argument("The matrix is not square");
        }

        for (size_t j = 0; j < adjacency_matrix[i].size(); j++)
        {
            if (adjacency_matrix[i][j] != adjacency_matrix[j][i])
            {
                // If the matrix is not symmetric, the graph is directed
                isDirected = true;
            }
            if (adjacency_matrix[j][j] != 0)
            {
                // If the diagonal is not zero, the matrix is not a valid adjacency matrix
                throw std::invalid_argument("The matrix is not a valid adjacency matrix");
            }
            if (adjacency_matrix[i][j] != 0)
            {
                // If the matrix has a non-zero element, it is an edge
                numOfEdges++;
            }
            if (adjacency_matrix[i][j] < 0)
            {
                // If the matrix has a negative element, the graph has a negative edge
                hasNegativeEdge = true;
            }

            if (adjacency_matrix[i][j] != 1 && adjacency_matrix[i][j] != 0)
            {
                // If the matrix has a non-zero element greater than 1, the graph has a weighted edge
                withWeights = true;
            }
        }
    }

    if (!isDirected)
    {
        numOfEdges = numOfEdges / 2;
    }

    this->matrix = adjacency_matrix;
}

// Method to print the graph , Should print the matrix of the graph: [0, 1, 0], [1, 0, 1], [0, 1, 0]
string Graph::printGraph()
{
    string result;
    cout << "Graph with " << matrix.size() << " vertices and " << numOfEdges << " edges." << std::endl;
    for (size_t i = 0; i < matrix.size() - 1; i++)
    {
        cout << "[";
        result += "[";
        for (size_t j = 0; j < matrix[i].size() - 1; j++)
        {
            cout << matrix[i][j] << " ,";
            result += to_string(matrix[i][j]) + ", ";
        }
        cout << matrix[i][matrix[i].size() - 1];
        result += to_string(matrix[i][matrix[i].size() - 1]);
        cout << "]\n";
        result += "]\n";
    }
    cout << "[";
    result += "[";
    for (size_t m = 0; m < matrix[matrix.size() - 1].size() - 1; m++)
    {
        cout << matrix[matrix.size() - 1][m] << " ,";
        result += to_string(matrix[matrix.size() - 1][m]) + ", ";
    }
    cout << matrix[matrix.size() - 1][matrix[matrix.size() - 1].size() - 1];
    result += to_string(matrix[matrix.size() - 1][matrix[matrix.size() - 1].size() - 1]);
    cout << "]";
    result += "]";
    cout << endl;
    return result;
}

// Method to get the adjacency matrix
const std::vector<std::vector<int>> Graph::getMatrix() const
{
    return matrix;
}

// Method to get if the graph is directed
bool Graph::getIsDirected()
{
    return isDirected;
}

// Method to get the number of edges
int Graph::getNumOfEdges()
{
    return numOfEdges;
}

// Method to get if the graph has a negative edge
bool Graph::getHasNegativeEdge()
{
    return hasNegativeEdge;
}

// Method to get if the graph has a weighted edge
bool Graph::getWithWeights()
{
    return withWeights;
}

//=====================================================================================================================
//                                     Arithmetic Operators Overloading
//=====================================================================================================================

/*
Operator overloading for the addition of two graphs
we will get new graph
maybe edges will be added
*/
Graph Graph::operator+(const Graph &g)
{
    Graph result;
    if (matrix.size() != g.getMatrix().size())
    {
        throw std::invalid_argument("The matrixes are not the same size");
        cout << "The matrixes are not the same size" << endl;
    }
    size_t size = matrix.size();
    vector<vector<int>> new_matrix(size, vector<int>(size, 0));
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            new_matrix[i][j] = matrix[i][j] + g.matrix[i][j];
        }
    }
    result.loadGraph(new_matrix);
    return result;
}

/*
Operator overloading for the subtraction of two graphs
we will get new graph
maybe edges will removed, we can get negative edges
*/
Graph Graph::operator-(const Graph &g)
{
    Graph result;
    if (matrix.size() != g.getMatrix().size())
    {
        throw std::invalid_argument("The matrixes are not the same size");
    }
    size_t size = matrix.size();
    vector<vector<int>> new_matrix(size, vector<int>(size, 0));
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            new_matrix[i][j] = matrix[i][j] - g.matrix[i][j];
        }
    }
    result.loadGraph(new_matrix);
    return result;
}

/*
Operator += performs a subtraction opertion to the graph that we get as a parameter.
*/
Graph &Graph::operator+=(const Graph &g)
{
    if (matrix.size() != g.getMatrix().size())
    {
        throw std::invalid_argument("The matrixes are not the same size");
    }
    *this = *this + g;
    return *this;
}

/*
Operator -= performs a add opertion to the graph that we get as a parameter.
*/
Graph &Graph::operator-=(const Graph &g)
{
    if (this->getMatrix().size() != g.getMatrix().size())
    {
        throw std::invalid_argument("The matrixes are not the same size");
    }
    *this = *this - g;
    return *this;
}

/*
Operator overloading for the unary plus
*/
Graph &ariel::Graph::operator+()
{
    return *this;
}

/*
operator overloading for the unary minus
use the *= operator to multiply the graph by -1
*/
Graph ariel::Graph::operator-()
{
    return *this * -1;
}

/*
Operator overloading for the postfix increment g++
*/
Graph ariel::Graph::operator++(int) // g++ postfix increment
{
    if (matrix.empty())
    {
        throw std::invalid_argument("The matrix is empty");
    }
    Graph newGraph = *this;
    size_t size = matrix.size();
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (matrix[i][j] != 0) // only if we have an edge
            {
                matrix[i][j] = matrix[i][j] + 1;
            }
        }
    }
    return newGraph;
}

/*
Operator overloading for the prefix increment ++g
*/
Graph &ariel::Graph::operator++() // ++g prefix increment
{
    if (matrix.empty())
    {
        throw std::invalid_argument("The matrix is empty");
    }
    size_t size = matrix.size();
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (matrix[i][j] != 0) // only if we have an edge
            {
                matrix[i][j] = matrix[i][j] + 1;
            }
        }
    }
    return *this;
}

/*
Operator overloading for the postfix decrement g--
*/
Graph ariel::Graph::operator--(int)
{
    if (matrix.empty())
    {
        throw std::invalid_argument("The matrix is empty");
    }
    Graph newGraph = *this;
    size_t size = matrix.size();
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (matrix[i][j] != 0) // only if we have an edge
            {
                matrix[i][j] = matrix[i][j] - 1;
            }
        }
    }
    return newGraph;
}

/*
operator overloading for the prefix decrement --g
*/
Graph &ariel::Graph::operator--()
{
    if (matrix.empty())
    {
        throw std::invalid_argument("The matrix is empty");
    }
    size_t size = matrix.size();
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (matrix[i][j] != 0) // only if we have an edge
            {
                matrix[i][j] = matrix[i][j] - 1;
            }
        }
    }
    return *this;
}

/*
opretor overloading for the multiplication of a graph by a scalar, the opertion work on the graph itself
this *= scalar
*/
Graph &ariel::Graph::operator*=(int scalar)
{
    if (matrix.empty())
    {
        throw std::invalid_argument("The matrix is empty");
    }
    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            matrix[i][j] = matrix[i][j] * scalar;
        }
    }
    return *this;
}

/*
opretor overloading for the multiplication of a graph by a scalar, the opertion work on new graph
g_new = g * scalar
*/
Graph ariel::Graph::operator*(int scalar)
{
    if (matrix.empty())
    {
        throw std::invalid_argument("The matrix is empty");
    }
    Graph result;
    vector<vector<int>> new_matrix = matrix;
    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            new_matrix[i][j] = matrix[i][j] * scalar;
        }
    }
    result.loadGraph(new_matrix);
    return result;
}

/*
opretor overloading for the multiplication of two graphs, the opertion work on new graph
g_new = g1 * g2
*/
Graph ariel::Graph::operator*(Graph &g)
{
    if (matrix.size() != g.getMatrix().size())
    {
        throw std::invalid_argument("The matrixes are not the same size");
    }
    Graph result;
    size_t size = matrix.size();
    vector<vector<int>> new_matrix(size, vector<int>(size, 0));
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            // for each cell in the result matrix cell(x,y)
            // we will multiply the row x of one gragh in the colmn y of the other graph
            for (size_t k = 0; k < size; k++)
            {
                new_matrix[i][j] += matrix[i][k] * g.matrix[k][j];
            }
        }
    }

    for (size_t i = 0; i < size; i++)
    {
        if (new_matrix[i][i] != 0)
        {
            new_matrix[i][i] = 0;
        }
    }
    result.loadGraph(new_matrix);
    return result;
}

Graph ariel::Graph::operator*=(Graph &g)
{
   *this = *this * g;
    return *this;
}

//=====================================================================================================================
//                                     comparison Operators Overloading
//=====================================================================================================================

/*
Operator overloading to check equality of two graphs
*/
bool ariel::Graph::operator==(Graph &g)
{
    return (!(*this < g) && !(*this > g)) ? true : false;
}

/*
operator overloading to check if one graph is contained in the other
this < g
*/
bool ariel::Graph::operator<(Graph &g) // this < g
{
    if (matrix.empty() || g.getMatrix().empty())
    {
        throw std::invalid_argument("The matrix is empty");
    }

    // If the matrixes are the same, one is not containd in the other
    if (matrix == g.getMatrix())
    {
        return false;
    }

    size_t size_big = g.getMatrix().size();
    size_t size_small = matrix.size();
    bool found = false;
    // If `this` graph is bigger, it cannot be smaller
    if (size_small > size_big)
    {
        return false;
    }
    for (size_t i = 0; i < size_big - size_small; i++)
    {
        for (size_t j = 0; j < size_big - size_small; j++)
        {
            if (matrix[i][j] == g.getMatrix()[i][j])
            // we found first element that is equal
            {
                found = true;
                for (size_t k = 0; k < size_small; k++)
                {
                    for (size_t l = 0; l < size_small; l++)
                    {
                        if (matrix[k][l] != g.getMatrix()[i + k][j + l])
                        {
                            found = false;
                            break;
                        }
                    }
                }
                if (found)
                    return true;
            }
        }
    }
    return false;
}

/*
operator overloading to check if one graph is contained in the other
this > g
uses the < operator
*/
bool ariel::Graph::operator>(Graph &g) // this > g
{
    // enoght to check if g < this
    return g < *this;
}

/*
operator overloading to check if one graph is contained in the other or the graphs are equal
this <= g
uses the < , == operators
*/
bool ariel::Graph::operator<=(Graph &g) // this <= g
{
    return *this == g || *this < g;
}

/*
operator overloading to check if one graph is contained in the other or the graphs are equal
this >= g
use the > , == operators
*/
bool ariel::Graph::operator>=(Graph &g) // this >= g
{
   
    return *this == g || *this > g;
}
