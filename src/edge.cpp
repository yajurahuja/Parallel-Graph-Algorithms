#include "../headers/allHeaders.h"

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


long Edge::getStartVertexId()
{
    return p_start_vertexId;
}

long Edge::getEndVertexId()
{
    return p_end_vertexId;
}

//double Edge::getWeight()
long Edge::getWeight()
{
    return p_weight;
}
