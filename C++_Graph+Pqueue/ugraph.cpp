#include<climits>
#include<algorithm>
#include<queue>
#include<math.h>
#include<vector>
#include<iostream>
#include<string>
#include<utility>
using namespace std;

#include "ugraph.h"
#include "item.h"
#include "priorityqueue.h"

Ugraph::Ugraph(int N){
	size = N;
	Adj.resize(size);
	distance.resize(size);
	parents.resize(size);
	colors.resize(size);
	stamps.resize(size);
	mst.resize(size);
}//Ugraph
bool lessThan(const edge &x, const edge &y) { return (x.w < y.w) ? true : false; }
//lessThan
void Ugraph::addEdge(int u, int v){
	Adj[u].push_back(edge(v, 0));
	Adj[v].push_back(edge(u, 0));
}//addEdge
void Ugraph::addEdge(int u, int v, int aweight){
	Adj[u].push_back(edge(v, aweight));
	Adj[v].push_back(edge(u, aweight));
}//addEdgeWeight
void Ugraph::removeEdge(int u, int v){
	int u_size = (int)Adj[u].size();
	for(int i = 0; i < u_size; i++){
		int u_temp = Adj[u][i].neighbor;
		if(u_temp == v){
			Adj[u][i] = Adj[u][u_size - 1];
			Adj[u].resize(u_size - 1);  
			break;
		}
	}
	int v_size = (int)Adj[v].size();
	for(int i = 0; i < v_size; i++){
		int v_temp = Adj[v][i].neighbor;
		if(v_temp == u){
			Adj[v][i] = Adj[v][v_size - 1];
			Adj[v].resize(v_size - 1);
			break;
		}
	}
}//removeEdge
void Ugraph::printGraph(){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < (int)Adj[i].size(); j++){
			int v = Adj[i][j].neighbor;
			cout << v << " ";
		}
		cout << endl;
	}
}//printGraph
void Ugraph::bfs(int s){
	for(int i = 0; i < size; i++){
		distance[i] = INT_MAX;
		parents[i] = i;
	}//for
	distance[s] = 0;
	queue<int> aq;
	aq.push(s);
	while(!aq.empty()){
		int u = aq.front();
        cout << u << " ";
        aq.pop();
		for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			if(distance[v] == INT_MAX){
				distance[v] = distance[u] + 1;
				parents[v] = u;
				aq.push(v);
			}
		}//for
	}//while
	cout << endl;
}//bfs
void Ugraph::dfs(){
	for(int i = 0; i < size; i++){
		parents[i] = i;
		colors[i] = 'W';
	}	
	int t = 0;

	for(int i = 0; i < size; i++){
		if(colors[i] == 'W'){
			dfsVisit(i, t);
		}
	}
	cout << endl;
}//dfs
void Ugraph::dfsVisit(int u, int &t){
	colors[u] = 'G';
	stamps[u].d = t;
	t++;
	cout << u << " ";
	for(int i = 0; i < (int)Adj[u].size(); i++){
		int v = Adj[u][i].neighbor;
		if(colors[v] == 'W'){
			parents[v] = u;
			colors[v] = 'G';
			dfsVisit(v, t);
		}
	}
	colors[u] = 'B';
	stamps[u].f = t;
	t++;
}//dfsVisit	

//
//
//PROJECT 4 - 
void Ugraph::dijkstra(int s){
	for(int v = 0; v < size; v++){
		parents[v] = v;
		distance[v] = INT_MAX;
	}
	distance[s] = 0;
	Item *itemObj = new Item[size];
	for(int v = 0; v < size; v++){
		itemObj[v] = Item(v, distance[v]);
	}
	PriorityQueue queue(itemObj, size);
	while(queue.getSize() > 0){
		Item itemCheck = queue.getMin();
		int itemKey = itemCheck.key;
		queue.pop();
		if(distance[itemKey] != INT_MAX){
			for(int i = 0; i < (int)Adj[itemKey].size(); i++){
				int weight = Adj[itemKey][i].w;
				int neighbor = Adj[itemKey][i].neighbor;
				int temp = distance[itemKey] + weight;
				if(temp < distance[neighbor]){
					parents[neighbor] = itemKey;
					distance[neighbor] = temp;
					queue.updatePriority(neighbor, temp);
				}
			}
		}
	}
}//dijkstra

void Ugraph::printDistance(){
	for(int v = 0; v < size; v++){
		cout << distance[v] << " ";
	}
	cout << endl;
}//printDistancee

void Ugraph::printParents(){
	for(int v = 0; v < size; v++){
		cout << parents[v] << " ";
	}
	cout << endl;
}//printParents

void Ugraph::printPath(int u, int v){
	if(parents[u] != v){
		printPathTwo(parents[v]);
	}
	cout << v << " ";
}//printPath
void Ugraph::printPathTwo(int u){
	if(parents[u] != u){
		printPathTwo(parents[u]);
	}
	cout << u << " ";
}//printPath

int Ugraph::lenghtShortestW(int u, int v){
	dijkstra(u);
	printPath(u, v);
	cout << endl;
	return distance[v];
}//lenghtShortestW

void Ugraph::kruskal(){
	for(int v = 0; v < size; v++){
		parents[v] = v;
		distance[v] = 0;
	}
	if(mst.size() > 0){
		mst.clear();
		mst.resize(size);
	}
	vector<edge> edgesAll;
	edgesAll.resize(size);
	int counter = 0;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < (int)Adj[i].size(); j++){
			int v = Adj[i][j].neighbor;
			int w = Adj[i][j].w;
			if(i < v){
				edgesAll.push_back(edge(i, v, w));
			}
		}
	}
	sort(edgesAll.begin(), edgesAll.end(), lessThan);
	mst.resize(size);
	for(int v = 0; counter != size - 1; v++){
		int source = edgesAll[v].source;
		int neighbor = edgesAll[v].neighbor;
		int weight = edgesAll[v].w;
		int find1 = findSet(source);
		int find2 = findSet(neighbor);
		if(find1 != find2){
			mst[source].push_back(edge(source, neighbor, weight));
			mst[neighbor].push_back(edge(neighbor, source, weight));
			combine(find1, find2);
			counter++;
		}
	}
}//kruskal

int Ugraph::findSet(int v){
	if(parents[v] != v){
		parents[v] = findSet(parents[v]);
	}
	return parents[v];
}//findSet

void Ugraph::combine(int x, int y){
	if(distance[x] > distance[y]){
		parents[y] = x;
	}
	else{
		parents[x] = y;
	}
	if(distance[x] == distance[y]){
		distance[y] = distance[y] + 1;
	}
}//combine

void Ugraph::printMST(){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < (int)mst[i].size(); j++){
			int res = mst[i][j].neighbor;
			cout << res << " ";
		}
		cout << endl;
	}
}//printMST

int Ugraph::weightMST(){
	int weight = 0;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < (int)mst[i].size(); j++){
			weight += mst[i][j].w;
		}
	}
	int weightTotal = weight / 2;					
	return weightTotal;
}//weightMST
