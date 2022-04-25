#ifndef INTERFACE_H
#define INTERFACE_H

//#include "../headers/allHeaders.h"

#include<string>
#include <iostream>

#include <stdlib.h>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <utility>
#include <memory>
#include <unordered_map>
#include <functional>
#include <omp.h>


//printing functions

class PrintV
{
    public:
    static void printVector(std::vector<long> v);
};

class VertexSubset;
class Graph;
class Vertex;

class Interface
{
    public:

    static std::set<long> convertToSet(std::vector<long> &v);

    static void RemoveDuplicates(VertexSubset &U); //TO DO: This function removes the duplicates from a vector

    static VertexSubset EdgeMap(const Graph &graph,
                                const VertexSubset &U,
                                const std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                const std::function<bool(long vertexIndex)> &C, long threshold); //Done : Tested

    static VertexSubset VertexMap(const VertexSubset &U, 
                                        const std::function<bool(long vertexIndex)> &F); //Done : Tested

    //private: 

    static VertexSubset EdgeMapSparse(const Graph &graph,
                                const VertexSubset &U,
                                const std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                const std::function<bool(long vertexIndex)> &C); //Done : Tested

    static VertexSubset EdgeMapDense(const Graph &graph,
                                const VertexSubset &U,
                                const std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                const std::function<bool(long vertexIndex)> &C); //Done : Tested

    static VertexSubset EdgeMapDenseWrite(const Graph &graph,
                                const VertexSubset &U,
                                const std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                const std::function<bool(long vertexIndex)> &C); //Done : Tested


};
#endif //!Ending header include gaurds