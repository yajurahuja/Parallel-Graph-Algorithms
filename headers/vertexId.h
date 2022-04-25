#ifndef VERTEX_ID_H
#define VERTEX_ID_H


class VertexIdTracker
{
    private:
    VertexIdTracker();      //!For singlton pattern
    ~VertexIdTracker();

    public:
    friend class Vertex;
    static VertexIdTracker * getInstance();
    void DestroyIdManager();

    //!Modifiers
    long FetchNewId();

    //!Access Functions
    long GetLastGeneratedIdIndex();

    //!Data members
    private:
    static VertexIdTracker * vertexIdManager;
    long p_vertexIdsUsedTill;
};

#endif