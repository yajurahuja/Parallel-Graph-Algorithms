#include "../headers/allHeaders.h"


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


long Vertex::getDataValue()
{
    return p_dataVal;
}


long Vertex::getId()
{
    return p_id;
}

std::vector<long> Vertex::getOutNeighbours()
{
    return OutNeighbours;
}
std::vector<long> Vertex::getInNeighbours()
{
    return InNeighbours;
}

std::vector<long>::const_iterator Vertex::getOutNeighboursBegin() const
{
    return OutNeighbours.begin();
}
std::vector<long>::const_iterator Vertex::getOutNeighboursEnd() const
{
    return OutNeighbours.end();
}
std::vector<long>::const_iterator Vertex::getInNeighboursBegin() const
{
    return InNeighbours.begin();
}
std::vector<long>::const_iterator Vertex::getInNeighboursEnd() const
{
    return InNeighbours.end();
}

long Vertex::getOutDegree()
{
    return OutNeighbours.size();
}
long Vertex::getInDegree()
{
    return InNeighbours.size();
}

void Vertex::addOutDegree(long v)
{   
    OutNeighbours.push_back(v);
}
void Vertex::addInDegree(long v)
{
    InNeighbours.push_back(v);
}
