#include "../headers/interface.h"
#include <iostream>
#include <filesystem>


int main()
{
    //!Getting the current path
    auto currPath = std::filesystem::current_path().string();

    //!Create objects of singlton classes
    VertexIdTracker * g_vidManager = VertexIdTracker::getInstance();
    EdgeIdTracker * g_eidManager = EdgeIdTracker::getInstance();

    std::cout << "Entered into main fxn" << std::endl;

    std::string fileName = currPath + std::string("/test/tempGraph.json");    //!Try with relative path
    std::vector<int> vertices;
    std::vector<std::pair<int,int>> edges;
    AuxFxns::LoadGraphFromJason(fileName, vertices, edges);
    
    std::cout << "Testing .vscode files and compilation" << std::endl;
    std::cout << "Test 2" << std::endl;

    //!Destroying the singlton objects
//   g_vidManager->DestroyIdManager();
//   g_eidManager->DestroyIdManager();
    return 0;
}