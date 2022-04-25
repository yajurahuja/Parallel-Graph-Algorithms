#include "../headers/allHeaders.h"


VertexSubset::VertexSubset()
{
    //Do Nothing
}
VertexSubset::VertexSubset(long v){
        p_vertices.push_back(v);
}

std::vector<long> & VertexSubset::getVertexSubset()
{
    return p_vertices;
}

std::vector<long>::const_iterator VertexSubset::getVertexSubsetBegin() const
{
    return p_vertices.begin();
}
std::vector<long>::const_iterator VertexSubset::getVertexSubsetEnd() const
{
    return p_vertices.end();
}

void VertexSubset::setVertexSubset(std::vector<long> v)
{
    p_vertices.assign(v.begin(), v.end());
}

void VertexSubset::printVertexSubset()
{
    std::cout<<"Vertex Subset Vertices Ids: ";
    for(auto it = p_vertices.begin(); it < p_vertices.end(); it++)
        std::cout<<*it<<" ";
    
    std::cout << std::endl;
}

void VertexSubset::LogIntoFile(std::fstream &out)
{
    out <<"VertexSubset Vertices Ids: ";
    for(auto it = p_vertices.begin(); it < p_vertices.end(); it++)
        out << *it <<" ";

    out << std::endl;
}



long VertexSubset::getVertexSubsetLength() const
{
    return p_vertices.size();
}
long VertexSubset::getVertexSubsetOutDegree(const Graph &graph) const
{
    long total = 0;
    //To DO: parallelize
    for(auto v = p_vertices.begin(); v < p_vertices.end(); v++)
        total += graph.getVertex(*v).getOutDegree();
    return total;
}


void VertexSubset::addVertex(long vertex)
{
    p_vertices.push_back(vertex);
}


