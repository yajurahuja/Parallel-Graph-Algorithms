#include "../headers/interface.h"
#include <filesystem>

bool OddEven(long vertex); //Interface functions
bool OddEven_(long v1Id, long v2Id); // Interface functions

int main(int argc, char** argv)
{
    long graphNumber = strtol(argv[1], NULL, 10);
    std::cout << "Entered into main fxn" << std::endl;


    //!Getting the current path
    auto currPath = std::filesystem::current_path().string();
    std::string fileName = currPath + std::string("/test/tempGraph.json");
    //This is for testing purposes.
    std::vector<int> vertices;
    std::vector<std::pair<int,int>> edges;
    AuxFxns::LoadGraphFromJason(graphNumber, fileName, vertices, edges);


    //!Create objects of singlton classes
    //!These will ensure unique id, make sure to destroy them at the end
    VertexIdTracker * g_vidManager = VertexIdTracker::getInstance();


    Graph graph;

    //!Hash table fetching node id from node value
    std::unordered_map<int, int> table_dataValueToUniqueId;
    //!Adding vertices to the graph
    for(int nodeIndex = 0; nodeIndex < vertices.size(); ++nodeIndex)
    {
        std::shared_ptr<Vertex> newVertex =  std::make_shared<Vertex>(vertices[nodeIndex]);
        graph.AddNodeInGraph(g_vidManager->GetLastGeneratedIdIndex(), newVertex);
        table_dataValueToUniqueId.insert({newVertex->getDataValue(),g_vidManager->GetLastGeneratedIdIndex()});
    }
    //!Adding edges to the graph and stoding vertex neighbourhood
    for(int edgeIndex = 0; edgeIndex < edges.size(); ++edgeIndex)
    {
        std::shared_ptr<Edge> currEdge = std::make_shared<Edge>(table_dataValueToUniqueId[edges[edgeIndex].first],
                                                                    table_dataValueToUniqueId[edges[edgeIndex].second],
                                                                    1.);
        graph.AddEdgeInGraph(currEdge); 
    }


    //Testing: Graph Creation
    std::cout<<"Graph Creation"<<std::endl;
    std::cout<<"Number of vertices:"<<graph.getNumberVertices()<<std::endl;
    std::cout<<"Number of edges:"<<graph.getNumberEdges()<<std::endl;
    
    for(int i = 1; i <= graph.getNumberVertices(); i++)
    {
        std::cout<<graph.getVertex(i).getId()<<" ";
    }
    std::cout<<std::endl;
    for(int i = 1; i <= graph.getNumberVertices(); i++)
    {
        Vertex v = graph.getVertex(i);
        std::cout<<"V ID:"<<v.getId() - 1<<std::endl;
        std::cout<<"V Data:"<<v.getDataValue()<<std::endl;
        std::cout<<"V Out Degree:"<<v.getOutDegree()<<std::endl;
        PrintV::printVector(v.getOutNeighbours());
        std::cout<<"V In Degree:"<<v.getInDegree()<<std::endl;
        PrintV::printVector(v.getInNeighbours());

    }

    //Testing: Remove function
    std::vector<long> v = {1, 2, 3, 4, 5, 1, 2, 7, 8, 8};
    PrintV::printVector(v);
    std::set<long> s = Interface::convertToSet(v);
    v.assign(s.begin(), s.end());
    PrintV::printVector(v);


    //!Destroying the singlton objects
    

    //Testing: Vertex subset functions
    std::vector<long> a{4, 3, 2};
    VertexSubset s_;
    s_.setVertexSubset(a);
    s_.printVertexSubset();
    std::cout<<"Vertex Subset length:"<<s_.getVertexSubsetLength()<<std::endl;
    std::cout<<"Vertex Subset Outdegree:"<<s_.getVertexSubsetOutDegree(graph)<<std::endl;


    //Testing: VertexMap
    VertexSubset o = Interface::VertexMap(s_, &OddEven);
    o.printVertexSubset();

    //Testing EdgeMapSparse
    s_.printVertexSubset();
    VertexSubset o = Interface::EdgeMapSparse(graph, s_, &OddEven_, &OddEven);
    o.printVertexSubset();

    //Testing: EdgeMapDense and EdgeMapDenseWrite

    //Testing EdgeMapDense
    s_.printVertexSubset();
    VertexSubset o = Interface::EdgeMapDenseWrite(graph, s_, &OddEven_, &OddEven);
    o.printVertexSubset();



    std::cout << "Exited into main fxn" << std::endl;
    g_vidManager->DestroyIdManager();
    return 0;
}

bool OddEven(long vertexId)
{
    if(vertexId % 2 == 1)
        return true;
    return false;
}

bool OddEven_(long v1Id, long v2Id)
{
    if((v1Id + v2Id) % 2 == 1)
        return true;
    return false;
}