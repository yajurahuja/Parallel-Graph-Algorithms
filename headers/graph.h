#ifndef GRAPH_H
#define GRAPH_H

//#include "../headers/allHeaders.h"

#include<string>
#include<vector>
#include<memory>
#include<unordered_map>
#include<utility>
#include<functional>

class Vertex;
class Edge;

struct HASH{
    size_t operator()(const std::pair<long, long>& p) const
    {
        auto hash1 = std::hash<long>{}(p.first);
        auto hash2 = std::hash<long>{}(p.second);
 
        if (hash1 != hash2) {
            return hash1 ^ hash2;             
        }
         
        // If hash1 == hash2, their XOR is zero.
          return hash1;
    }
};


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
    Edge* getEdgePointer(long e) const;
    long getNumberVertices() const;
    long getNumberEdges() const;
    double getEdgeWeight(long start, long end) const;
    
    private:
    std::unordered_map<long, std::shared_ptr<Vertex> > p_table_uniqueNodeToVertex;
    std::vector<std::shared_ptr<Edge> > p_edges;
    std::unordered_map<std::pair<long, long>, double, HASH> weights;

};

#endif