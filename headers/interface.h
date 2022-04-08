#ifndef INTERFACE_H
#define INTERFACE_H

#include<string>
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>


//Data structures for the graph

class VertexIdTracker
{
    private:
    VertexIdTracker();      //!For singlton pattern
    ~VertexIdTracker();

    public:
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

class EdgeIdTracker
{
    private:
    EdgeIdTracker();      //!For singlton pattern
    ~EdgeIdTracker();

    public:
    static EdgeIdTracker * getInstance();
    void DestroyIdManager();

    //!Modifiers
    long FetchNewId();

    //!Access Functions
    long GetLastGeneratedIdIndex();

    //!Data members
    private:
    static EdgeIdTracker * edgeIdManager;
    long p_edgeIdsUsedTill;
};


class Vertex
{
    public:        
    //!Constructor
    Vertex();
    Vertex(long vid);

    private:
    long p_id;      //!Identifier

};

class Edge
{
    public:

    private:
    long p_id;      //!Identifier
};

class VertexSubset
{
    public:

    private:

};


class Graph
{
    public:

    private:

};

class AuxFxns
{
    public:
    static bool LoadGraphFromJason(const std::string &filename, std::vector<int> &vertices, std::vector<std::pair<int, int> > &edges);
};

#endif //!Ending header include gaurds