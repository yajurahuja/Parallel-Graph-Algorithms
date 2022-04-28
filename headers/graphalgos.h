#ifndef BFS_H
#define BFS_H

#include "../headers/allHeaders.h"
#include <filesystem>
#include <iostream>
#include <deque>
//#include <omp.h> 
#include<atomic>
#include<limits>

class Graph;

//Atomic operations
bool CAS(long *ptr, long oldv, long newv);
bool CAS(double *ptr, double oldv, double newv);
bool writeMin(long *ptr, long newv);
bool writeMin(double *ptr, double newv);


//Sequential BFS
void bfs_s(const Graph &graph, long root);

//BFS using interface
bool update(long v, long ind);
bool cond(long ind);
void bfs(const Graph &graph, long root);

//Conected Components
bool CCUpdate(long s, long d);
bool Copy(long ind);
void connectedComp(const Graph &graph);

//Sequential Bellman Ford
bool bellmanFord_s(const Graph &graph, long root);
//Bellman Ford
bool bfUpdate(long s, long d, double edgeWeight); //TO DO: for double weight
bool bfReset(long ind);
bool bellmanFord(const Graph &graph, long root);



#endif