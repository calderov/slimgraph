/*
Example Demo 02

Stress demo. Creates a graph with 10 million nodes and 1 million edges
*/

#include <iostream>
#include <ctime>

#include "graph.h"

using namespace std;

int main()
{
	int const MAXNODES = 10000000;
	int const MAXEDGES = 1000000;
	
	Graph G;
	
	clock_t time_start;
	clock_t time_end;

  	cout << "Creating "<< MAXNODES <<" nodes" << endl;
	time_start = clock();
	for (int v = 0; v < MAXNODES; v++)
		G.add_node(v);
	time_end = clock();
  	
  	double elapsed_time_nodes = double(time_end - time_start) / CLOCKS_PER_SEC;
	
  	cout << "Creating "<< MAXEDGES <<" edges" << endl;
	time_start = clock();
	for (int e = 0; e < MAXEDGES; e++)
		G.add_edge(e % MAXNODES, (e + 1) % MAXNODES);
	time_end = clock();

  	double elapsed_time_edges = double(time_end - time_start) / CLOCKS_PER_SEC;

  	cout << endl;
	cout << "Time creating nodes: " << elapsed_time_nodes << " secs." << endl;
	cout << "Time creating edges: " << elapsed_time_edges << " secs." << endl;
	cout << "Total time: " << elapsed_time_nodes + elapsed_time_edges << " secs." << endl;

	return 0;
}
