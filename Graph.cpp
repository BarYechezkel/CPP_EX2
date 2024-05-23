#include "Graph.hpp"
using namespace ariel;
#include <iostream>
using namespace std;

// Constructor implementation
Graph::Graph()
{
    //print the graph [0, 1, 0], [1, 0, 1], [0, 1, 0]
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
void Graph::loadGraph( std::vector<std::vector<int>> &adjacency_matrix)
{
    this->isDirected = false;
    this->numOfEdges = 0;
    this->withWeights = false;
    this->hasNegativeEdge = false;

    if (adjacency_matrix.size() == 0)
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
            if (adjacency_matrix[i][j] < 0){
                // If the matrix has a negative element, the graph has a negative edge
                hasNegativeEdge = true;
            }

            if (adjacency_matrix[i][j] != 1 && adjacency_matrix[i][j] != 0){
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

// Method to print the graph
// void Graph::printGraph()
// {
//     std::cout << "Graph with " << matrix.size() << " vertices and "<< numOfEdges <<" edges." << std::endl;
//     for (size_t i = 0; i < matrix.size(); i++)
//     {
//         for (size_t j = 0; j < matrix[i].size(); j++)
//         {
//             std::cout << matrix[i][j] << " ";
//         }
//         std::cout << std::endl;
//     }
  
// }

// Method to print the graph , Should print the matrix of the graph: [0, 1, 0], [1, 0, 1], [0, 1, 0]
void Graph::printGraph()
{
    std::cout << "Graph with " << matrix.size() << " vertices and "<< numOfEdges <<" edges." << std::endl;
    for (size_t i = 0; i < matrix.size()-1; i++)
    {
        std::cout << "[";
        for (size_t j = 0; j < matrix[i].size()-1; j++)
        {
            std::cout << matrix[i][j] << " ,";
        }
        std::cout << matrix[i][matrix[i].size()-1];
        std::cout << "], ";
    }
    std::cout << "[";
        for (size_t m = 0; m < matrix[matrix.size()-1].size()-1; m++)
        {
            std::cout << matrix[matrix.size()-1][m] << " ,";
        }
        std::cout << matrix[matrix.size()-1][matrix[matrix.size()-1].size()-1];
        std::cout << "]";
    std::cout << std::endl;
}


// Method to get the adjacency matrix
const std::vector<std::vector<int>> Graph:: getMatrix() const
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


/*
Operator overloading for the addition of two graphs
we will get new graph
maybe edges will be added
*/ 
Graph Graph::operator+(const Graph &g){
Graph result;
if (matrix.size() != g.getMatrix().size()){
    throw std::invalid_argument("The matrixes are not the same size");
}
size_t size =matrix.size();
vector<vector<int>> new_matrix(size , vector<int>(size,0));
for (size_t i = 0 ; i < size ;i++){
    for (size_t j = 0 ; j < size ;j++){
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
Graph Graph::operator-(const Graph &g){
Graph result;
if (matrix.size() != g.getMatrix().size()){
    throw std::invalid_argument("The matrixes are not the same size");
}
size_t size =matrix.size();
vector<vector<int>> new_matrix(size , vector<int>(size,0));
for (size_t i = 0 ; i < size ;i++){
    for (size_t j = 0 ; j < size ;j++){
        new_matrix[i][j] = matrix[i][j] - g.matrix[i][j];
    }
}
result.loadGraph(new_matrix);
return result;
}
/*
Operator += performs a subtraction opertion to the graph that we get as a parameter.
*/
Graph& Graph::operator+=(const Graph &g){
if (matrix.size() != g.getMatrix().size()){
    throw std::invalid_argument("The matrixes are not the same size");
}
*this= *this + g;
return *this;
    }

/*
Operator -= performs a add opertion to the graph that we get as a parameter.
*/
    Graph& Graph::operator-=(const Graph &g){
if (this->getMatrix().size() != g.getMatrix().size()){
    throw std::invalid_argument("The matrixes are not the same size");
}
*this= *this - g;
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
use the * operator to multiply the graph by -1
*/
    Graph &ariel::Graph::operator-()
    {
       return  (*this) * -1;
    }



    Graph& ariel::Graph::operator++() // ++g prefix increment
    {
         if (matrix.empty()){
            throw std::invalid_argument("The matrix is empty");
        }
        size_t size = matrix.size();
         for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size ; j++)
            {
                if (matrix[i][j] != 0)// only if we have an edge
                {
                    matrix[i][j] = matrix[i][j] + 1;
                }
            }
        }
        return *this;
    }

    Graph ariel::Graph::operator++(int)// g++ postfix increment
    {
        if (matrix.empty()){
            throw std::invalid_argument("The matrix is empty");
        }
        Graph newGraph = *this;
        size_t size = matrix.size();
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                if (matrix[i][j] != 0)//only if we have an edge
                {
                    matrix[i][j] = matrix[i][j] + 1;
                }
            }
        }
        return newGraph;
    }
    


/*
opretor overloading for the multiplication of a graph by a scalar
*/
    Graph& ariel::Graph::operator*(int scalar)
    {
        if (matrix.empty()){
            throw std::invalid_argument("The matrix is empty");
        }
        for (size_t i = 0; i < matrix.size(); i++)
        {
            for (size_t j = 0; j < matrix[i].size(); j++)
            {
                matrix[i][j] = matrix[i][j] *scalar;
            }
        }
        return *this;
    }




















// // Operator overloading for the addition of two graphs
// Graph ariel::operator+(Graph &g1, Graph &g2)
// {
//     std::vector<std::vector<int>> matrix1 = g1.getMatrix();
//     std::vector<std::vector<int>> matrix2 = g2.getMatrix();

//     if (matrix1.size() != matrix2.size())
//     {
//         // If the matrices are not the same size, they cannot be added
//         throw std::invalid_argument("The matrices are not the same size");
//     }

//     std::vector<std::vector<int>> result;
//     for (size_t i = 0; i < matrix1.size(); i++)
//     {
//         std::vector<int> row;
//         for (size_t j = 0; j < matrix1[i].size(); j++)
//         {
//             row.push_back(matrix1[i][j] + matrix2[i][j]);
//         }
//         result.push_back(row);
//     }

//     Graph g;
//     g.loadGraph(result);
//     return g;
// }

// // molitiply 2 matrix
// Graph ariel::operator*(Graph &g1, Graph &g2)
// {
//     std::vector<std::vector<int>> matrix1 = g1.getMatrix();
//     std::vector<std::vector<int>> matrix2 = g2.getMatrix();

//     if (matrix1.size() != matrix2[0].size())
//     {
//         // If the number of columns in the first matrix is not equal to the number of rows in the second matrix, they cannot be multiplied
//         throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
//     }

//     std::vector<std::vector<int>> result;
//     for (size_t i = 0; i < matrix1.size(); i++)
//     {
//         std::vector<int> row;
//         for (size_t j = 0; j < matrix2[i].size(); j++)
//         {
//             int sum = 0;
//             for (size_t k = 0; k < matrix1[i].size(); k++)
//             {
//                 sum += matrix1[i][k] * matrix2[k][j];
//             }
//             row.push_back(sum);
//         }
//         result.push_back(row);
//     }

//     Graph g;
//     g.loadGraph(result);
//     return g;
// }
  

// // Operator overloading for the division of a graph by a scalar

// Graph Graph::operator/=(int scalar)
// {
//     if (scalar == 0)
//     {
//         // If the scalar is zero, the division is not possible
//         throw std::invalid_argument("Division by zero");
//     }

//     std::vector<std::vector<int>> result;
//     for (size_t i = 0; i < matrix.size(); i++)
//     {
//         std::vector<int> row;
//         for (size_t j = 0; j < matrix[i].size(); j++)
//         {
//             row.push_back(matrix[i][j] / scalar);
//         }
//         result.push_back(row);
//     }

//     Graph g;
//     g.loadGraph(result);
//     return g;
// }

// // Operator overloading for the output stream
// // std::ostream &ariel::operator<<(std::ostream &os, Graph &graph)
// // {
// //     graph.printGraph();
// //     for (size_t i = 0; i < graph.getMatrix().size(); i++)
// //     {
// //         for (size_t j = 0; j < graph.getMatrix()[i].size(); j++)
// //         {
// //             os << graph.getMatrix()[i][j] << " ";
// //         }
// //         os << std::endl;
// //     }
// //     return os;
// // }

// // Operator overloading for the multiplication of a graph by a scalar
// Graph Graph::operator*=(int scalar)
// {
//     std::vector<std::vector<int>> result;
//     for (size_t i = 0; i < matrix.size(); i++)
//     {
//         std::vector<int> row;
//         for (size_t j = 0; j < matrix[i].size(); j++)
//         {
//             row.push_back(matrix[i][j] * scalar);
//         }
//         result.push_back(row);
//     }

//     this->loadGraph(result);
//     return *this;

// }






