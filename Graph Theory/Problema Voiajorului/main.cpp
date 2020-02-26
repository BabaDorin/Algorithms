#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
ifstream fin("path.in");

//The shortest path to follow in ordert to go throgh the entire graph and return
//to the starting point.

//Number of nodes
int n;
//Adiacency List
vector<pair<int,int> > G[100];
bool visited[100];
//Current path length
int lungime = 0;
//Minimum path length
int lungimeMinima = 2000000000;
vector<int> ShortestPath;
vector<int> Path;
int visitedNodes = 1;
//Start Node
int start;

void dfs(int startNode){
	
	//All the nodes have been visited so we check if there is a way from the lastVisitedNode to the startNode
	if(visitedNodes == n){
		for(int i=0; i<G[startNode].size(); i++){
			
			//Once we now we've travelled the entire graph, we check to see if
			//the is there is a edge from last visited node to the first node (starting point).
			if(G[startNode][i].first == start){
				
				//If there is a node from last to start
				//Insert it in localPath and update the length
				Path[n+1] = start;
				lungime+=G[startNode][i].second;
				
				//Update the minimumPath and minimum length if it's the case
				if(lungime<lungimeMinima){
					for(int i=1; i<=n+1; i++){
						ShortestPath[i] = Path[i];
					}
					lungimeMinima = lungime;
					
					//Don't forget to step back
					lungime-=G[startNode][i].second;
					return;
				}
				//step back;
				lungime-=G[startNode][i].second;
			}
		}
	}
	
	//Optimizare.
	//If the minimum length that was already found is less than the current length, then there is no
	//sense to continue the dfs deeper
	if(lungime>lungimeMinima) return;
	
	for(int i=0; i<G[startNode].size(); i++){
		
		//Go through each neighbour
		int nextNode = G[startNode][i].first;
		
		//Send dfs to it's neighbour if it has not been visited yet
		if(!visited[nextNode]){
			visited[nextNode] = true;
			visitedNodes++;
			lungime+=G[startNode][i].second;
			Path[visitedNodes] = nextNode;	
			
			dfs(nextNode);
			
			//steps back;
			visitedNodes--;
			lungime-=G[startNode][i].second;
			visited[nextNode] = false;
		}
	}
}

void Voiajor(int startNode){
	
	visited[startNode] = true;
	Path[1] = startNode;
	
	dfs(startNode);
	
}


int main(int argc, char** argv) {
	
	int m;
	fin>>n>>m;
	
	//Initialize the paths
	for(int i=0; i<=n; i++){
		ShortestPath.push_back(-1);
		Path.push_back(-1);
	}
	
	//Read the adiacencyMatrix from the input file
	for(int i=0; i<m; i++){
		int from,to,cost;
		fin>>from>>to>>cost;
		G[from].push_back(make_pair(to,cost));
		G[to].push_back(make_pair(from,cost));
	}
	
	//Set the start node and start send the start node to Voiajor
	start = 1;
	Voiajor(1);
	
	//Displaying the results
	for(int i=1; i<=n+1; i++){
		cout<<ShortestPath[i]<<" ";
	}
	
	cout<<endl;
	cout<<"Lungimea minima: "<<lungimeMinima;
	
	return 0;
}
