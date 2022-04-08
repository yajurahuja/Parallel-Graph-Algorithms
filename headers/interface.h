#ifndef INTERFACE_H
#define INTERFACE_H

#include<string>
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <memory>
#include <unordered_map>
#include <functional>

//Data structures for the graph

class VertexIdTracker
{
    private:
    VertexIdTracker();      //!For singlton pattern
    ~VertexIdTracker();

    public:
    friend class Vertex;
    static VertexIdTracker * getInstance();
    void DestroyIdManager();

    //!Modifiers
    long FetchNewId();

    //!Access Functions
    long GetLastGeneratedIdIndex();

    //!Data members
    private:
    static VertexIdTracker * vertexIdManager;
    long p_vertexIdsUsedTill;
};


class Vertex
{
    public:        

    //!Constructor
    Vertex();
    Vertex(long value);
    long GetDataValue();

    private:
    long p_id;      //!Identifier

    long p_dataVal; //!Data supplied as input


};

class Edge
{
    public:
    Edge(long startVertexId, long endVertexId);
    Edge(long startVertexId, long endVertexId, double weight);

    private:
    long p_start_vertexId;
    long p_end_vertexId;
    double p_weight;
};

class Graph
{
    public:
    Graph();
    bool AddNodeInGraph(int uniqueNodeId, std::shared_ptr<Vertex> &node);
    bool AddEdgeInGraph(std::shared_ptr<Edge> &edge);


    private:
    std::unordered_map<int, std::shared_ptr<Vertex> > p_table_uniqueNodeToVertex;
    std::vector<std::shared_ptr<Edge> > p_edges;

};


class VertexSubset
{
    public:

    private:
    std::vector<long > p_vertices;
};


class AuxFxns
{
    public:
    static bool LoadGraphFromJason(const std::string &filename, std::vector<int> &vertices, std::vector<std::pair<int, int> > &edges);
};

class Inferface
{
    public:
    static VertexSubset EdgeMap(const Graph &graph,
                                const VertexSubset &U,
                                std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                std::function<bool(long vertexIndex)> &C);

    static VertexSubset VertexMap(const VertexSubset &U,
                                std::function<bool(long startVertexIndex, long endVertexIndex)> &F);
};

#endif //!Ending header include gaurds