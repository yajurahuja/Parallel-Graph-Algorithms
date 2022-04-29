#include "../headers/allHeaders.h"


// std::deque<std::atomic<long>> parents;
// std::deque<std::atomic<long>> layers;
std::deque<long> parents;
std::deque<long> layers;
std::deque<long> parents_s;
std::deque<long> layers_s;
// long* parents;
// long* layers;
// long* parents_s;
// long* layers_s;
// std::deque<long> IDs;
// std::deque<long> prevIDs;
//Bellman Ford
std::deque<double> SP;
std::deque<long> Visited;

std::deque<double>SP_s;
std::deque<long> Visited_s;

bool CAS(long *ptr, long oldv, long newv)
{
    return __sync_bool_compare_and_swap((long*)ptr, *((long*)&oldv), *((long*)&newv));
}

bool CAS(double *ptr, double oldv, double newv)
{
	return __atomic_compare_exchange((double*)ptr, ((double*)&oldv), ((double*)&newv), 0, __ATOMIC_RELAXED, __ATOMIC_RELAXED);
}

bool writeMin(long *ptr, long newv)
{
	long c;
	bool ret = false;
	do
	{
		c = *ptr;
	} while (c > newv && !(ret = CAS(ptr, c, newv)));
	return ret;
}

bool writeMin(double *ptr, double newv)
{
	double c;
	bool ret = false;
	do
	{
		c = *ptr;
	} while (c > newv && !(ret = CAS(ptr, c, newv)));
	return ret;
}

void bfs_s(const Graph &graph, long root)
{
	
	long size = graph.getNumberVertices();
	parents_s.resize(size);
	layers_s.resize(size);
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
	return CAS(&parents[ind], old, v);
}

bool cond(long ind) 
{	
	bool result = false;
	result = (parents[ind] == -1);
	return result;
}

void bfs(const Graph &graph, long root, int threadsCount)
{
    long size = graph.getNumberVertices();
	parents.resize(size);
	layers.resize(size);
	//TO DO: parallel

//	std::cout << "Inside bfs" << std::endl;

	#pragma omp parallel for
    for(int i = 0; i < size; i++)
	{
        parents[i] = -1;
		layers[i] = -1;
	}
    long threshhold = 0; //set the threshhold
    parents[root] = root; //set the root's parent to itself
	layers[root] = 0; //set the layer of root to 0
	VertexSubset frontier(root);
	long layer = 1;
	while(frontier.getVertexSubsetLength() > 0)
	{
//	std::cout << "Inside bfs 2" << std::endl;
		frontier = Interface::EdgeMap(graph, frontier, &update, &cond, threshhold, threadsCount);
		//TO DO: parallel
		for(auto v = frontier.getVertexSubsetBegin(); v < frontier.getVertexSubsetEnd(); v++)
			layers[*v] = layers[parents[*v]] + 1;
		layer += 1;
	}
    // std::cout<<"Parallel:"<<std::endl;
    // for(int i = 0; i < size; i++)  
    //     std::cout<<i<<": "<<"PARENT "<<parents[i]<<" LAYER "<<layers[i]<<std::endl;
	return;
}




// //Connected Components
// bool CCUpdate(long s, long d)
// {
// 	long origId = IDs[d];
// 	if(writeMin(&IDs[d], IDs[s]))
// 		return (origId == prevIDs[d]);
// 	return true;
// }
// bool Copy(long ind)
// {
// 	prevIDs[ind] = IDs[ind];
// 	return true;
// }
// void connectedComp(const Graph &graph)
// {
// 	long threshhold = 0; //set threshhold
// 	VertexSubset frontier;
// 	while(frontier.getVertexSubsetLength() > 0)
// 	{
// 		frontier = Interface::VertexMap(frontier, &Copy);
// 		frontier = Interface::EdgeMap(graph, frontier, &CCUpdate, &Copy, threshhold);
// 	}
// }



//Sequential Bellman Ford
// bool bellmanFord_s(const Graph &graph, long root)
// {
// 	long size = graph.getNumberVertices(); //size stores the number of vertices
// 	SP_s.resize(size);
// 	Visited_s.resize(size);
// 	//TO DO: parallel
// 	for(int i = 0; i < size; i++) //initialization
// 	{	
// 		SP_s[i] = std::numeric_limits<double>::max();
// 		Visited_s[i] = 0;
// 	}
// 	SP_s[root] = 0;
// 	for(long i = 1; i < size; i++)
// 	{
// 		for(long e = 0; e < graph.getNumberEdges(); e++)
// 		{
// 			Edge* curr = graph.getEdgePointer(e);
// 			long u = curr->getStartVertexId();
// 			long v = curr->getEndVertexId();
// 			double weight = curr->getWeight();
// 			if (SP_s[u] + weight < SP_s[v])
//                 SP_s[v] = SP_s[u] + weight;		
// 		}
// 	}

// 	// for(long e = 0; e < graph.getNumberEdges(); e++)
// 	// {
// 	// 	Edge* curr = graph.getEdgePointer(e);
// 	// 	long u = curr->getStartVertexId();
// 	// 	long v = curr->getEndVertexId();
// 	// 	double weight = curr->getWeight();	
// 	// 	if (SP_s[u] + weight < SP_s[v])
//     //         return true;
//     // }
// 	return false;
// }

//Bellman Ford
bool bfUpdate_s(long s, long d, double edgeWeight)
{
	if(writeMin(&SP_s[d], SP_s[s] + edgeWeight))
		return CAS(&Visited_s[d], 0, 1);
	else
		return false;
}

bool bfReset_s(long ind)
{
	Visited_s[ind] = 0;
	return true;
}


bool bellmanFord_s(const Graph &graph, long root)
{
	long threshhold = 0;
	long size = graph.getNumberVertices();
	SP_s.resize(size);
	Visited_s.resize(size);
	//TO DO: parallel
	for(int i = 0; i < size; i++) //initialization
	{	
		SP_s[i] = std::numeric_limits<double>::max();
		Visited_s[i] = 0;
	}
	SP_s[root] = 0;
	VertexSubset frontier(root);
	long round = 0;
	while (frontier.getVertexSubsetLength() > 0 && round < size)
	{
		round += 1;
		frontier = Interface::EdgeMap(graph, frontier, &bfUpdate_s, &bfReset_s, threshhold);
		frontier = Interface::VertexMap(frontier, &bfReset_s);
	}
	if(round == size)
	{
		std::cout<<"Encountered a negative cycle\n";
		return true;
	}
	return false;
}



//Bellman Ford
bool bfUpdate(long s, long d, double edgeWeight)
{
	if(writeMin(&SP[d], SP[s] + edgeWeight))
		return CAS(&Visited[d], 0, 1);
	else
		return false;
}

bool bfReset(long ind)
{
	Visited[ind] = 0;
	return true;
}
bool bellmanFord(const Graph &graph, long root, int threadsCount)
{
	long threshhold = 0;
	long size = graph.getNumberVertices();
	SP.resize(size);
	Visited.resize(size);
	//TO DO: parallel
	for(int i = 0; i < size; i++) //initialization
	{	
		SP[i] = std::numeric_limits<double>::max();
		Visited[i] = 0;
	}
	SP[root] = 0;
	VertexSubset frontier(root);
	long round = 0;
	while (frontier.getVertexSubsetLength() > 0 && round < size)
	{
		round += 1;
		frontier = Interface::EdgeMap(graph, frontier, &bfUpdate, &bfReset, threshhold);
		frontier = Interface::VertexMap(frontier, &bfReset);
	}
	if(round == size)
	{
		std::cout<<"Encountered a negative cycle\n";
		return true;
	}
	return false;
}
