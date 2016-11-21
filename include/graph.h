#include "propertymanager.h"

class Graph{

private:
	size_t _numNodes;
	size_t _numEdges;
	EDGEID _edgeIdGen;

	map<NODEID, NODE> _nodes;
	map<EDGEID, EDGE> _edges;
	map<pair<NODEID, NODEID>, EDGEID> _edgeIndex;

	PropertyManager _nodeProperties;
	PropertyManager _edgeProperties;

	EDGEID get_available_edge_id();

public:

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
	EDGEID get_edge_id(NODEID v, NODEID u);

	// Query total properties
	size_t total_node_properties();
	size_t total_edge_properties();

	// Node Property handling functions
	bool add_node_property(PROPERTY_NAME name, PROPERTY_TYPE type);
	bool set_node_property(NODEID v, PROPERTY_NAME name, const char* value);
	bool set_node_property(NODEID v, PROPERTY_NAME name, string value);
	bool del_node_property(PROPERTY_NAME name);
	bool del_all_node_properties();

	void print_node_properties(NODEID v);
	void print_node_properties();

	PROPERTY_RESULT get_node_property(NODEID v, PROPERTY_NAME name);

	template <typename T> bool set_node_property(NODEID v, PROPERTY_NAME name, T value)
	{
		if (node_exists(v))
			return _nodeProperties.set(v, name, value);
		return false;
	}

	// Edge Property handling functions
	bool add_edge_property(PROPERTY_NAME name, PROPERTY_TYPE type);
	bool set_edge_property(EDGEID e, PROPERTY_NAME name, const char* value);
	bool set_edge_property(EDGEID e, PROPERTY_NAME name, string value);
	bool set_edge_property(NODEID v /*from*/, NODEID u /*to*/, PROPERTY_NAME name, const char* value);
	bool set_edge_property(NODEID v /*from*/, NODEID u /*to*/, PROPERTY_NAME name, string type);
	bool del_edge_property(PROPERTY_NAME name);
	bool del_all_edge_properties();

	void print_edge_properties(NODEID v /*from*/, NODEID u /*to*/);
	void print_edge_properties(EDGEID e);
	void print_edge_properties();

	PROPERTY_RESULT get_edge_property(EDGEID e, PROPERTY_NAME name);
	PROPERTY_RESULT get_edge_property(NODEID v /*from*/, NODEID u /*to*/, PROPERTY_NAME name);

	template <typename T> bool set_edge_property(EDGEID e, PROPERTY_NAME name, T value)
	{
		if (edge_exists(e))
			return _edgeProperties.set(e, name, value);
		return false;
	}

	template <typename T> bool set_edge_property(NODEID v /*from*/, NODEID u /*to*/, PROPERTY_NAME name, T value)
	{
		if (edge_exists(v, u))
			return _edgeProperties.set(get_edge_id(v, u), name, value);
		return false;
	}

};
