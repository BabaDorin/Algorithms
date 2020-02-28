#include <iostream>
#include <vector>
#include <stack>
using namespace std;

//Algorith for finding strongly connected components

//U and V are called strongly connected algorithms when there is a path
//from U to V and from V to U. It means that n nodes are strongly connected
//when where exists a path from each to each node.

//There is a great explanation why we have to use the stack
//in this video => https://www.youtube.com/watch?v=09_LlHjoEiY&list=WL&index=24&t=10618s

//Number of nodes
int n;
//Adiacency List
vector<int> G[100];

//variables
int id = 0;
int sccCount = 0;

//Id of every node
int ids[100];
//low-link value of each node.
//A low link value is the smalles id in a cicle
int low[100];

//To keep track of the nodes which are in stack
bool inStack[100];
stack<int> Stk;

void dfs(int startNode){
	//Home stuff
	Stk.push(startNode);
	inStack[startNode] = true;
	ids[startNode] = id;
	low[startNode] = id;
	id++;
	
	//check the neighbours of startNode and lowLink on callback
	for(int i=0; i<G[startNode].size(); i++){
		int nextNode = G[startNode][i];
		
		//If the nextNode is unvisited
		if(ids[nextNode]==-1){
			dfs(nextNode);
		} 
		
		//There can be the case when the nextNode is visited and it is in our stack.
		//it means that a cicle has been found.
		//so we do the low-link stuff
		if(inStack[nextNode]) low[startNode] = min(low[startNode], low[nextNode]);
	}
	
	//The last part is to pop out from the stack the cicle.
	//it happens after having visited all the neighbours of startNode,
	//if we are at the start of a SCC, then we have to empty the stack until we're back
	//to the startnode of scc
	
	//We know that we are at the starting of a cicle when the id of the current node is equal to the
	//low-link value of it.
	if(ids[startNode]==low[startNode]){
		int node;
		while(!Stk.empty()){
			node = Stk.top();
			Stk.pop();
			inStack[node]=false;
			
			//All the nodes within the current cicle should have the same ID
			low[node] = ids[startNode];
			
			//there may be nodes left in the stack, so we don't have to touch them now.
			//We pop only the elements on the top of startNode (Which have been visited after
			//visiting the startNode);
			if(node==startNode) break;
		}
		
		//Strongly connected components found.
		sccCount++;
	}
}

void findSccs(){
	for(int i=0; i<n; i++) ids[i] = -1; //Unvisited
	
	for(int i=0; i<n; i++){
		//We start the dfs whenever we find an unvisited node.
		if(ids[i]==-1){
			dfs(i);
		}
	}
}

int main(int argc, char** argv) {
	n = 8;
	
	G[6].push_back(0);
	G[6].push_back(2);
	G[3].push_back(4);
	G[6].push_back(4);
	G[2].push_back(0);
	G[0].push_back(1);
	G[4].push_back(5);
	G[5].push_back(6);
	G[3].push_back(7);
	G[7].push_back(5);
	G[1].push_back(2);
	G[7].push_back(3);
	G[5].push_back(0);
	
	findSccs();
	cout<<"Number of strongly connected components:"<<sccCount<<endl;
	for(int i=0; i<8; i++){
		cout<<low[i]<<" ";
	}
	return 0;
}
