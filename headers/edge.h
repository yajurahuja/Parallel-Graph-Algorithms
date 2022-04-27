#ifndef EDGE_H
#define EDGE_H

class Edge
{
    public:
    Edge(long startVertexId, long endVertexId);
    Edge(long startVertexId, long endVertexId, double weight);


    long getStartVertexId();
    long getEndVertexId();
    //double getWeight();
    double getWeight();
    
    private:
    long p_start_vertexId;
    long p_end_vertexId;
    double p_weight;
};

#endif