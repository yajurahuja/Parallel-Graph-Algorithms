#include "../headers/interface.h"
#include "../ext/json.hpp"
using json = nlohmann::json;

VertexIdTracker * VertexIdTracker::vertexIdManager = nullptr;

VertexIdTracker::VertexIdTracker()
{
    p_vertexIdsUsedTill = 0;
}

VertexIdTracker::~VertexIdTracker()
{
    //!Do nothing
}

VertexIdTracker * VertexIdTracker::getInstance()
{
    if(vertexIdManager == nullptr)
    {
        vertexIdManager  = new VertexIdTracker;
    }
    return  vertexIdManager;
}

void VertexIdTracker::DestroyIdManager()
{
    if(vertexIdManager == nullptr)
    {
        delete vertexIdManager;
        vertexIdManager = nullptr;
    }
}

long VertexIdTracker::FetchNewId()
{ 
    p_vertexIdsUsedTill++;
    return p_vertexIdsUsedTill;
}

long VertexIdTracker::GetLastGeneratedIdIndex()
{
    return p_vertexIdsUsedTill;
}

//!Vertex class
Vertex::Vertex()
{
    p_dataVal = 0;
    p_id = VertexIdTracker::getInstance()->FetchNewId();
}

Vertex::Vertex(long value)
{
    p_dataVal = value;
    p_id = VertexIdTracker::getInstance()->FetchNewId();
}

long Vertex::GetDataValue()
{
    return p_dataVal;
}


Edge::Edge(long startVertexId, long endVertexId)
{
    p_start_vertexId = startVertexId;
    p_end_vertexId = endVertexId;
    p_weight = 1;
}

Edge::Edge(long startVertexId, long endVertexId, double weight)
{
    p_start_vertexId = startVertexId;
    p_end_vertexId = endVertexId;
    p_weight = weight;
}

Graph::Graph()
{

}

bool Graph::AddNodeInGraph(int uniqueNodeId, std::shared_ptr<Vertex> &node)
{
    p_table_uniqueNodeToVertex.insert({uniqueNodeId, node});
    return true;
}

bool Graph::AddEdgeInGraph(std::shared_ptr<Edge> &edge)
{
    p_edges.push_back(edge);
    return true;
}



bool AuxFxns::LoadGraphFromJason(const std::string &filename, std::vector<int> &vertices, std::vector<std::pair<int, int> > &edges)
{
	// Load json data from scene file
	json data;
	std::ifstream in(filename);
	in >> data;

    //!Count
    long nodesCount = data["Graph1"]["VertexCount"][0];
    long edgesCount = data["Graph1"]["EdgeCount"][0];

    for(int i = 0; i < nodesCount; ++i)
    {
        vertices.push_back(int(data["Graph1"]["Vertex"][i]));
    }

    for(int i = 0; i < edgesCount; ++i)
    {
        int s = data["Graph1"]["Edge"][i][0];
        int e = data["Graph1"]["Edge"][i][1];
    }
    return true;
}

