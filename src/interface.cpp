#include "../headers/interface.h"
#include "../ext/json.hpp"
using json = nlohmann::json;

VertexIdTracker * VertexIdTracker::vertexIdManager = nullptr;
EdgeIdTracker * EdgeIdTracker::edgeIdManager = nullptr;

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


EdgeIdTracker::EdgeIdTracker()
{
    p_edgeIdsUsedTill = 0;
}

EdgeIdTracker::~EdgeIdTracker()
{
    //!Do nothing
}

EdgeIdTracker * EdgeIdTracker::getInstance()
{
    if(edgeIdManager == nullptr)
    {
        edgeIdManager = new EdgeIdTracker;
    }
    return edgeIdManager;
}

void EdgeIdTracker::DestroyIdManager()
{
    if(edgeIdManager == nullptr)
    {
        delete edgeIdManager;
        edgeIdManager = nullptr;
    }
}

long EdgeIdTracker::FetchNewId()
{ 
    p_edgeIdsUsedTill++;
    return p_edgeIdsUsedTill;
}

long EdgeIdTracker::GetLastGeneratedIdIndex()
{
    return p_edgeIdsUsedTill;
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
        vertices.push_back(int(data["Graph1"]["Vertex"][0]));
    }

    for(int i = 0; i < edgesCount; ++i)
    {
        int s = data["Graph1"]["Edge"][i][0];
        int e = data["Graph1"]["Edge"][i][1];
    }

    return true;
}