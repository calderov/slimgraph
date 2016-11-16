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

	G.add_node_property("Name", STRING);
	G.set_node_property(1, "Name", "Artur");
	G.set_node_property(2, "Name", "Negro");
	G.set_node_property(3, "Name", "Gibri");

	G.add_edge_property("W", DOUBLE);
	G.set_edge_property(1, 2, "W", 1111111);
	G.set_edge_property(2, 3, "W", 2222222);
	G.set_edge_property(3, 1, "W", 3333333);

	cout << "PROPERTY \"Names\":" << endl;
	cout << 1 << " : " << G.get_node_property(1, "Name") << endl;
	cout << 2 << " : " << G.get_node_property(2, "Name") << endl;
	cout << 3 << " : " << G.get_node_property(3, "Name") << endl;
	cout << endl;
	cout << "PROPERTY \"W\":" << endl;
	cout << 1 << " : " << G.get_edge_property(1, 2, "W") << endl;
	cout << 1 << " : " << G.get_edge_property(1, 2, "W") << endl;
	cout << 1 << " : " << G.get_edge_property(1, 2, "W") << endl;

	return 0;
}