#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
using namespace std;
ifstream fin("bridges.in");

//An articulation point is a node which, if deleteted, increases the number of islands.
//So, an articulation point can be found this way:
//if there is a bridge from u to v, then or u or v is an articulation point, but there are some edge cases:
//Also, if there is a cicle, a node can be an articulation point even if there is no bridge between it and another node.
//and also that can be an articulation point only if it has more than 1 outEdgeCount (edges going from / to him).

//more from the video with graph theory;

int n; //Number of nodes;
vector<int> G[100]; //Adiacency List
int id;
int ids[100];
bool visited[100];
int low[100];
int outEdgeCount; 
bool isArt[100];

void dfs(int root, int node, int parent){
	if(parent == root) outEdgeCount++;
	visited[node] = true;
	id++;
	ids[node] = id;
	low[node] = id;
	
	for(int i=0; i<G[node].size(); i++){
		int nextNode = G[node][i];
		if(nextNode==parent) continue;
		
		if(!visited[nextNode]){
			dfs(root,nextNode,node);
			low[node] = min(low[node], low[nextNode]);
			
			//articulation point found via bridge
			if(ids[node] < low[nextNode]){
				isArt[node] = true;
			}
			
			//articulation point found via cicle
			//This is the condition for cicle. check the video for mode details on
			//how it works
			if(ids[node] == low[nextNode]){
				isArt[node] = true;
			}
			
		} else{
			low[node] = min(low[node], ids[nextNode]);
		}
	}
	
}

vector<int> findPoints(){
	
	vector<int> Points;
	for(int i=0; i<n; i++){
		if(!visited[i]){
			outEdgeCount = 0;
			dfs(i,i,-1);
			isArt[i] = (outEdgeCount>1); 
		}
	}
	
	for(int i=0; i<100; i++){
		if(isArt[i]) Points.push_back(i);
	}	
	
	return Points;
}

int main(int argc, char** argv) {
	int m;
	fin>>n>>m;
	for(int i=0; i<m; i++){
		int x, y;
		fin>>x>>y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	
	
	vector<int> p = findPoints();
	
	for(int i=0; i<p.size(); i++){
		cout<<p[i]<<endl;
	}
	return 0;
}
