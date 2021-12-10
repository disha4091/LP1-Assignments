//============================================================================
// Name        : BellmanFordAlgo.cpp
// Author      : Disha Chavan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <bits/stdc++.h>
using namespace std;
struct edge						// structure for edge
{
	int source, dest, weight ;
};
class Graph{					// Graph data
	int V_tot, E_tot ;			// total number of vertices and edges
	edge* Edges ;				// array containing edges

public:
	Graph(int v, int e){		// constructor to initialize data members
		V_tot = v ;
		E_tot = e ;
		Edges = new edge[e] ;
	}

	void input(){

		for(int i = 0 ; i < E_tot ; i++){
			cout << "For Edge " << (i+1) << " :" << endl ;
			cout << "Enter source: " ;
			cin >> Edges[i].source ;
			cout << "Enter destination: " ;
			cin >> Edges[i].dest ;
			cout << "Enter weight: " ;
			cin >> Edges[i].weight ;
		}
	}
	void display(){
		cout << "\nSource\t\tDestination\tWeight"<< endl ;
		for(int i = 0 ; i < E_tot ; i++){
			cout << Edges[i].source << "\t\t" << Edges[i].dest << "\t\t" << Edges[i].weight << endl ;
		}
	}
	void BellmanFord(){
		int src ;				// take input for source vertex
		cout << "Enter source node: " ;
		cin >> src ;

		int distance[V_tot] ;

		for(int i = 0 ; i < V_tot ; i++){	// loop to initialize distance as infinity
			distance[i] = 99999 ;
		}
		distance[src] = 0 ;		// distance of source from itself is 0

		for(int i = 0 ; i < (V_tot-1) ; i++){ 	// considering edges for v-1 times
			for(int j = 0 ; j < E_tot ; j++ ){	// for edges
				int u = Edges[j].source ;
				int v = Edges[j].dest ;
				int w = Edges[j].weight ;

				if(distance[u]!=99999 && (distance[u]+w)<distance[v]){	// update distance if less than current distance of the node
					distance[v] = distance[u]+w ;
				}

			}
		}

		for(int j = 0 ; j < E_tot ; j++ ){	// for edges
			int u = Edges[j].source ;
			int v = Edges[j].dest ;
			int w = Edges[j].weight ;

			if(distance[u]!=99999 && (distance[u]+w)<distance[v]){	// update distance if less than current distance of the node
					cout << "\nGraph contains negative cycle!!" << endl  ;
			}

		}

		cout << "\nVertex\t\tDistance" << endl ;
		for(int i = 0 ; i < V_tot ; i++){
			cout << i << "\t\t" << distance[i] << endl ;
		}

	}
};

int main() {
	int v, e ;
	cout << "\nEnter number of vertices: " ;
	cin >> v ;
	cout << "\nEnter number of edges: " ;
	cin >> e ;
	Graph* obj = new Graph(v,e) ;
	obj->input() ;
	obj->display() ;
	obj->BellmanFord() ;


}
