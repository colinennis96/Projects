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

Ugraph::Ugraph(int N){
	size = N;
	Adj.resize(size);
	distance.resize(size);
	parents.resize(size);
	colors.resize(size);
	stamps.resize(size);
	dCheck.resize(size);
}//Ugraph

void Ugraph::addEdge(int u, int v){
	Adj[u].push_back(edge(v, 0));
	Adj[v].push_back(edge(u, 0));
}//addEdge

void Ugraph::addEdge(int u, int v, int weight){
	Adj[u].push_back(edge(v, weight));
}//addEdge

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

bool Ugraph::distinctPaths(int u, int v){
	bool result = true;
	if(twoPaths(u, v)){
		bfsSilent(u);
		pathRecurse(v);
		cout << endl;
		backtrackSetW(v);
		bfsDistinct(u);
		pathRecurse(v);
		cout << endl;
		return result;
	}
	result = false;
	return result;
}//distinctPaths

bool Ugraph::twoPaths(int s, int r){
	bfsSilent(s);
	if(distance[r] == INT_MAX){
		return false;
	}
	backtrackSetW(r);
	bfsDistinct(s);
	if(distance[r] == INT_MAX){
		return false;
	}
	return true;
}//twoPaths

void Ugraph::backtrackSetW(int v){
	int par = parents[v];
	if(par == v){
		return;
	}
	for(int i = 0; i < (int)Adj[par].size(); i++){
		int myNeighbor = Adj[par][i].neighbor;
		if(myNeighbor == v){
			Adj[par][i].w = -1;
			break;
		}
	}
	backtrackSetW(par);
}//backtrackSetW

void Ugraph::bfsSilent(int s){
	for(int i = 0; i < size; i++){
		distance[i] = INT_MAX;
		parents[i] = i;
	}//for
	distance[s] = 0;
	queue<int> aq;
	aq.push(s);
	while(!aq.empty()){
		int u = aq.front();
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
}//bfsSilent

void Ugraph::bfsDistinct(int s){
	for(int i = 0; i < size; i++){
		distance[i] = INT_MAX;
		parents[i] = i;
	}
	distance[s] = 0;
	queue<int> aq;
	aq.push(s);
	while(!aq.empty()){
		int u = aq.front();
        aq.pop();
		for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			int myWeight = Adj[u][i].w;
			if( (distance[v] == INT_MAX) && (myWeight != -1) ){
				distance[v] = distance[u] + 1;
				parents[v] = u;
				aq.push(v);
			}
		}
	}
}//bfsDistinct

void Ugraph::pathRecurse(int v)
{
	if(v != parents[v]){
		pathRecurse(parents[v]);
	}
	cout << v << " ";
}//pathRecurse

void Ugraph::printBridges(){
	for(int i = 0; i < size; i++){
		colors[i] = 'W';
		parents[i] = i;
		dCheck[i] = INT_MAX;
	}
	int t = 1;
	for(int i = 0; i < size; i++){
		if(colors[i] == 'W'){
			bridge(i, t);
		}
	}
}//printBridges

void Ugraph::bridge(int u, int &t){
	colors[u] = 'G';
	stamps[u].d = t;
	dCheck[u] = t;
	t++;
	for(int i = 0; i < (int)Adj[u].size(); i++){
		int v = Adj[u][i].neighbor;
		if(colors[v] == 'W'){
			parents[v] = u;
			bridge(v, t);
			dCheck[u] = min(dCheck[u], dCheck[v]);
			if(dCheck[v] == stamps[v].d){
				cout << u << " " << v << endl;
			}
		}
		else if(colors[v] == 'G' || colors[v] == 'B'){
			if(parents[u] != v){
				dCheck[u] = min(dCheck[u], stamps[v].d);
			}
		}
	}
	colors[u] = 'B';
	stamps[u].f = t;
	t++;
}//bridge

void Ugraph::printCC(){
	for(int i = 0; i < size; i++){
		parents[i] = i;
		colors[i] = 'W';
	}
	int t = 0;
	for(int i = 0; i < size; i++){
		if(colors[i] == 'W'){
			vector<int> temp;
			colors[i] = 'G';
			temp.push_back(i);
			cycle_two(i, t, temp);
			if(temp[(int)temp.size() - 1] < temp[(int)temp.size() - 2]){
				swap(temp[(int)temp.size() - 1], temp[(int)temp.size() - 2]);
			}
			for(int j = 0; j < (int)temp.size(); j++){
				cout << temp[j] << " ";
			}
			cout << endl;
		}
	}
}//printCC

void Ugraph::cycle_two(int v, int &t, vector<int> &temp)
{
	colors[v] = 'G';
	stamps[v].d = t;
	t++;
	for(int i = 0; i < (int)Adj[v].size(); i++){
		int u = Adj[v][i].neighbor;
		if(colors[u] == 'W'){ 
			parents[u] = v;
			colors[u] = 'G';
			temp.push_back(u);
			cycle_two(u, t, temp);
		}
	}
	colors[v] = 'B';
	stamps[v].f = t;
	t++;
}//cycle_two

bool Ugraph::twoColoring(){
	bool result;
	cCheck.resize(size);
	for(int i = 0; i < size; i++){
		distance[i] = 0;
		parents[i] = i;
		colors[i] = 'W';
		cCheck[i] = 'R';
	}
	int t = 0;
	for(int i = 0; i < size; i++){
		if(colors[i] == 'W'){
			cCheck[i] = 'R';
			result = dfsSilent(i, t);
		}
	}
	return result;
}//twoColoring

bool Ugraph::dfsSilent(int v, int &t){
	bool result = true;
	stamps[v].d = t;
	colors[v] = 'G';
	t++;
	for(int i = 0; i < (int)Adj[v].size(); i++){
		int u = Adj[v][i].neighbor;
		if(colors[u] == 'W'){
			parents[u] = v;
			if(cCheck[v] == 'R'){
				cCheck[u] = 'B';
			}
			else{
				cCheck[u] = 'R';
			}
			result = dfsSilent(u, t);
		}
		if(cCheck[u] == cCheck[v]){
			result = false;
		}
	}
	stamps[v].f = t;
	t++;
	return result;
}//dfsSilent
