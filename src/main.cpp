#include "../headers/interface.h"
#include <filesystem>



int main()
{
    std::cout << "Entered into main fxn" << std::endl;


    //!Getting the current path
    auto currPath = std::filesystem::current_path().string();
    std::string fileName = currPath + std::string("/test/tempGraph.json");
    //This is for testing purposes.
    std::vector<int> vertices;
    std::vector<std::pair<int,int>> edges;
    AuxFxns::LoadGraphFromJason(fileName, vertices, edges);


    //!Create objects of singlton classes
    //!These will ensure unique id, make sure to destroy them at the end
    VertexIdTracker * g_vidManager = VertexIdTracker::getInstance();


    Graph graph1;

    //!Hash table fetching node id from node value
    std::unordered_map<int, int> table_dataValueToUniqueId;
    //!Adding vertices to the graph
    for(int nodeIndex = 0; nodeIndex < vertices.size(); ++nodeIndex)
    {
        std::shared_ptr<Vertex> newVertex =  std::make_shared<Vertex>(vertices[nodeIndex]);
        graph1.AddNodeInGraph(g_vidManager->GetLastGeneratedIdIndex(), newVertex);
        table_dataValueToUniqueId.insert({newVertex->getDataValue(),g_vidManager->GetLastGeneratedIdIndex()});
    }
    //!Adding edges to the graph and stoding vertex neighbourhood
    for(int edgeIndex = 0; edgeIndex < edges.size(); ++edgeIndex)
    {
        std::shared_ptr<Edge> currEdge = std::make_shared<Edge>(table_dataValueToUniqueId[edges[edgeIndex].first],
                                                                    table_dataValueToUniqueId[edges[edgeIndex].second],
                                                                    1.);
        graph1.AddEdgeInGraph(currEdge); 
    }






    //!Destroying the singlton objects
    g_vidManager->DestroyIdManager();

    std::cout << "Exited into main fxn" << std::endl;

    return 0;
}