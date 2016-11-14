#include "propertymanager.h"

class Graph{

private:
	size_t _numNodes;
	size_t _numEdges;
	EDGEID _edgeIdGen;

	map<NODEID, NODE> _nodes;
	map<EDGEID, EDGE> _edges;
	map<pair<NODEID, NODEID>, EDGEID> _edgeIndex;

	EDGEID get_available_edge_id();

public:

	PropertyManager nodeProperties;
	PropertyManager edgeProperties;
	
	// Constructor and destructor
	Graph();
	~Graph();

	// Printing functions
	void print_graph();

	// Numerical queries
	size_t total_nodes();
	size_t total_edges();
	size_t node_degree(NODEID v);
	size_t node_indegree(NODEID v);
	size_t node_outdegree(NODEID v);

	// Node structural operations
	bool node_exists(NODEID v);
	bool add_node(NODEID v);
	bool del_node(NODEID v);

	// Edge structural operations
	bool edge_exists(EDGEID e);
	bool edge_exists(NODEID v, NODEID u);
	bool add_edge(NODEID v, NODEID u);
	bool add_edge(EDGEID e, NODEID v, NODEID u);
	bool del_edge(EDGEID e);
	bool del_edge(NODEID v, NODEID u);

	// Query an EDGEID from a pair
	EDGEID edgeId(NODEID v, NODEID u);
};
