#ifndef BFS_H
#define BFS_H

#include "../headers/allHeaders.h"
#include <filesystem>
#include <iostream>
#include <deque>
#include <omp.h> 
#include<atomic>

class Graph;
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

//Bellman Ford
bool bfUpdate(long s, long d,double weight);
bool bfReset(long ind);
void bellmanFord(const Graph &graph, long root);



#endif