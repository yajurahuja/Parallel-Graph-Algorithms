#ifndef VERTEX_H
#define VERTEX_H

#include<vector>
#include<atomic>


class Vertex
{
    public:        

    //!Constructor
    Vertex();
    Vertex(long value);

    long getDataValue(); 
    long getId(); 
    std::vector<long> getOutNeighbours();
    std::vector<long> getInNeighbours(); 
    std::vector<long>::const_iterator getOutNeighboursBegin() const;
    std::vector<long>::const_iterator getOutNeighboursEnd() const;
    std::vector<long>::const_iterator getInNeighboursBegin() const;
    std::vector<long>::const_iterator getInNeighboursEnd() const;
    long getOutDegree();
    long getInDegree(); 
    void addOutDegree(long v); 
    void addInDegree(long v); 
    long getOutNeighboursEl(long ind);


    private:
    long p_id;      //!Identifier

    long p_dataVal; //!Data supplied as input


    std::vector<long> InNeighbours; //vector storing all the vertex ids of the vertices which have an edge to this vertex
    std::vector<long> OutNeighbours; //vector storing all teh vertex ids of the vertices which have an edge from this vertex

};

#endif