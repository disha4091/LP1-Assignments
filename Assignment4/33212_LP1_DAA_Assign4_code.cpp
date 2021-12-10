//============================================================================
// Name        : TravellingSalesman.cpp
// Author      : Disha Chavan
// Version     :
// Copyright   : Your copyright notice
// Description : Travelling Salesman problem
//============================================================================

#include <bits/stdc++.h>
using namespace std;
const int N = 4;

int final_path[N+1];		// final_path[] stores the final solution ie, the path of the salesman.
bool visited[N];			// visited[] keeps track of the already visited nodes in a particular path
int final_res = INT_MAX;	// Stores the final minimum weight of shortest tour.

void copyToFinal(int curr_path[])	// Function to copy temporary solution to the final solution
{
    for (int i=0; i<N; i++)
        final_path[i] = curr_path[i];
    final_path[N] = curr_path[0];
}

int firstMin(int adj[N][N], int i)	// Function to find the minimum edge cost having an end at the vertex i
{
    int min = INT_MAX;
    for (int k=0; k<N; k++)
        if (adj[i][k]<min && i != k)
            min = adj[i][k];
    return min;
}

int secondMin(int adj[N][N], int i)	// function to find the second minimum edge cost having an end at the vertex i
{
    int first = INT_MAX, second = INT_MAX;
    for (int j=0; j<N; j++)
    {
        if (i == j)
            continue;

        if (adj[i][j] <= first)
        {
            second = first;
            first = adj[i][j];
        }
        else if (adj[i][j] <= second &&
                 adj[i][j] != first)
            second = adj[i][j];
    }
    return second;
}




//
void TSPRec(int adj[N][N], int curr_bound, int curr_weight,		// curr_bound is lower bound of the root node, curr_weight stores the weight of the path so far
            int level, int curr_path[])							// level is current level while moving in the search space tree curr_path[] -> where the solution is being stored
{

    if (level==N)												// base case is when we have reached level N i.e we have covered all the nodes once
    {
        if (adj[curr_path[level-1]][curr_path[0]] != 0)			// check if there is an edge from last vertex in path back to the first vertex
        {
            int curr_res = curr_weight +
                    adj[curr_path[level-1]][curr_path[0]];

            if (curr_res < final_res)							//  // Update final result and final path if current result is better.
            {
                copyToFinal(curr_path);
                final_res = curr_res;
            }
        }
        return;
    }


    for (int i=0; i<N; i++)								// for any other level iterate for all vertices to build the search space tree recursively
    {

        if (adj[curr_path[level-1]][i] != 0 &&			// Consider next vertex if it is not same (diagonal entry in adjacency matrix and not visited already)
            visited[i] == false)
        {
            int temp = curr_bound;
            curr_weight += adj[curr_path[level-1]][i];

            if (level==1)
              curr_bound -= ((firstMin(adj, curr_path[level-1]) +
                             firstMin(adj, i))/2);
            else
              curr_bound -= ((secondMin(adj, curr_path[level-1]) +
                             firstMin(adj, i))/2);

            // curr_bound + curr_weight is the actual lower bound for the node
            // If current lower bound < final_res, we need to explore the node
            if (curr_bound + curr_weight < final_res)
            {
                curr_path[level] = i;
                visited[i] = true;


                TSPRec(adj, curr_bound, curr_weight, level+1,curr_path);	// call TSPRec for the next level

            }


            curr_weight -= adj[curr_path[level-1]][i];		// Else we need to prune the node by resetting all changes to curr_weight and curr_bound
            curr_bound = temp;

            memset(visited, false, sizeof(visited));		// Also reset the visited array
            for (int j=0; j<=level-1; j++)
                visited[curr_path[j]] = true;
        }
    }
}


void TSP(int adj[N][N])						// This function sets up final_path[]
{
    int curr_path[N+1];



    int curr_bound = 0;
    memset(curr_path, -1, sizeof(curr_path));// initializing the curr_path and visited array
    memset(visited, 0, sizeof(curr_path));


    for (int i=0; i<N; i++)					//  initial lower bound for the root node = 1/2 * (sum of first min + second min) for all edges.
        curr_bound += (firstMin(adj, i) + secondMin(adj, i));


    curr_bound = (curr_bound&1)? curr_bound/2 + 1 : curr_bound/2; // Rounding off the lower bound to an integer

    // We start at vertex 1 so the first vertex in curr_path[] is 0
    visited[0] = true;
    curr_path[0] = 0;


    TSPRec(adj, curr_bound, 0, 1, curr_path);	//// Call to TSPRec for curr_weight equal to 0 and level 1
}


int main()
{

	int adj[N][N];									//Adjacency matrix for the given graph
	cout << "\nEnter adjacency matrix for graph: ";
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			cin >> adj[i][j];
		}
	}
    TSP(adj);

    printf("Minimum cost : %d\n", final_res);
    printf("Path Taken : ");
    for (int i=0; i<=N; i++)
        printf("%d ", final_path[i]);

    return 0;
}
