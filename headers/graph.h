#ifndef GRAPH_H
#define GRAPH_H

//#include "../headers/allHeaders.h"

#include<string>
#include<vector>
#include<memory>
#include<unordered_map>

class Vertex;
class Edge;


class Graph
{
    public:
    Graph();
    Graph(std::string &fileName);
    ~Graph();

    bool AddNodeInGraph(int uniqueNodeId, std::shared_ptr<Vertex> &node);

    bool AddEdgeInGraph(std::shared_ptr<Edge> &edge);//Done
    std::unordered_map<int, std::shared_ptr<Vertex> > getGraphTable(); //TO DO
    Vertex getVertex(long v) const;
    Vertex* getVertexPointer(long v) const;
    long getNumberVertices() const;
    long getNumberEdges() const;
    
    private:
    std::unordered_map<long, std::shared_ptr<Vertex> > p_table_uniqueNodeToVertex;
    std::vector<std::shared_ptr<Edge> > p_edges;

};

#endif