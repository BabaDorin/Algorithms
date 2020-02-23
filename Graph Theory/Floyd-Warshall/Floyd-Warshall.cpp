#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
ifstream fin("floyd.in");

// computes the shortest distances between every pair of vertices in the input graph.

//Number of nodes
int n;

//Adiacency Matrix
int Map[1000][1000];

//Path Matrix => for more info - https://www.youtube.com/watch?v=09_LlHjoEiY&t=8085s
int Path[1000][1000];

void floyd(){
	/*
			 (k)
			/	\	
		  (i)---(j)
	*/
	for(int k=0; k<n; k++){
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				if(Map[i][k] + Map[k][j] < Map[i][j]){
					Map[i][j] = Map[i][k] + Map[k][j];
					
					//in this case, to get from i to j we have to go from i to k and then from k to j, so
					//the path from i to j is made up from path from i to k (+ j, which should not be included)
					Path[i][j] = Path[i][k];
				}
			}
		}
	}
}

//this frunction reconstructs the path from start to end based on Path matrix.
//it returns a vector if nodes, which will be the path to get from start to end.
vector<int> ReconstructPath(int start, int end){
	
	vector<int> path;
	
	//If there is no way from start to end
	if(Map[start][end]==99999999) return path;
	
	//Starting the process with start node.
	int at = start;
	
	while(at!=end){
		//reconstruct the path step by step
		path.push_back(at);
		
		//Now go to the next node on the way to end node.
		at=Path[at][end];
	}
	
	//Don't forget to include the end node
	path.push_back(end);
	
	return path;
}

int main(int argc, char** argv) {
	
	n = 5;
	
	//For the first, the adiacency matrix has to be initialized with values of infinite, except the main diagonal
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			if(i==j) Map[i][j]=0; 
			else
			Map[i][j]=99999999;
		}
	}
	
	//Set the edges
	Map[0][1] = 1;
	Map[0][3] = 4;
	Map[1][2] = 2;
	Map[2][3] = 8;
	Map[2][4] = 3;
	Map[3][4] = 16;
	Map[4][0] = 9;
	
	//init the path matrix
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			if(Map[i][j]!=99999999)
				Path[i][j] = j; // 0 -> 1
		}
	}
	
	//Run the algo
	floyd();
	
	vector<int> path = ReconstructPath(2,1);
	
	//Print the adiacency matrix.
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			if(Map[i][j]==99999999)
				cout<<"0 ";
			else
			cout<<Map[i][j]<<" ";
		}
		cout<<endl;
	}
	
	//Print path from 0 to 4
	for(int i=0; i<path.size(); i++){
		cout<<path[i]<<" ";
	}
	return 0;
}
