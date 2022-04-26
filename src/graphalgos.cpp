#include "../headers/allHeaders.h"



//BFS
std::deque<long> parents;
std::deque<long> layers;

//BFS Sequential
std::deque<long> parents_s;
std::deque<long> layers_s;
//Connected Components
std::deque<std::atomic<long>> IDs;
std::deque<std::atomic<long>> prevIDs;
//Bellman Ford
std::deque<std::atomic<double>> SP;
std::deque<std::atomic<long>> Visited;


void bfs_s(const Graph &graph, long root)
{
	long size = graph.getNumberVertices();
	parents_s.resize(size);
	layers_s.resize(size);
	//TO DO: maybe parallel
    for(int i = 0; i < size; i++)
	{
        parents_s[i] = -1;
		layers_s[i] = -1;
	}

	std::deque<long> queue; // to store current layer
	parents_s[root] = root; //set the root's parent to itself
	layers_s[root] = 0; //set the layer of root to 0
	queue.push_back(root);
	while(!queue.empty())
	{
		auto curr = queue.front();
		queue.pop_front();
		Vertex* v = graph.getVertexPointer(curr);
		for(auto ngh = v->getOutNeighboursBegin(); ngh < v->getOutNeighboursEnd(); ngh++)
        {
			if (parents_s[*ngh] == -1) //The neighbour has not been visited yet
			{
				parents_s[*ngh] = curr;
				layers_s[*ngh] = layers_s[curr] + 1; 
				queue.push_back(*ngh);	
			}
        }
	}

	// std::cout<<"Sequential"<<std::endl;
	// for(int i = 0; i < size; i++)  
	// 	std::cout<<i<<": "<<"PARENT "<<parents_s[i]<<" LAYER "<<layers_s[i]<<std::endl;
}


bool update(long v, long ind)
{
	long old = -1;
	bool ret;
	if (parents[ind] == old)
	{
		parents[ind] = v;
		ret = true;
	}
	else
		ret = false;
	
	return ret;
}

bool cond(long ind) 
{	
	bool result;
	result = (parents[ind] == -1);
	return result;
}

void bfs(const Graph &graph, long root)
{
    long size = graph.getNumberVertices();
	parents.resize(size);
	layers.resize(size);
	//TO DO: parallel
    for(int i = 0; i < size; i++)
	{
        parents[i] = -1;
		layers[i] = -1;
	}
    long threshhold; //set the threshhold
    parents[root] = root; //set the root's parent to itself
	layers[root] = 0; //set the layer of root to 0
	VertexSubset frontier(root);
	long layer = 1;
	while(frontier.getVertexSubsetLength() > 0)
	{
		frontier = Interface::EdgeMap(graph, frontier, &update, &cond, threshhold);
		//TO DO: parallel
		for(auto v = frontier.getVertexSubsetBegin(); v < frontier.getVertexSubsetEnd(); v++)
			layers[*v] = layers[parents[*v]] + 1;
		
		//std::cout<<"iteration "<<layer<<":"<<std::endl;
		// for(long i = 0; i < layers.size(); i++)
		// {
		// 	std::cout<<i<<":"<<layers[i]<<" ";
		// }
		//std::cout<<std::endl;
		layer += 1;
	}
    // std::cout<<"Parallel:"<<std::endl;
    // for(int i = 0; i < size; i++)  
    //     std::cout<<i<<": "<<"PARENT "<<parents[i]<<" LAYER "<<layers[i]<<std::endl;
	return;
}


bool writeMin()
{
	return true;
}


//Connected Components
bool CCUpdate(long s, long d)
{
	long origId = IDs[d].load();
	return true;
}
bool Copy(long ind)
{
	prevIDs[ind] = IDs[ind].load();
	return  true;
}
void connectedComp(const Graph &graph)
{
	VertexSubset frontier;
}



//Bellman Ford
bool bfUpdate(long s, long d,double weight)
{
	return true;
}

bool bfReset(long ind)
{
	Visited[ind] = 0;
	return true;
}
void bellmanFord(const Graph &graph, long root)
{
	return;
}
