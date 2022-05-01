#include "../headers/allHeaders.h"


Graph::Graph()
{
    VertexIdTracker::getInstance();
}

Graph::~Graph()
{
    VertexIdTracker::getInstance()->DestroyIdManager();
}

Graph::Graph(std::string &fileName)
{
    VertexIdTracker::getInstance();

    std::vector<long> vertices;
    std::vector<std::pair<long,long> > edges;
    std::vector<double> weights;
    // bool readingSuccess = AuxFxns::LoadGraphFromTxtFiles(0, 
    //                                                      fileName, 
    //                                                      vertices, 
    //                                                      edges,
    //                                                      weights);

    bool readingSuccess = AuxFxns::LoadUndirectedGraphFromTxtFiles(0, 
                                                                     fileName, 
                                                                     vertices, 
                                                                     edges,
                                                                     weights);

     if(readingSuccess)
         std::cout << "Graph reading from " << fileName << " successful" << std::endl;

    //!Hash table fetching node id from node value
    std::unordered_map<long, long> table_dataValueToUniqueId;
    //!Adding vertices to the graph
    for(long nodeIndex = 0; nodeIndex < vertices.size(); ++nodeIndex)
    {
        std::shared_ptr<Vertex> newVertex =  std::make_shared<Vertex>(vertices[nodeIndex]);
        AddNodeInGraph(VertexIdTracker::getInstance()->GetLastGeneratedIdIndex(), newVertex);
        table_dataValueToUniqueId.insert({newVertex->getDataValue(),VertexIdTracker::getInstance()->GetLastGeneratedIdIndex()});
    }
    //!Adding edges to the graph and stoding vertex neighbourhood
    for(long edgeIndex = 0; edgeIndex < edges.size(); ++edgeIndex)
    {
        long firstNodeDataValue = edges[edgeIndex].first;
        long secondNodeDataValue = edges[edgeIndex].second;
        double weight = weights[edgeIndex];
        std::shared_ptr<Edge> currEdge = std::make_shared<Edge>(table_dataValueToUniqueId[firstNodeDataValue],
                                                                    table_dataValueToUniqueId[secondNodeDataValue],
                                                                    weight);
        AddEdgeInGraph(currEdge);
    }
    
}

bool Graph::AddNodeInGraph(long uniqueNodeId, std::shared_ptr<Vertex> &node)
{
    p_table_uniqueNodeToVertex.insert({uniqueNodeId, node});
    return true;
} 

bool Graph::AddEdgeInGraph(std::shared_ptr<Edge> &edge) //Done 
{
    p_edges.push_back(edge);
    Edge e = *edge;
    Vertex *start = getVertexPointer(e.getStartVertexId());
    Vertex *end = getVertexPointer(e.getEndVertexId());
    start->addOutDegree(end->getId());
    end->addInDegree(start->getId());
    std::pair<long, long> p(e.getStartVertexId(), e.getEndVertexId());
    
    weights.insert({p, e.getWeight()});
    return true;
}

Vertex Graph::getVertex(long v) const
{
    return *p_table_uniqueNodeToVertex.at(v);
}

Vertex* Graph::getVertexPointer(long v) const
{
    return p_table_uniqueNodeToVertex.at(v).get();
}

Edge* Graph::getEdgePointer(long e) const
{
    return p_edges.at(e).get();
}

long Graph::getNumberVertices() const
{
    return p_table_uniqueNodeToVertex.size();
}
long Graph::getNumberEdges() const
{
    return p_edges.size();
}

double Graph::getEdgeWeight(long start, long end) const
{
    //TO DO: get edge using start and end vertex
    std::pair<long, long> p(start, end);
    return weights.at(p);
}