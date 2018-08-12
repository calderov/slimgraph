/*
Example Demo 06

Creates a simple tree and traverses it using DFS
*/

#include <iostream>
#include <vector>

#include "digraph.h"
#include "graph_algorithms.h"

using namespace std;

int main()
{
	cout << "Creating simple tree" << endl;

	DiGraph G;
	G.add_edge(0, 1);
	G.add_edge(0, 2);
	G.add_edge(0, 3);
	G.add_edge(0, 4);
	G.add_edge(0, 5);
	G.add_edge(0, 6);
	G.add_edge(0, 7);
	G.add_edge(0, 8);
	
	G.add_edge(1, 9);
	G.add_edge(1,10);
	G.add_edge(1,11);

	G.add_edge(11,12);
	G.add_edge(11,13);

	cout << "Running DFS from node 0..." << endl;
	vector<NODEID> dfs = GraphAlgorithms::dfs(&G, 0);
	
	cout << endl;
	cout << "DFS walk: " << endl;
	cout << " [ ";
	for (NODEID v : dfs)
		cout << v << " ";
	cout << "] " << endl;

	return 0;
}
