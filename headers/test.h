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
   //bool FxnOddEven(long vertexId);
   //bool FxnOddEven_(long v1Id, long v2Id);
    std::vector<long> GenerateRandomIntegers(long minInteger, long maxInteger, long totalNumbers);

    void TestVertexSubset(Graph &g,
                          VertexSubset &vs,
                          long nodesCountInSubset,
                          std::string &logFile);

    void DoTestingOnThisGraph(Graph &currGraph, std::string &logFile);

    //bool CompareLayers(std::deque<std::atomic<long>> &layers, std::deque<long> &layers_s);
    void TestBFS(Graph& currGraph, long root);
    bool CompareLayers(long* layers, long* layers_s);
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

};

#endif