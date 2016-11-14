/*
Example Demo 03

Creates a graph with 3 nodes and 3 edges. Then a string property is 
defined for the nodes and a numerical property is defined for the edges.
*/

#include <iostream>
#include "graph.h"

using namespace std;

int main()
{
	Graph G;
	
	G.add_node(1);
	G.add_node(2);
	G.add_node(3);

	G.add_edge(1, 2);
	G.add_edge(2, 3);
	G.add_edge(3, 1);

	G.nodeProperties.add("Name", STRING);
	G.nodeProperties.set(1, "Name", "Artur");
	G.nodeProperties.set(2, "Name", "Negro");
	G.nodeProperties.set(3, "Name", "Gibri");

	G.edgeProperties.add("W", DOUBLE);
	G.edgeProperties.set(G.edgeId(1, 2), "W", 1111111);
	G.edgeProperties.set(G.edgeId(2, 3), "W", 2222222);
	G.edgeProperties.set(G.edgeId(3, 1), "W", 3333333);

	cout << "PROPERTY \"Names\":" << endl;
	cout << 1 << " : " << G.nodeProperties.get(1, "Name").to_string() << endl;
	cout << 2 << " : " << G.nodeProperties.get(2, "Name").to_string() << endl;
	cout << 3 << " : " << G.nodeProperties.get(3, "Name").to_string() << endl;
	cout << endl;
	cout << "PROPERTY \"W\":" << endl;
	cout << 1 << " : " << G.edgeProperties.get(G.edgeId(1, 2), "W").to_string() << endl;
	cout << 2 << " : " << G.edgeProperties.get(G.edgeId(2, 3), "W").to_string() << endl;
	cout << 3 << " : " << G.edgeProperties.get(G.edgeId(3, 1), "W").to_string() << endl;


	return 0;
}
