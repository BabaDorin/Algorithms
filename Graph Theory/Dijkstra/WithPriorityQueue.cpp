#include <iostream>
#include <queue>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("dijkstra.in");
ofstream fout("dijkstra.out");

//Adiacency list
vector<pair<int,int> > Map[50005];

//n - number of nodes, m - number of edges
int n,m;

//Distance list
int D[50005];

//To keep trak of the nodes that are already in list
//We need it so we won't insert a node multimple times into the queue.
bool InCoada[50005];

struct compara{
	bool operator() (int x, int y){
		return D[x] > D[y];
	}
};

//Priority queue that will sort elements based on calculated distance, so everytime the .top() element will be that
//node which distance in D is least.
priority_queue<int, vector<int>, compara> Coada;

//Dijkstra from start node to whatever node
void dijkstra(int nodStart){
	
	//Init with infinite all the distances
	for(int i=1; i<=n; i++){
		D[i]=2147483647;
	}
	
	//Set the distance from start node to start node to 0, put the node in queue and set the incoada[nod] = true;
	D[nodStart] = 0;
	Coada.push(nodStart);
	InCoada[nodStart] = true;
	
	while(!Coada.empty()){
		
		//While there are elements into queue	
		//Pop the top element, remove it from the queue and set the InCoada to false, because it is no more in queue
		int nodCurent = Coada.top();
		Coada.pop();
		InCoada[nodCurent] = false;
		
		//Now, for each of it's neighbours do the following
		for(size_t i=0; i<Map[nodCurent].size(); i++){
			
			//Get the nodeID and the cost from current node to that node.
			int Vecin  = Map[nodCurent][i].first;
			int Cost = Map[nodCurent][i].second;
			
			//Count the distance to Vecin through current node
			if(D[nodCurent] + Cost < D[Vecin]){
				D[Vecin] = D[nodCurent] + Cost;
				
				//Insert the neighbour into queue if it is not there yet.
				if(InCoada[Vecin]==false){
					Coada.push(Vecin);
					InCoada[Vecin] = true;
				}
			}
		}
	}
}

int main(int argc, char** argv) {
	
	//Read the data from the file.
	
	fin>>n>>m;
	
	for(int i=0; i<m; i++){
		int x, y, c;
		fin>>x>>y>>c;
		Map[x].push_back(make_pair(y,c));
	}
	
	//Start the dijkstra from node 1
	dijkstra(1);
	
	//Print the distances, if distance is equal to infinite, then it means that specific node is not accesible from node with id 1
	for(int i = 2; i <= n; i++)
    {
        if(D[i] != 2147483647)
            fout << D[i] << " ";
        else
            fout << "0 ";
    }
    
	return 0;
}
