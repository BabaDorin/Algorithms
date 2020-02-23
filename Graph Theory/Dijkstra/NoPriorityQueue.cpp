#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
ifstream fin("graph.in");

//Adiacency list
vector<vector<pair<int,int> > > Map;
/*
The way Adiacency List works:
the list i contains j pairs<int,int>;
i is the from node, j.first is the to node and j.second is the cost to get from "from" to "to".

example:

<4,2> <1,4>
<3,3> <4,5>

=> Node 0 has a vertice to node 4, which cost is 2
	and it has a vertice to node 1, which cost is 4.
	
=> Node 1 has a vertice to node 3, which cost is 3
	and it has a vertice to node 4, which cost is 5.

*/

//distance from start node to other nodes.
int dist[100];

//to track the visited nodes.
bool visited[100];

//the path from start node to end node.
int path[100];

//Number of nodes
int n;

void dijkstra(int start, int end){
	
	//init distances with infinite value
	for(int i=0; i<100; i++){
		dist[i]=9999999;
	}
	
	//Set the starting node as visited and set the distance to it as 0;
	visited[start]=true;
	dist[start] = 0;
	bool isFirstNode = true;
	
	//Dijkstra strarts
	while(true){
		
		//find the closest node;
		int closestNode;
		int closestDistance = 999999999;
		
		//If it is the first node
		if(isFirstNode){
			closestNode = start;
			closestDistance = 0;
			isFirstNode = false;
		}else{
			//fint the actual closest node whose distance is assigned but it has not been visisted;
			for(int i=0; i<n; i++){
				if(!visited[i] && dist[i]<closestDistance){
					closestNode = i;
					closestDistance = dist[i];
				}
			}
		}
		
		//exit condition -> this is true only if all the nodes have been visited
		if(closestDistance == 999999999)
		break;
		
		//mark the chosed node as visited;
		visited[closestNode] = true;
		
		//Update (or not) the distance to the nodes adiacent to the current node
		//but only if that specific note has not been visited yet
		for(int i=0; i<Map[closestNode].size(); i++){
			//p.first => destination node, p.second => cost to get from current node to that node.
			pair<int,int> p = Map[closestNode][i];
			
			//Skip this itteration if the chosen node is already visited
			if(visited[p.first]) continue;
			
			//calculating the new distace to that specific node, which will be the distance we already have
			//to get from start node to the current node + distance from current node to that node (p.first)
			int newDistance = dist[closestNode] + p.second;
			if(newDistance<dist[p.first]){
				path[p.first] = closestNode;
				dist[p.first] = newDistance;
			}
		}
	}
}

int main(int argc, char** argv) {

/*
input file has this structure:

numberOfNodes numberOfVertices
fromNode toNode Cost
fromNode toNode Cost
etc etc etc
*/
	//Number of vertices;
	int m;
	
	fin>>n>>m;
	
	//The adiacency list has to be initalized so it will have n empty objects in it.
	for(int i=0; i<n; i++){
		vector<pair<int,int> > vec;
		Map.push_back(vec);
	}
	
	//Read the data and put it in adiacency list.
	for(int i=0; i<m; i++){
		int source, destination, cost;
		fin>>source>>destination>>cost;
		pair<int,int> value = make_pair(destination,cost);
		Map[source].push_back(value);
	}
	
	//Start the dijkstra's algorithm from node 0 to node 4.
	dijkstra(0,4);
	
	for(int i=0; i<n; i++){
		cout<<dist[i]<<" ";
	}
	
	cout<<endl;
	
	for(int i=0; i<n; i++){
		cout<<path[i];
	}
	
	//I want to display the path from node 4 to start node, which is 0
	int node = 4;
	vector<int> shortestPath;
	shortestPath.push_back(node);
	while(node!=0){
		shortestPath.push_back(path[node]);
		node = path[node];
	}
	
	cout<<endl;
	for(int i=shortestPath.size()-1; i>=0; i--){
		cout<<shortestPath[i]<<" ";
	}
}
