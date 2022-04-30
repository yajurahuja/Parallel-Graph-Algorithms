#ifndef TEST_H
#define TEST_H

#include<vector>
#include <cstdlib>
#include <functional>
#include <deque>


class VertexSubset;
class Graph;
class Test
{

   public:

    //!Constructor
    Test(std::string  &currPath,
        std::string &dataFileName);
   //bool FxnOddEven(long vertexId);
   //bool FxnOddEven_(long v1Id, long v2Id);
    std::vector<long> GenerateRandomIntegers(long minInteger, long maxInteger, long totalNumbers);



    void TestVertexSubset(Graph &g,
                          VertexSubset &vs,
                          long nodesCountInSubset,
                          std::string &logFile);

    void DoTestingOnThisGraph(Graph &currGraph);

    //bool CompareLayers(std::deque<std::atomic<long>> &layers, std::deque<long> &layers_s);
    bool CompareLayers(Graph &g, std::deque<long> &layers, std::deque<long> &layers_s);
    void TestBFS(Graph& currGraph, long root);
    bool CompareSPs(Graph &g, std::deque<double> &SP, std::deque<double> & SP_s);
    void TestBF(Graph& currGraph, long root);
    //bool CompareLayers(long* layers, long* layers_s);
    //bool CompareParents(std::deque<std::atomic<long>> &parents, std::deque<long> &parents_s);
    

    // void TestVertexMap(VertexSubset &vs, std::function<bool(long id)>);
    // void TestEdgeMapSparse(Graph &g, 
    //                        VertexSubset &s,
    //                        std::function<bool(long id1, long id2)>,
    //                        std::function<bool(long id1, long id2)>);
    // void TestEdgeMapSparse(Graph &g,
    //                        VertexSubset &s,
    //                        std::function<bool(long id1, long id2)>,
    //                        std::function<bool(long id1, long id2)>);

    private:
//    int p_threadsCount;
//    std::string p_logFilePath;
//    std::fstream & p_currFileStream;

    std::string  p_currPath;
    std::string p_dataFileName;


    //!Temp Containers for storing data

    //!These are for bfs: //!Note that

    public: //Making it public, use it wisrely

    // std::vector<long> p_sourceVertices;
    // std::vector<double> p_seqTimesBFS;
    // std::vector<double> p_parallelTimesBFS;
    // std::vector<double> p_speedUpBFS;
    // std::vector<long>   p_maxLayersCount;
    // std::vector<bool> p_comparisonSuccess;

    //!These are for BF
    //!These are for bfs: //!Note that

    std::vector<long> p_BF_sourceVertices;
    std::vector<double> p_BF_seqTimes;
    std::vector<double> p_BF_parTimes;
    std::vector<double> p_BF_speedUp;
    std::vector<bool> p_BF_comparisonSuccess;

    //!Array for short summary data:
    std::vector<int> g_threads;
    std::vector<std::pair<double, double> > g_seqParTimes;
    std::vector<long>g_sourceVertices;
    std::vector<int> g_maxLayersCount;
    std::vector<int> g_speedUps;
    std::vector<bool> g_compSuccess;

    // //!For Bellman Ford
    std::vector<int> b_threads;
    std::vector<std::pair<double, double> > b_seqParTimes;
    std::vector<long>b_sourceVertices;
    std::vector<int> b_speedUps;
    std::vector<bool> b_compSuccess;

};

#endif