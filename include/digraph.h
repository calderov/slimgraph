#pragma once
#include "igraph.h"


class DiGraph: public iGraph{

protected:
	EDGEID get_available_edge_id()                override;
	NODE bad_node()                               override;
	EDGE bad_edge()                               override;

public:

	// Constructor and destructor
	DiGraph();
	~DiGraph();

	// Printing functions
	void print_graph()                            override;

	// Numerical queries
	size_t total_nodes()                          override;
	size_t total_edges()                          override;
	size_t node_degree(NODEID v)                  override;
	size_t node_indegree(NODEID v)                override;
	size_t node_outdegree(NODEID v)               override;

	// Node structural operations
	bool node_exists(NODEID v)                    override;
	bool add_node(NODEID v)                       override;
	bool del_node(NODEID v)                       override;
	NODE get_node(NODEID v)                       override;

	// Edge structural operations
	bool edge_exists(EDGEID e)                    override;
	bool edge_exists(NODEID v, NODEID u)          override;
	bool add_edge(NODEID v, NODEID u)             override;
	bool add_edge(EDGEID e, NODEID v, NODEID u)   override;
	bool del_edge(EDGEID e)                       override;
	bool del_edge(NODEID v, NODEID u)             override;
	EDGE get_edge(EDGEID e)                       override;
	EDGE get_edge(NODEID v, NODEID u)             override;

	// Query an EDGEID from a pair
	EDGEID get_edge_id(NODEID v, NODEID u)         override;

	// Query total properties
	size_t total_node_properties()                 override;
	size_t total_edge_properties()                 override;

	// Node Property handling functions
	bool add_node_property(PROPERTY_NAME name, PROPERTY_TYPE type)                      override;
	bool set_node_property(NODEID v, PROPERTY_NAME name, const char* value)             override;
	bool set_node_property(NODEID v, PROPERTY_NAME name, string value)                  override;
	bool del_node_property(PROPERTY_NAME name)                                          override;
	bool del_all_node_properties()                                                      override;

	void print_node_properties(NODEID v)                                                override;
	void print_node_properties()                                                        override;

	PROPERTY_RESULT get_node_property(NODEID v, PROPERTY_NAME name)                     override;

	/**
	  * Sets the numerical value for the specified node on the given property.
	  */
	template <typename T> bool set_node_property(NODEID v, PROPERTY_NAME name, T value)
	{
		if (node_exists(v))
			return _nodeProperties.set(v, name, value);
		return false;
	}

	// Edge Property handling functions
	bool add_edge_property(PROPERTY_NAME name, PROPERTY_TYPE type)                      override;
	bool set_edge_property(EDGEID e, PROPERTY_NAME name, const char* value)             override;
	bool set_edge_property(EDGEID e, PROPERTY_NAME name, string value)                  override;
	bool set_edge_property(NODEID v, NODEID u, PROPERTY_NAME name, const char* value)   override;
	bool set_edge_property(NODEID v, NODEID u, PROPERTY_NAME name, string type)         override;
	bool del_edge_property(PROPERTY_NAME name)                                          override;
	bool del_all_edge_properties()                                                      override;

	void print_edge_properties(NODEID v, NODEID u)                                      override;
	void print_edge_properties(EDGEID e)                                                override;
	void print_edge_properties()                                                        override;

	PROPERTY_RESULT get_edge_property(EDGEID e, PROPERTY_NAME name)                     override;
	PROPERTY_RESULT get_edge_property(NODEID v, NODEID u, PROPERTY_NAME name)           override;

	/**
	  * Sets the numerical value for the specified edge on the given property.
	  */
	template <typename T> bool set_edge_property(EDGEID e, PROPERTY_NAME name, T value)
	{
		if (edge_exists(e))
			return _edgeProperties.set(e, name, value);
		return false;
	}

	/**
	  * Sets the numerical value for the specified edge (given as a pair of nodes) on the given property.
	  */
	template <typename T> bool set_edge_property(NODEID v, NODEID u, PROPERTY_NAME name, T value)
	{
		if (edge_exists(v, u))
			return _edgeProperties.set(get_edge_id(v, u), name, value);
		return false;
	}

};
