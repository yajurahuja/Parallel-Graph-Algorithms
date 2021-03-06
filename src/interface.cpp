#include "../headers/allHeaders.h"
#include <algorithm>

long total;
long iterations;

std::set<long> Interface::convertToSet(std::vector<long> &v)
{
    v.erase(std::unique(v.begin(), v.end()), v.end());


    std::set<long> s;
    for (auto &x : v) 
        s.insert(x);
    return s;
}

void Interface::RemoveDuplicates(VertexSubset &U) //TO DO: This function removes the duplicates from a vector
{
    U.getVertexSubset().erase(std::unique(U.getVertexSubset().begin(), U.getVertexSubset().end()), U.getVertexSubset().end());
    
    // std::set<long> s = convertToSet(U.getVertexSubset());
    // U.getVertexSubset.clear
    // U.getVertexSubset().assign(s.begin(), s.end());
    // return;
}

VertexSubset Interface::EdgeMap(const Graph &graph,
                            const VertexSubset &U,
                            const std::function<bool(long startVertexIndex, long endVertexIndex, double edgeWeight)> &F,
                            const std::function<bool(long vertexIndex)> &C, long threshold,
                            int threadsCount)
{
    return EdgeMapSparse(graph, U, F, C, threadsCount);
}

VertexSubset Interface::EdgeMap_t(const Graph &graph,
                            const VertexSubset &U,
                            const std::function<bool(long startVertexIndex, long endVertexIndex, double edgeWeight)> &F,
                            const std::function<bool(long vertexIndex)> &C, long threshold,
                            int threadsCount)
{
    return EdgeMapSparse_t(graph, U, F, C, threadsCount);
}



VertexSubset Interface::EdgeMap(const Graph &graph,
                                const VertexSubset &U,
                                const std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                const std::function<bool(long vertexIndex)> &C, long threshold,
                                int threadsCount)
{
    // if(U.getVertexSubsetLength() + U.getVertexSubsetOutDegree(graph) > threshold)
    //     return EdgeMapDense(graph, U, F, C);
    // else
        //return EdgeMapSparse(graph, U, F, C);
        return EdgeMapSparse(graph, U, F, C, threadsCount);
}


VertexSubset Interface::EdgeMap_t(const Graph &graph,
                                const VertexSubset &U,
                                const std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                const std::function<bool(long vertexIndex)> &C, long threshold,
                                int threadsCount)
{
    // if(U.getVertexSubsetLength() + U.getVertexSubsetOutDegree(graph) > threshold)
    //     return EdgeMapDense(graph, U, F, C);
    // else
        //return EdgeMapSparse(graph, U, F, C);
        return EdgeMapSparse_t(graph, U, F, C, threadsCount);
}

VertexSubset Interface::EdgeMapSparse(const Graph &graph,
                            const VertexSubset &U,
                            const std::function<bool(long startVertexIndex, long endVertexIndex, double edgeWeight)> &F,
                            const std::function<bool(long vertexIndex)> &C,
                            int threadsCount) //Done : Tested
{
    // total += U.getVertexSubsetLength();
    // iterations++;
    VertexSubset Out; 
    size_t *prefix;
    #pragma omp parallel num_threads(threadsCount)
    {
        long ithread  = omp_get_thread_num(); //get the thread number
        long nthreads = omp_get_num_threads(); //get number of threads
        #pragma omp single
        {
            prefix = new size_t[nthreads+1]; //this stores the sizes of the different vertex neighbours
            prefix[0] = 0;
        }
        std::vector<long> vec_private;
        #pragma omp for nowait
        for(long v = 0; v < U.getVertexSubsetLength(); v++)
        {
            long curr = U.getVertexAt(v);
            Vertex* v_ = graph.getVertexPointer(curr);

            long oSize = v_->getOutDegree();
            for(long ngh = 0; ngh < oSize; ngh++)
            {   
                if(C(v_->getOutNeighboursEl(ngh)) && F(curr, v_->getOutNeighboursEl(ngh), graph.getEdgeWeight(curr, v_->getOutNeighboursEl(ngh))))
                {
                    vec_private.push_back(v_->getOutNeighboursEl(ngh)); 
                }
            }
        }
        prefix[ithread + 1] = vec_private.size();    
        #pragma omp barrier
        #pragma omp single 
        {
            for(int i=1; i <= nthreads; i++) prefix[i] += prefix[i-1];
            Out.getVertexSubset().resize(prefix[nthreads]);
        }
        //Out.getVertexSubset().insert(Out.getVertexSubset().end(), vec_private.begin(), vec_private.end());
        std::copy(vec_private.begin(), vec_private.end(), Out.getVertexSubset().begin() + prefix[ithread]);
    }

    delete prefix; 

    
    std::sort(Out.getVertexSubset().begin(), Out.getVertexSubset().end());
    Out.getVertexSubset().erase(std::unique(Out.getVertexSubset().begin(), Out.getVertexSubset().end()), Out.getVertexSubset().end());
    total += Out.getVertexSubsetLength();
    iterations++;
    //RemoveDuplicates(Out); //TO DO: confirm if it remains in the scope
    return Out;
}

VertexSubset Interface::EdgeMapSparse(const Graph &graph,
                                const VertexSubset &U,
                                const std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                const std::function<bool(long vertexIndex)> &C,
                                int threadsCount)
{

    VertexSubset Out; 
    size_t *prefix;
    #pragma omp parallel num_threads(threadsCount)
    {
        long ithread  = omp_get_thread_num(); //get the thread number
        long nthreads = omp_get_num_threads(); //get number of threads
        #pragma omp single
        {
            prefix = new size_t[nthreads+1]; //this stores the sizes of the different vertex neighbours
            prefix[0] = 0;
        }
        std::vector<long> vec_private;
        #pragma omp for nowait
        for(long v = 0; v < U.getVertexSubsetLength(); v++)
        {
            long curr = U.getVertexAt(v);
            Vertex* v_ = graph.getVertexPointer(curr);

            long oSize = v_->getOutDegree();
            for(long ngh = 0; ngh < oSize; ngh++)
            {   
                if(C(v_->getOutNeighboursEl(ngh)) && F(curr, v_->getOutNeighboursEl(ngh)))
                {
                    vec_private.push_back(v_->getOutNeighboursEl(ngh)); 
                }
            }
        }
        prefix[ithread + 1] = vec_private.size();    
        #pragma omp barrier
        #pragma omp single 
        {
            for(int i=1; i <= nthreads; i++) prefix[i] += prefix[i-1];
            Out.getVertexSubset().resize(prefix[nthreads]);
        }
        //Out.getVertexSubset().insert(Out.getVertexSubset().end(), vec_private.begin(), vec_private.end());
        std::copy(vec_private.begin(), vec_private.end(), Out.getVertexSubset().begin() + prefix[ithread]);
    }
        
    delete prefix;
    
    std::sort(Out.getVertexSubset().begin(), Out.getVertexSubset().end());
    Out.getVertexSubset().erase(std::unique(Out.getVertexSubset().begin(), Out.getVertexSubset().end()), Out.getVertexSubset().end());

    total += Out.getVertexSubsetLength();
    iterations++;
    //RemoveDuplicates(Out); //TO DO: confirm if it remains in the scope
    return Out;
}


VertexSubset Interface::EdgeMapSparse_t(const Graph &graph,
                                const VertexSubset &U,
                                const std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                const std::function<bool(long vertexIndex)> &C,
                                int threadsCount)
{
    VertexSubset Out; 
    #pragma omp parallel num_threads(threadsCount)
    {
        #pragma omp for nowait
        for(long v = 0; v < U.getVertexSubsetLength(); v++)
        {
            long curr = U.getVertexAt(v);
            Vertex* v_ = graph.getVertexPointer(curr);

            long oSize = v_->getOutDegree();
            for(long ngh = 0; ngh < oSize; ngh++)
            {   
                if(C(v_->getOutNeighboursEl(ngh)) && F(curr, v_->getOutNeighboursEl(ngh)))
                {
                    #pragma omp critical
                    Out.getVertexSubset().push_back(v_->getOutNeighboursEl(ngh)); 
                }
            }
        }
    }
    
    std::sort(Out.getVertexSubset().begin(), Out.getVertexSubset().end());
    Out.getVertexSubset().erase(std::unique(Out.getVertexSubset().begin(), Out.getVertexSubset().end()), Out.getVertexSubset().end());

    total += Out.getVertexSubsetLength();
    iterations++;
    //RemoveDuplicates(Out); //TO DO: confirm if it remains in the scope
    return Out;
}


VertexSubset Interface::EdgeMapSparse_t(const Graph &graph,
                                const VertexSubset &U,
                                const std::function<bool(long startVertexIndex, long endVertexIndex, double weight)> &F,
                                const std::function<bool(long vertexIndex)> &C,
                                int threadsCount)
{
    VertexSubset Out; 
        for(long v = 0; v < U.getVertexSubsetLength(); v++)
        {
            long curr = U.getVertexAt(v);
            Vertex* v_ = graph.getVertexPointer(curr);

            long oSize = v_->getOutDegree();
            for(long ngh = 0; ngh < oSize; ngh++)
            {   
                if(C(v_->getOutNeighboursEl(ngh)) && F(curr, v_->getOutNeighboursEl(ngh), graph.getEdgeWeight(curr, v_->getOutNeighboursEl(ngh))))
                {

                    Out.getVertexSubset().push_back(v_->getOutNeighboursEl(ngh)); 
                }
            }
        }
    
    std::sort(Out.getVertexSubset().begin(), Out.getVertexSubset().end());
    Out.getVertexSubset().erase(std::unique(Out.getVertexSubset().begin(), Out.getVertexSubset().end()), Out.getVertexSubset().end());

    total += Out.getVertexSubsetLength();
    iterations++;
    //RemoveDuplicates(Out); //TO DO: confirm if it remains in the scope
    return Out;
}


//To Do: Does it need to iterate from i = 1...|V| or can we do it in the way it is stored in the map


VertexSubset Interface::EdgeMapDense(const Graph &graph,
                                const VertexSubset &U,
                                const std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                const std::function<bool(long vertexIndex)> &C,
                                int threadsCount)
{
    VertexSubset Out;
    //TO DO: Parallel
    for(long i = 0; i < graph.getNumberVertices(); i++)
    {
        Vertex* v = graph.getVertexPointer(i);
        if (C(i) == 1)
            for(auto ngh = v->getInNeighboursBegin(); ngh < v->getInNeighboursEnd(); ngh++)
            {
                if(std::find(U.getVertexSubsetBegin(), U.getVertexSubsetEnd(), *ngh) != U.getVertexSubsetEnd() && F(*ngh, i))
                    Out.addVertex(i);
                if(C(i) == 0)
                    break;

            }
    }
    return Out;
    
}

VertexSubset Interface::EdgeMapDenseWrite(const Graph &graph,
                                const VertexSubset &U,
                                const std::function<bool(long startVertexIndex, long endVertexIndex)> &F,
                                const std::function<bool(long vertexIndex)> &C,
                                int threadsCount)
{
    VertexSubset Out;
    // TO DO: parallel
    for(long i = 0; i < graph.getNumberVertices(); i++)
    {

        if(std::find(U.getVertexSubsetBegin(), U.getVertexSubsetEnd(), i) != U.getVertexSubsetEnd())
        {
            //TO DO: parallel
            Vertex* v = graph.getVertexPointer(i);
            for(auto ngh = v->getOutNeighboursBegin(); ngh < v->getOutNeighboursEnd(); ngh++)
            {
                if(C(*ngh) && F(i, *ngh))
                    Out.addVertex(*ngh);
            }
        }
    }
    std::sort(Out.getVertexSubset().begin(), Out.getVertexSubset().end());
    Out.getVertexSubset().erase(std::unique(Out.getVertexSubset().begin(), Out.getVertexSubset().end()), Out.getVertexSubset().end());    
    return Out;
}

VertexSubset Interface::VertexMap(const VertexSubset &U,
                                  const std::function<bool(long vertexIndex)> &F,
                                  int threadsCount)
{
    VertexSubset Out;
    size_t *prefix;
    #pragma omp parallel num_threads(threadsCount)
    {
        long ithread  = omp_get_thread_num(); //get the thread number
        long nthreads = omp_get_num_threads(); //get number of threads
        #pragma omp single
        {
            prefix = new size_t[nthreads+1]; //this stores the sizes of the different vertex neighbours
            prefix[0] = 0;
        }
        std::vector<long> vec_private;
        #pragma omp for nowait
        for(auto v = U.getVertexSubsetBegin(); v < U.getVertexSubsetEnd(); v++)
        {
                if(F(*v))
                    vec_private.push_back(*v);
        }
        prefix[ithread + 1] = vec_private.size();    
        #pragma omp barrier
        #pragma omp single 
        {
            for(int i=1; i <= nthreads; i++) prefix[i] += prefix[i-1];
            Out.getVertexSubset().resize(prefix[nthreads]);
        }
        //Out.getVertexSubset().insert(Out.getVertexSubset().end(), vec_private.begin(), vec_private.end());
        std::copy(vec_private.begin(), vec_private.end(), Out.getVertexSubset().begin() + prefix[ithread]);
    }
    delete prefix;
    return Out;
}   


VertexSubset Interface::VertexMap_t(const VertexSubset &U,
                                  const std::function<bool(long vertexIndex)> &F,
                                  int threadsCount)
{
    VertexSubset Out;
    for(auto v = U.getVertexSubsetBegin(); v < U.getVertexSubsetEnd(); v++)
    {
            if(F(*v))
            {   
                Out.getVertexSubset().push_back(*v);
            }
    }
  
    return Out;
}   