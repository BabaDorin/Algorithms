#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;
ifstream fin("bridges.in");
//Bridge -> An edge which, if deleted, increases the number of connected components
//in a graph.
//A bridge separates islands.
// from -> https://www.youtube.com/watch?v=09_LlHjoEiY&t=10097s





//Find bridges.

int id = 0; //Id of the current node.
vector<int> G[100]; //Adiacency list
int n; //Size of the graph.

int ids[100]; // Id-urile nodurilor

//lowLink value of node i
int low[100]; // this will store the smalles id if the node which starts an island
bool visited[100]; // for dfs

//Dfs with modification for finding the bridges
void dfs(int node, int parent, vector<pair<int,int> > &Bridges){
	
	//Home stuff
	visited[node] = true;
	id++;
	ids[node] = id;
	low[node] = id;
	
	//Go through each node the current node is connected
	for(int i=0; i<G[node].size(); i++){
		
		//Pick the next node
		int nextNode = G[node][i];
		
		//As the graph is unidirected, it means that the next node ca point to the previous node, in this case
		//the iteration is skipped and the new next node is picked
		if(nextNode == parent) continue;
		
		//it the edge is pointing to an already visited node, it means that an islans was found.
		//otherwise do the following
		if(!visited[nextNode]){
			
			//Da-i cu dfs-u in cap
			dfs(nextNode,node,Bridges);
			
			//La intoarcere din dsf se vor modifica valorile din low. Daca la intoarcere, low[nextNode] va fi mai 
			//mic decat low[node], inseamna ca a fost gasit un ciclu sau o insula sau whatever
			low[node] = min(low[node], low[nextNode]); 
			
			//the condition for finding bridges
			if(ids[node] < low[nextNode]){
				Bridges.push_back(make_pair(node,nextNode));
			}
		} else{
			//the case when it's pointing to an already visited node.
			low[node] = min(ids[nextNode], low[node]);
		}
	}	
}

//Function that will return a vector containing the bridges
vector<pair<int,int> > findBridges(){
	vector<pair<int,int> > Bridges;
	
	//now, run dfs for each node.
	for(int i=0; i<n; i++){
		if(!visited[i])
			dfs(i, -1, Bridges);
	}
	
	return Bridges;
}

int main(int argc, char** argv) {
	
	int m; //Number of edges
	fin>>n>>m;
	
	for(int i=0; i<m; i++){
		int from,to;
		fin>>from>>to;
		//It is an unidirected graph.
		G[from].push_back(to);
		G[to].push_back(from);
	}
	
	vector<pair<int,int> > Bridges = findBridges();
	for(int i=0; i<Bridges.size(); i++){
		cout<<"Bridge from "<<Bridges[i].first<<" to "<<Bridges[i].second<<endl;	
	}
	
	return 0;
}
