/*
Example Demo 06

Creates a simple tree and traverses it using DFS
*/

#include <iostream>
#include <vector>

#include "digraph.h"
#include "graph_algorithms.h"

using namespace std;

void print_walk(vector<NODEID> walk)
{
	cout << " [ ";
	for (NODEID v : walk)
		cout << v << " ";
	cout << "] " << endl;
	cout << endl;
}

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

	cout << "Built tree:" << endl;
	G.print_graph();
	cout << endl;

	cout << "DFS walk from node 0: " << endl;
	vector<NODEID> dfs = GraphAlgorithms::dfs(&G, 0);
	print_walk(dfs);

	cout << "BFS walk from node 0: " << endl;
	vector<NODEID> bfs = GraphAlgorithms::bfs(&G, 0);
	print_walk(bfs);	

	return 0;
}
