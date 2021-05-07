#include<string>
#include<iostream>
using namespace std;

#include "timestamp.h"
#ifndef UGRAPH_H
#define UGRAPH_H

struct edge{
	int neighbor;
	int w;
	edge(){
		neighbor = 0;
		w = 0;
	};
	edge(int i, int j){
		neighbor = i;
		w = j;
	};
};

class Ugraph{
public:
	Ugraph(int N);
	void bfs(int s);
	void dfs();
	void dfsVisit(int u, int &t);
	void printGraph();
	void addEdge(int u, int v);
	void addEdge(int u, int v, int weight);

	void removeEdge(int u, int v);
	bool distinctPaths(int u, int v);
	void printBridges();
	void printCC();
	bool twoColoring();

	bool twoPaths(int s, int r);
	void pathRecurse(int u);
	void backtrackSetW(int v);
	void bfsSilent(int s);
	void bfsDistinct(int s);
	void bridge(int u, int &t);
	void cycle_two(int v, int &t, vector<int> &temp);
	bool dfsSilent(int v, int &t);

private:
	vector< vector<edge> > Adj; //adjacency lists of the graph 
	vector<int> distance; //for BFS and DFS
	vector<int> parents; //for BFS and DFS
	vector<char> colors; //for DFS
	vector<TimeStamp> stamps; //for DFS: stamps[v].d returns discovery time of v, and stamps[v].f finishing time.
    vector<int> dCheck;
    vector<char> cCheck;
    int size;
};

#endif
