#pragma once

#include "propertymanager.h"

class iGraph{

protected:
	size_t _numNodes;
	size_t _numEdges;
	EDGEID _edgeIdGen;

	map<NODEID, NODE> _nodes;
	map<EDGEID, EDGE> _edges;
	map<pair<NODEID, NODEID>, EDGEID> _edgeIndex;

	PropertyManager _nodeProperties;
	PropertyManager _edgeProperties;

	virtual EDGEID get_available_edge_id()                = 0;
	virtual NODE bad_node()                               = 0;
	virtual EDGE bad_edge()                               = 0;

public:

	// Constructor and destructor
	iGraph(){}
	~iGraph(){}

	// Printing functions
	virtual void print_graph()                            = 0;

	// Numerical queries
	virtual size_t total_nodes()                          = 0;
	virtual size_t total_edges()                          = 0;
	virtual size_t node_degree(NODEID v)                  = 0;
	virtual size_t node_indegree(NODEID v)                = 0;
	virtual size_t node_outdegree(NODEID v)               = 0;

	// Node structural operations
	virtual bool node_exists(NODEID v)                    = 0;
	virtual bool add_node(NODEID v)                       = 0;
	virtual bool del_node(NODEID v)                       = 0;
	virtual NODE get_node(NODEID v)                       = 0;

	// Edge structural operations
	virtual bool edge_exists(EDGEID e)                    = 0;
	virtual bool edge_exists(NODEID v, NODEID u)          = 0;
	virtual bool add_edge(NODEID v, NODEID u)             = 0;
	virtual bool add_edge(EDGEID e, NODEID v, NODEID u)   = 0;
	virtual bool del_edge(EDGEID e)                       = 0;
	virtual bool del_edge(NODEID v, NODEID u)             = 0;
	virtual EDGE get_edge(EDGEID e)                       = 0;
	virtual EDGE get_edge(NODEID v, NODEID u)             = 0;

	// Query an EDGEID from a pair
	virtual EDGEID get_edge_id(NODEID v, NODEID u)         = 0;

	// Query total properties
	virtual size_t total_node_properties()                 = 0;
	virtual size_t total_edge_properties()                 = 0;

	// Node Property handling functions
	virtual bool add_node_property(PROPERTY_NAME name, PROPERTY_TYPE type)                      = 0;
	virtual bool set_node_property(NODEID v, PROPERTY_NAME name, const char* value)             = 0;
	virtual bool set_node_property(NODEID v, PROPERTY_NAME name, string value)                  = 0;
	virtual bool del_node_property(PROPERTY_NAME name)                                          = 0;
	virtual bool del_all_node_properties()                                                      = 0;

	virtual void print_node_properties(NODEID v)                                                = 0;
	virtual void print_node_properties()                                                        = 0;

	virtual PROPERTY_RESULT get_node_property(NODEID v, PROPERTY_NAME name)                     = 0;

	/**
	  * Sets the numerical value for the specified node on the given property.
	  */
	template <typename T> bool set_node_property(NODEID v, PROPERTY_NAME name, T value);

	// Edge Property handling functions
	virtual bool add_edge_property(PROPERTY_NAME name, PROPERTY_TYPE type)                      = 0;
	virtual bool set_edge_property(EDGEID e, PROPERTY_NAME name, const char* value)             = 0;
	virtual bool set_edge_property(EDGEID e, PROPERTY_NAME name, string value)                  = 0;
	virtual bool set_edge_property(NODEID v, NODEID u, PROPERTY_NAME name, const char* value)   = 0;
	virtual bool set_edge_property(NODEID v, NODEID u, PROPERTY_NAME name, string type)         = 0;
	virtual bool del_edge_property(PROPERTY_NAME name)                                          = 0;
	virtual bool del_all_edge_properties()                                                      = 0;

	virtual void print_edge_properties(NODEID v, NODEID u)                                      = 0;
	virtual void print_edge_properties(EDGEID e)                                                = 0;
	virtual void print_edge_properties()                                                        = 0;

	virtual PROPERTY_RESULT get_edge_property(EDGEID e, PROPERTY_NAME name)                     = 0;
	virtual PROPERTY_RESULT get_edge_property(NODEID v, NODEID u, PROPERTY_NAME name)           = 0;

	/**
	  * Sets the numerical value for the specified edge on the given property.
	  */
	template <typename T> bool set_edge_property(EDGEID e, PROPERTY_NAME name, T value);


	/**
	  * Sets the numerical value for the specified edge (given as a pair of nodes) on the given property.
	  */
	template <typename T> bool set_edge_property(NODEID v, NODEID u, PROPERTY_NAME name, T value);

};
