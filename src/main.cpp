#include "../headers/allHeaders.h"

#include <filesystem>
#include <iostream>



int main(int argc, char** argv)
{

    std::cout << "Execution started" << std::endl;

    //!Data files names:

    //!Hard coding all the file Names;
    std::vector<std::string> fileNames;
    fileNames.emplace_back("tinyEWDlong.txt");
    //fileNames.emplace_back("tinyEWD.txt");
    //fileNames.emplace_back("BFtest.txt");
    //fileNames.emplace_back("mediumEWD.txt");
    //fileNames.emplace_back("largeEWD.txt");
    //fileNames.emplace_back("1000EWD.txt");
    //fileNames.emplace_back("10000EWD.txt");

    //!Getting the current path
    auto currPath = std::filesystem::current_path().string();


    const int maxThreads = 128;


    //!Array for short summary data:
    std::vector<std::pair<int, int> > g_threadsFileIndex;
    std::vector<std::pair<double, double> > g_seqParTimes;
    std::vector<long>g_sourceVertices;
    std::vector<int> g_maxLayersCount;
    std::vector<int> g_speedUps;
    std::vector<bool> g_compSuccess;

    //!For Bellman Ford
    std::vector<std::pair<int, int> > b_threadsFileIndex;
    std::vector<std::pair<double, double> > b_seqParTimes;
    std::vector<long>b_sourceVertices;
    std::vector<int> b_speedUps;
    std::vector<bool> b_compSuccess;



    //!Looping over threads
    for(int iThreads = 1; iThreads <= maxThreads; ++iThreads)
    {
        int currThreadsCount = iThreads;

            std::fstream fileStream(logFile, std::ios::app);            

        for(size_t fileCount = 0; fileCount < fileNames.size(); ++fileCount)    //!Do all operations in this loop
        {
            auto currFileName = fileNames[fileCount];
            std::string currFileNameAppended =  std::string("/data/") + currFileName; //!Data extended

            //!Logging file path
            std::string fulLogPath = currPath + std::string("/test/log_") + std::string("num_threads_") + std::to_string(currThreadsCount) + std::string("_file_name_") + currFileName;


            std::fstream fileStream(fulLogPath, std::ios::out);
            fileStream << " " << std::endl;
            fileStream << " " << std::endl;
            fileStream << " " << std::endl;
            fileStream << " " << std::endl;
            fileStream << "================" << std::endl;
            fileStream << "================" << std::endl;
            fileStream << "New Run" << std::endl;


            std::string fullFilePath = currPath + currFileNameAppended;
            Graph currGraph(fullFilePath);

            Test test(currThreadsCount, fulLogPath, fileStream);
            test.DoTestingOnThisGraph(currGraph, fulLogPath);

            //!At this point, for every graph, with given number of threads, some random calculations, have been done


            //!Find maximum speed up element in bfs:

            auto bfs_max_speedup = std::max_element(test.p_speedUpBFS.begin(), test.p_speedUpBFS.end());
            auto index = std::distance(bfs_max_speedup, test.p_speedUpBFS.begin());

            //!Push this data for BFS
            g_threadsFileIndex.push_back(std::make_pair(currThreadsCount, fileCount));
            g_seqParTimes.push_back(std::make_pmair(test.p_seqTimesBFS[index],test.p_parallelTimesBFS[index]));
            g_maxLayersCount.push_back(test.p_maxLayersCount[index]);
            g_speedUps.push_back(test.p_speedUpBFS[index]);
            g_sourceVertices.push_back(test.p_sourceVertices[index]);
            g_compSuccess.push_back(test.p_comparisonSuccess[index]);

            auto bf_max_speedup = std::max_element(test.p_BF_speedUp.begin(), test.p_BF_speedUp.end());
            auto bf_index = std::distance(bf_max_speedup, test.p_BF_speedUp.begin());

            b_threadsFileIndex.push_back(std::make_pair(currThreadsCount, fileCount));
            b_seqParTimes.push_back(std::make_pmair(test.p_BF_seqTimes[bf_index],test.p_BF_parTimes[bf_index]));
            b_speedUps.push_back(p_BF_speedUp[bf_index]);
            b_sourceVertices.push_back(test.p_BF_sourceVertices[bf_index]);
            b_compSuccess.push_back(test.p_BF_comparisonSuccess[bf_index]);

            int tempDebugVar = 0;




        }
    }

    //!Run it in the scope to automatically delete stream object early

    //!Printing summary of BFS
    {
        std::string summaryBFSLog = currPath + std::string("/test/summary_bfs_log.txt");
        std::fstream bfsstream(summaryBFSLog, std::ios::out);
        //!Print the summary log
        bfsstream << "File Name " << " ThreadsCount" << " SourceVertex" << " SeqTime" << " ParTime" << " SpeedUp" << " LayersCountMax" << " Status" << std::endl;
        for(int size_t i = 0; g_threadsFileIndex.size(); ++ i)
        {
            bfsstream << fileNames[g_threadsFileIndex[i].second] << " " << g_threadsFileIndex[i].first << " " << g_sourceVertices[i] << " " << g_seqParTimes[i].first << " " << g_seqParTimes[i].second << " " << g_speedUps[i] << " " << g_maxLayersCount[i] << g_compSuccess[i] << endl;
        }
    }

    //!Printing summary of BF    
    {
        std::string summaryBFLog = currPath + std::string("/test/summary_bf_log.txt");
        std::fstream bfstream(summaryBFLog, std::ios::out);
        //!Print the summary log
        bfsstream << "File Name " << " ThreadsCount" << " SourceVertex" << " SeqTime" << " ParTime" << " SpeedUp" << " Status" << std::endl;
        for(int size_t i = 0; g_threadsFileIndex.size(); ++ i)
        {
            bfsstream << fileNames[b_threadsFileIndex[i].second] << " " << b_threadsFileIndex[i].first << " " << b_sourceVertices[i] << " " << b_seqParTimes[i].first << " " << b_seqParTimes[i].second << " " << b_speedUps[i] << " " <<  b_compSuccess[i] << endl;
        }
    }
//    std::cout << "Exited into main fxn" << std::endl;

    return 0;
}

// int main(int argc, char** argv)
// {
//     if(argc == 1)
//     {
//         std::cout<<"No user input. Exiting..."<<std::endl;
//         return 0;
//     }
//     long graphNumber = strtol(argv[1], NULL, 10);
//     std::cout << "Entered into main fxn" << std::endl;


//     auto currPath = std::filesystem::current_path().string();
//     std::string fileName = currPath + std::string("/test/tempGraph.json");
//     std::vector<int> vertices;
//     std::vector<std::pair<int,int>> edges;
//     AuxFxns::LoadGraphFromJason(graphNumber, fileName, vertices, edges);
//     VertexIdTracker * g_vidManager = VertexIdTracker::getInstance();


//     Graph graph;

//     std::unordered_map<int, int> table_dataValueToUniqueId;
//     for(int nodeIndex = 0; nodeIndex < vertices.size(); ++nodeIndex)
//     {
//         std::shared_ptr<Vertex> newVertex =  std::make_shared<Vertex>(vertices[nodeIndex]);
//         graph.AddNodeInGraph(g_vidManager->GetLastGeneratedIdIndex(), newVertex);
//         table_dataValueToUniqueId.insert({newVertex->getDataValue(),g_vidManager->GetLastGeneratedIdIndex()});
//     }
//     for(int edgeIndex = 0; edgeIndex < edges.size(); ++edgeIndex)
//     {
//         std::shared_ptr<Edge> currEdge = std::make_shared<Edge>(table_dataValueToUniqueId[edges[edgeIndex].first],
//                                                                     table_dataValueToUniqueId[edges[edgeIndex].second],
//                                                                     1.);
//         graph.AddEdgeInGraph(currEdge); 
//     }

//     Test test;
//     test.TestBFS(graph, 0);
//     //!Destroying the singlton objects
//     g_vidManager->DestroyIdManager();

//     std::cout << "Exited into main fxn" << std::endl;

//     return 0;
// }