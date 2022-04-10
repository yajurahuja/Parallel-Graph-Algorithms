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
    long getDataValue();    
    long getId();
    std::vector<long> getOutNeighbours();
    std::vector<long> getInNieghbours();
    long getOutNeighboursSize();
    long getInNieghboursSize();
    long getOutDegree();
    long getInDegree();
    void addOutDegree(long v); //TO DO
    void addInDegree(long v); // TO DO

    private:
    long p_id;      //!Identifier

    long p_dataVal; //!Data supplied as input

    std::vector<long> InNieghbours; //vector storing all the vertex ids of the vertices which have an edge to this vertex
    std::vector<long> OutNeighbours; //vector storing all teh vertex ids of the vertices which have an edge from this vertex


};

class Edge
{
    public:
    Edge(long startVertexId, long endVertexId);
    Edge(long startVertexId, long endVertexId, double weight);

    long getStartVertexId();
    long getEndVertexId();
    double getWeight();

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
    bool AddEdgeInGraph(std::shared_ptr<Edge> &edge);//Done
    std::unordered_map<int, std::shared_ptr<Vertex> > getGraphTable(); //TO DO
    Vertex getVertex(long v) const;
    long getNumberVertices() const;


    private:
    std::unordered_map<long, std::shared_ptr<Vertex> > p_table_uniqueNodeToVertex;
    std::vector<std::shared_ptr<Edge> > p_edges;

};


class VertexSubset
{
    public:
    std::vector<long> getVertexSubset() const; // Done
    long getVertexSubsetLength() const; //Done
    long getVertexSubsetOutDegree() const; // TO DO: is it containing duplicates or the lenght of the set
    void addVertex(long vertex);// Done
    private:
    std::vector<long> p_vertices;
};


class AuxFxns
{
    public:
    static bool LoadGraphFromJason(const std::string &filename, std::vector<int> &vertices, std::vector<std::pair<int, int> > &edges);
};

class Interface
{
    public:

    static void RemoveDuplicates(VertexSubset &U); //TO DO: This function removes the duplicates from a vector

    static VertexSubset EdgeMap(const Graph &graph,
                                const VertexSubset &U,
                                std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                std::function<bool(long vertexIndex)> &C, long threshold); //Done

    static VertexSubset VertexMap(const VertexSubset &U, 
                                         std::function<bool(long vertexIndex)> &F); //Done

    private: 

    static VertexSubset EdgeMapSparse(const Graph &graph,
                                const VertexSubset &U,
                                std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                std::function<bool(long vertexIndex)> &C); //Done

    static VertexSubset EdgeMapDense(const Graph &graph,
                                const VertexSubset &U,
                                std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                std::function<bool(long vertexIndex)> &C); //Done

    static VertexSubset EdgeMapDenseWrite(const Graph &graph,
                                const VertexSubset &U,
                                std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                std::function<bool(long vertexIndex)> &C); //Done

};

#endif //!Ending header include gaurds