#include<string>
#include<iostream>
using namespace std;

#include "timestamp.h"
#ifndef UGRAPH_H
#define UGRAPH_H

struct edge{
	int source;
	int neighbor;
	int w;
	edge(){
		source = 0;
		neighbor = 0;
		w = 0;
	};
	edge(int i, int j){
		source = 0;
		neighbor = i;
		w = j;
	};
	edge(int from, int to, int aweight){
        source = from;
        neighbor = to;
        w = aweight;
    };
    //bool operator<(edge y){ return (this->w < y.w) ? true : false; };
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
	
	//Project 4
	void dijkstra(int s);
	void printDistance();
	void printParents();
	void kruskal();
	void printPath(int u, int v);
	void printPathTwo(int u);
	int lenghtShortestW(int u, int v);
	int findSet(int v);
	void combine(int x, int y);
	void printMST();
	int weightMST();


private:
	vector< vector<edge> > Adj; //adjacency lists of the graph 
	vector<int> distance; //for BFS and DFS
	vector<int> parents; //for BFS and DFS
	vector<char> colors; //for DFS
	vector<TimeStamp> stamps; //for DFS: stamps[v].d returns discovery time of v, and stamps[v].f finishing time.
    vector<vector< edge > > mst;
    int size;
};

#endif
