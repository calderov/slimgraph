/*
Example Demo 05

Stress demo. Creates an 8-tree with 1 million nodes
*/

#include <iostream>
#include <ctime>

#include "digraph.h"

using namespace std;

int main()
{
	int const MAXNODES = 1000000;
	
	DiGraph G;

	clock_t time_start;
	clock_t time_end;

  	cout << "Creating 8-tree with " << MAXNODES <<" nodes" << endl;
	
	time_start = clock();
	int u = 0;
	int v = 0;
	while (G.total_nodes() < MAXNODES)
	{
		for (int i = 0; i < 8; i++)
		{
			v++;
			G.add_edge(u, v);
		}
		u++;
	}
	time_end = clock();
  	
  	double total_elapsed_time = double(time_end - time_start) / CLOCKS_PER_SEC;

  	cout << endl;
	cout << "Total elapsed time: " << total_elapsed_time << " secs." << endl;

	return 0;
}
