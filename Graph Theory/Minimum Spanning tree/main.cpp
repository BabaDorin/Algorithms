#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//MINIMUM SPANNING TREE - Given a graph with edges and costs, find the most optimal way
//to connect all the nodes with a minimum cost path. smth like kruskal algorithm

struct edge{
	int from;
	int to;
	int cost;
};

//Number of nodes and edges
int n,m;
//Adiacency list
vector<pair<int,int> > G[100];
//number of already processed edges
int TraversedEdges = 0;
//Visited or not
bool visited[100];
int costs[100];
int minimumCost;
vector<int> MinimumSpanningTree;

struct compare{
	bool operator() (edge x, edge y){
		return x.cost > y.cost;
	}
};

priority_queue< edge, vector<edge>, compare> coada; 

void AddEdge(int from, int to, int cost){
	//This algorithm works with directed graphs, so in this case we have an unidirected graph
	//which in easily transformed into a directed graph where the distance from node a to b is the 
	//same as the distance from node b to a.
	G[from].push_back(make_pair(to,cost));	
	G[to].push_back(make_pair(from,cost));
}

void MinSpanningTree(int start){
	//mark the node as visited,
	
	//skip current node if it has been already visited via another path
	
	//go through all the neighbours and insrt the cost from the current node to the specific
	//node into the priority queue (Only if that node has not been visited yet)
	
	//extract the most promising node from the priority queue and increment the traversedEdge
	
	//Make a recursive call to this function and send that most promising node as parameter.
	
	visited[start] = true;
	MinimumSpanningTree.push_back(start);
	
	//insert the neighbours of start node into the queue
	for(int i=0; i<G[start].size(); i++){
		//if the neighbour is not visited yet, insert the edge into the queue
		edge next;
		next.from = start;
		next.to = G[start][i].first;
		next.cost = G[start][i].second;
		if(!visited[next.to])
			coada.push(next);
	}
	
	while(TraversedEdges!=m && !coada.empty()){
		edge next = coada.top();
		coada.pop();
		
		if(visited[next.to])continue;
		
		MinimumSpanningTree.push_back(next.to);
		minimumCost+=next.cost;
		visited[next.to] = true;
		TraversedEdges++;
		
		//go through neighbours of node next
		for(int i=0; i<G[next.to].size(); i++){
			if(visited[G[next.to][i].first]) continue;
			edge e;
			e.from = next.to;
			e.to = G[next.to][i].first;
			e.cost = G[next.to][i].second;
			
			coada.push(e);
		}
	}
}

int main(int argc, char** argv) {
	
	n = 10;
	m = n-1;
	AddEdge(0,1,5);
	AddEdge(1,2,4);
	AddEdge(2,9,2);
	AddEdge(0,4,1);
	AddEdge(0,3,4);
	AddEdge(1,3,2);
	AddEdge(2,7,4);
	AddEdge(2,8,1);
	AddEdge(9,8,0);
	AddEdge(4,5,1);
	AddEdge(5,6,7);
	AddEdge(6,8,4);
	AddEdge(4,3,2);
	AddEdge(5,3,5);
	AddEdge(3,6,11);
	AddEdge(6,7,1);
	AddEdge(3,7,2);
	AddEdge(7,8,6);
	
    MinSpanningTree(0);
	
	cout<<"Minimum Cost: "<<minimumCost<<endl;
	cout<<"Minimum Spanning Tree: ";
	for(int i=0; i<MinimumSpanningTree.size(); i++){
		cout<<MinimumSpanningTree[i]<<" ";
	}
}
