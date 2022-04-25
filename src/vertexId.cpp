#include "../headers/allHeaders.h"


VertexIdTracker * VertexIdTracker::vertexIdManager = nullptr;

VertexIdTracker::VertexIdTracker()
{
    p_vertexIdsUsedTill = -1;
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
    if(vertexIdManager != nullptr)
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

