#include <iostream>
#include <vector>
using namespace std;

//EULERIAN PATH - A path within a graph which traverses all the edges (Edges, not nodes)
//exactly ones. Note that a node can be traversed multiple times, but an edge - only once.

//EULERIAN CICLE - The same algorithm, but the condition of existence is a little different.
//An eulerian cicle exists within a graph only if, for each node, the number of outgoing edges 
//is the same as the number of incoming edges, so inDegree[i]==outDegree[i], otherwise, there can not be
//an eulerian cicle.

//n - number of vertices, m - number of edges.
int n,m;
//Adiacency list
vector<int> G[100];
//here the eulerian path will get stored
vector<int> EulerianPath;

//The base condition for an eulerian path to exist says that 
//each node has to have the same inDegree and OutDegree. THERE CAN BE ONLY ONE NODE WITH AN EXTRA
//OUT DEGREE (The start node) AND ONLY ONE NODE WITH ONE MORE IN DEGREE (The end node).
int inDegree[100+1];
int outDegree[100+1];

//These are used in the isEulerian function
int startNode = 0, endNode = 0;

bool isEulerian(){
	//Count the number of in-out degrees and then, for each node check if the number of in nodes is equal
	//to the number of out nodes. Otherwise, if inNodes is with 1 unit greater than outnodes, then endNode++,
	//otherwise, if outnodes is greater with 1, then startnode++. In the end, there must be 0 startNode and 0 endNode
	//or 1 startNode and 1 EndNode.
	
	for(int i=1; i<=n; i++){
		//chech every neighbour of node i
		for(int j=0; j<G[i].size(); j++){
			outDegree[i]++;
			inDegree[G[i][j]]++;
		}
	}
	
	for(int i=1; i<=n; i++){
		//If the difference between inDegree and outDegree for a node is bigger than 1, there is no Eulerian Path,
		if(inDegree[i]-outDegree[i]>1 || outDegree[i]-inDegree[i]>1) return false;
		if(inDegree[i]-outDegree[i]==1) endNode++;
		if(outDegree[i]-inDegree[i]==1) startNode++;
	}
	
	if(startNode==0 && endNode==0) return true;
	if(startNode==1 && endNode==1) return true;
	return false;
}

void dfs(int start){
	
	while(outDegree[start]>0){
		//Everytime we pick a neighbour of node i, we have to decrement the value of outDegree[i]
		//because we've visited one edge.
		int nextNode = G[start][outDegree[start]-1];
		outDegree[start]--;
		dfs(nextNode);
	}
	
	//The while loop is done when there are no out edges, so we have to insert the node into the vector.
	EulerianPath.push_back(start);
}

void FindEulerianPath(){
	//Pick startNode
	//Initially, the start node is set to 1, and it is valid when all the nodes have the amount of in-edges equal to 
	//the amount of out-edges.
	//Otherwise, there is a node that has one extra out-edge, and that node is the startNode.
	int start = 1;
	if(startNode==0) {}
	else for(int i=1; i<=n; i++){
		if(outDegree[i]-inDegree[i]==1) start = i;
	}
	
	//Start dfs fron startNode
	dfs(start);
}

int main(int argc, char** argv) {
	
	n = 6;
	//initialize the adiacency list
	G[1].push_back(2);
	G[1].push_back(3);
	G[2].push_back(2);
	G[2].push_back(4);
	G[2].push_back(4);
	G[3].push_back(1);
	G[3].push_back(2);
	G[3].push_back(5);
	G[4].push_back(3);
	G[4].push_back(6);
	G[5].push_back(6);
	G[6].push_back(3);
	
	//Now, check if there is an eulerian path
	if(!isEulerian()){
		cout<<"There is no eulerian path.";
		return 0;
	}
	
	//Run etasamaia
	FindEulerianPath();
	
	//Print the eulerian path from the end to beginning
	cout<<"The eulerian path: ";
	for(int i=EulerianPath.size()-1; i>=0; i--){
		cout<<EulerianPath[i]<<" ";
	}
	
	return 0;
}
