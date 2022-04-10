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
std::vector<long> Vertex::getInNieghbours()
{
    return InNieghbours;
}

long Vertex::getOutDegree()
{
    return OutNeighbours.size();
}
long Vertex::getInDegree()
{
    return InNieghbours.size();
}

void Vertex::addOutDegree(long v)
{   
    OutNeighbours.push_back(v);
}

void Vertex::addInDegree(long v)
{
    InNieghbours.push_back(v);
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

long Edge::getStartVertexId()
{
    return p_start_vertexId;
}

long Edge::getEndVertexId()
{
    return p_end_vertexId;
}

double Edge::getWeight()
{
    return p_weight;
}

Graph::Graph()
{

}

bool Graph::AddNodeInGraph(int uniqueNodeId, std::shared_ptr<Vertex> &node)
{
    p_table_uniqueNodeToVertex.insert({uniqueNodeId, node});
    return true;
} 

bool Graph::AddEdgeInGraph(std::shared_ptr<Edge> &edge) //Done 
{
    p_edges.push_back(edge);
    Edge e = *edge;
    Vertex start = getVertex(e.getStartVertexId());
    Vertex end = getVertex(e.getEndVertexId());
    start.addOutDegree(end.getId());
    end.addInDegree(start.getId());
    return true;
}

Vertex Graph::getVertex(long v) const
{
    return *p_table_uniqueNodeToVertex.at(v);
}

long Graph::getNumberVertices() const
{
    return p_table_uniqueNodeToVertex.size();
}

std::vector<long> VertexSubset::getVertexSubset() const
{
    return p_vertices;
}

long VertexSubset::getVertexSubsetLength() const
{
    return p_vertices.size();
}
long VertexSubset::getVertexSubsetOutDegree() const
{
    return 0;
}


void VertexSubset::addVertex(long vertex)
{
    p_vertices.push_back(vertex);
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


void Interface::RemoveDuplicates(VertexSubset &U) //TO DO: This function removes the duplicates from a vector
{
    return;
}


VertexSubset Interface::EdgeMap(const Graph &graph,
                                const VertexSubset &U,
                                std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                std::function<bool(long vertexIndex)> &C, long threshold)
{
    if(U.getVertexSubsetLength() + U.getVertexSubsetOutDegree() > threshold)
        return EdgeMapDense(graph, U, F, C);
    else
        return EdgeMapSparse(graph, U, F, C);
}

VertexSubset Interface::EdgeMapSparse(const Graph &graph,
                                const VertexSubset &U,
                                std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                std::function<bool(long vertexIndex)> &C)
{
    VertexSubset Out; 
    //std::vector<long>::iterator v;
    //std::vector<long>::iterator ngh;
    //TO DO: parallel
    for(auto v = U.getVertexSubset().begin(); v < U.getVertexSubset().end(); v++)
    {
        Vertex v_ = graph.getVertex(*v);
        //TO DO: parallel
        for(auto ngh = v_.getOutNeighbours().begin(); ngh < v_.getOutNeighbours().end(); ngh++)
            if(C(*ngh) == 1 && F(*v, *ngh) == 1)
                Out.addVertex(*ngh);
    }
    RemoveDuplicates(Out); //TO DO: confirm if it remains in the scope
    return Out;
}

//To Do: Does it need to iterate from i = 1...|V| or can we do it in the way it is stored in the map


VertexSubset Interface::EdgeMapDense(const Graph &graph,
                                const VertexSubset &U,
                                std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                std::function<bool(long vertexIndex)> &C)
{
    VertexSubset Out;
    //std::vector<long>::iterator ngh;
    //TO DO: Pparallel
    // Vertex indexing starts from 1
    for(long i = 1; i <= graph.getNumberVertices(); i++)
        if (C(i) == 1)
            for(auto ngh = graph.getVertex(i).getInNieghbours().begin(); ngh < graph.getVertex(i).getInNieghbours().end(); ngh++)
            {
                if(std::find(U.getVertexSubset().begin(), U.getVertexSubset().end(), *ngh) != U.getVertexSubset().end() && F(*ngh, i) == 1)
                    Out.addVertex(i);
                if(C(i) == 0)
                    break;

            }
    return Out;
    
}

VertexSubset EdgeMapDenseWrite(const Graph &graph,
                                const VertexSubset &U,
                                std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                std::function<bool(long vertexIndex)> &C)
{
    VertexSubset Out;
    //std::vector<long>::iterator ngh;
    // TO DO: parallel
    for(long i = 1; i <= graph.getNumberVertices(); i++)
        if(std::find(U.getVertexSubset().begin(), U.getVertexSubset().end(), i) != U.getVertexSubset().end())
        {
            //TO DO: parallel
            for(auto ngh = graph.getVertex(i).getOutNeighbours().begin(); ngh < graph.getVertex(i).getOutNeighbours().end(); ngh++)
                if(C(*ngh) == 1 && F(i, *ngh) == 1)
                    Out.addVertex(*ngh);  
        }
    return Out;

}

VertexSubset Interface::VertexMap(const VertexSubset &U, 
                                         std::function<bool(long vertexIndex)> &F)
{
    VertexSubset Out;
    //TO DO: parallel
    for(auto v = U.getVertexSubset().begin(); v < U.getVertexSubset().end(); v++)
        if(F(*v))
            Out.addVertex(*v);
    
    return Out;
}   
