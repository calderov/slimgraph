#include <iostream>
#include "graph.h"


/**
 * Graph constructor.
 */
Graph::Graph()
{
	_edgeIdGen = 0;
	_numNodes = 0;
	_numEdges = 0;
}


/**
 * Graph destructor.
 */
Graph::~Graph()
{}


/**
 * Print graph nodes and edges.
 */
void Graph::print_graph()
{
	cout << "Total nodes:" << _numNodes << endl;
	cout << "Total edges:" << _numEdges << endl;

	cout << endl;
	cout << "Nodes:" << endl;
	for (map<NODEID, NODE>::iterator it = _nodes.begin(); it != _nodes.end(); ++it)
	{
		cout << "  " << it->first;
	}

	cout << "\n" << endl;
	cout << "Edges:" << endl;
	for (map<EDGEID, EDGE>::iterator it = _edges.begin(); it != _edges.end(); ++it)
	{
		cout << "  " << it->first << " : " << it->second.from << "," << it->second.to << endl;
	}
}


/**
 * Returns the total number of nodes.
 */
size_t Graph::total_nodes()
{
	return _numNodes;
}


/**
 * Returns the total number of edges.
 */
size_t Graph::total_edges()
{
	return _numEdges;
}


/**
 * Returns the given node's degree.
 */
size_t Graph::node_degree(NODEID v)
{
	return node_indegree(v) + node_outdegree(v);
}


/**
 * Returns the given node's in-degree.
 */
size_t Graph::node_indegree(NODEID v)
{
	return _nodes[v].inNeighbors.size();
}


/**
 * Returns the given node's out-degree.
 */
size_t Graph::node_outdegree(NODEID v)
{
	return _nodes[v].outNeighbors.size();
}


/**
 * Generates a unique and safe EDGEID.
 */
EDGEID Graph::get_available_edge_id()
{
	while (edge_exists(_edgeIdGen))
	{
		_edgeIdGen++;
	}

	return _edgeIdGen;
}


/**
 * Generates a bad node.
 */
NODE Graph::bad_node()
{
	NODE bad_node;
	bad_node.nodeId = BAD_NODEID;
	return bad_node;
}


/**
 * Generates a bad edge.
 */
EDGE Graph::bad_edge()
{
	EDGE bad_edge;
	bad_edge.edgeId = BAD_EDGEID;
	return bad_edge;
}


/**
 * Returns true if the given node exists in the graph, 
 * returns false otherwise.
 */
bool Graph::node_exists(NODEID v)
{
	if (_nodes.count(v))
		return true;
	return false;
}


/**
 * Adds a node with the given NODEID to the graph. Returns
 * true if the addition succeeded of false otherwise.
 */
bool Graph::add_node(NODEID v)
{
	if (node_exists(v))
		return false;

	NODE newNode;
	newNode.nodeId = v;
	_nodes[v] = newNode;

	_numNodes++;

	return true;
}


/**
 * Deletes the node with the given NODEID from the graph.
 * Returns true if the deletion was performed or false if
 * there was no such node in the graph.
 */
bool Graph::del_node(NODEID v)
{
	if (!node_exists(v))
		return false;

	// Remove edges pointing to v
	for(auto u : _nodes[v].inNeighbors)
		del_edge(u, v);

	// Remove edges departing from v
	for(auto u : _nodes[v].outNeighbors)
		del_edge(v, u);

	_nodeProperties.clear(v);
	_nodes.erase(v);
	_numNodes--;

	return true;
}


/**
 * Gets a copy of the node that corresponds to the given NODEID.
 */
NODE Graph::get_node(NODEID v)
{
	if (node_exists(v))
		return _nodes[v];
	return bad_node();
}


/**
 * Returns true if the given edge exists in the graph, 
 * returns false otherwise.
 */
bool Graph::edge_exists(EDGEID e)
{
	if (_edges.count(e))
		return true;
	return false;
}


/**
 * Returns true if an edge between the given pair of nodes exists
 * in the graph, returns false otherwise.
 */
bool Graph::edge_exists(NODEID v, NODEID u)
{
	pair<NODEID, NODEID> e;
	e = pair<NODEID, NODEID>(v, u);

	if (!_edgeIndex.count(e))
		return false;
	return true;
}


/**
 * Adds an edge between the given pair of nodes to the graph. 
 * Returns true if the addition succeeded of false otherwise.
 */
bool Graph::add_edge(NODEID v, NODEID u)
{
	// If (v, u) is already a pair, abort
	if (node_exists(v) && node_exists(u))
	{
		if (edge_exists(v, u))
			return false;
	}

	// If v or u are not existing nodes, create them
	add_node(v);
	add_node(u);

	// Get an available edgeId to map with (v, u) in the _edgeIndex
	EDGEID edgeId = get_available_edge_id();

	// Create the new edge
	EDGE newEdge;
	newEdge.edgeId = edgeId;
	newEdge.from = v;
	newEdge.to = u;

	// Insert the new edge in the _edges map
	_edges[edgeId] = newEdge;

	// Map the pair (u, v) to edgeId in the _edgeIndex
	_edgeIndex[pair<NODEID, NODEID>(v, u)] = edgeId;

	// Update nodes neighbors
	_nodes[v].outNeighbors.insert(u);
	_nodes[u].inNeighbors.insert(v);

	// Update number of edges
	_numEdges++;

	return true;
}


/**
 * Adds an edge between the given pair of nodes to the graph
 * making sure the inserted edge has the specified EDGEID. 
 * Returns true if the addition succeeded of false otherwise.
 */
bool Graph::add_edge(EDGEID e, NODEID v, NODEID u)
{
	// If e is the id of an already existant edge, abort
	if (edge_exists(e))
		return false;

	// If (v, u) is already a pair, abort
	if (node_exists(v) && node_exists(u))
	{
		if (edge_exists(v, u))
			return false;
	}

	// If v or u are not existing nodes, create them
	add_node(v);
	add_node(u);

	EDGEID edgeId = e;

	// Create the new edge
	EDGE newEdge;
	newEdge.edgeId = edgeId;
	newEdge.from = v;
	newEdge.to = u;

	// Insert the new edge in the _edges map
	_edges[edgeId] = newEdge;

	// Map the pair (u, v) to edgeId in the _edgeIndex
	_edgeIndex[pair<NODEID, NODEID>(v, u)] = edgeId;

	// Update nodes neighbors and number of edges
	_nodes[v].outNeighbors.insert(u);
	_nodes[u].inNeighbors.insert(v);
	_numEdges++;

	return true;
}


/**
 * Deletes the edge with the given EDGEID from the graph.
 * Returns true if the deletion was performed or false if
 * there was no such edge in the graph.
 */
bool Graph::del_edge(EDGEID e)
{
	// If the edge does NOT exists, abort
	if (!edge_exists(e))
		return false;

	NODEID v = _edges[e].from;
	NODEID u = _edges[e].to;
	_edgeIndex.erase(pair<NODEID, NODEID>(v, u));

	_edgeProperties.clear(e);
	_edges.erase(e);
	_numEdges--;

	return true;
}


/**
 * Deletes the edge between the two given nodes from the graph.
 * Returns true if the deletion was performed or false if
 * there was no such edge in the graph.
 */
bool Graph::del_edge(NODEID v, NODEID u)
{
	// If (v, u) is NOT an existing edge, return false
	if (!edge_exists(v, u))
		return false;

	EDGEID e = _edgeIndex[pair<NODEID, NODEID>(v, u)];
	return del_edge(e);
}


/**
 * Gets a copy of the edge that corresponds to the given EDGEID.
 */
EDGE Graph::get_edge(EDGEID e)
{
	if (edge_exists(e))
		return _edges[e];
	return bad_edge();
}


/**
 * Gets a copy of the edge between the given pair of nodes.
 */
EDGE Graph::get_edge(NODEID v /*from*/, NODEID u /*to*/)
{
	if (edge_exists(v, u))
		return _edges[get_edge_id(v, u)];
	return bad_edge();
}


/**
 * Gets the EDGEID of the edge between the given pair of nodes.
 */
EDGEID Graph::get_edge_id(NODEID v, NODEID u)
{
	// If no EDGEID corresponds to the given pair, return BAD_EDGEID
	if (!edge_exists(v, u))
		return BAD_EDGEID;

	return _edgeIndex[pair<NODEID, NODEID>(v, u)];
}


/**
 * Gets the total number of node properties for the graph.
 */
size_t Graph::total_node_properties()
{
	return _nodeProperties.total_properties();
}


/**
 * Gets the total number of edge properties for the graph.
 */
size_t Graph::total_edge_properties()
{
	return _edgeProperties.total_properties();
}


/**
 * Adds a node property with the given name and type.
 */
bool Graph::add_node_property(PROPERTY_NAME name, PROPERTY_TYPE type)
{
	return _nodeProperties.add(name, type);
}


/**
 * Sets the string value for the specified node on the given property.
 */
bool Graph::set_node_property(NODEID v, PROPERTY_NAME name, const char* value)
{
	if (node_exists(v))
		return _nodeProperties.set(v, name, value);
	return false;
}


/**
 * Sets the string value for the specified node on the given property.
 */
bool Graph::set_node_property(NODEID v, PROPERTY_NAME name, string value)
{
	if (node_exists(v))
		return _nodeProperties.set(v, name, value);
	return false;
}


/**
 * Deletes the given node property.
 */
bool Graph::del_node_property(PROPERTY_NAME name)
{
	return _nodeProperties.del(name);
}


/**
 * Deletes all node properties.
 */
bool Graph::del_all_node_properties()
{
	return _nodeProperties.del_all();
}


/**
 * Prints the value of all properties for the given node.
 */
void Graph::print_node_properties(NODEID v)
{
	if (node_exists(v))
	{
		cout << "Node Properties for node " << v << ": " << endl;
		_nodeProperties.print_properties(v);
	}
}


/**
 * Prints the name and type of all node properties.
 */
void Graph::print_node_properties()
{
	cout << "Node Properties:" << endl;
	_nodeProperties.print_properties();
}


/**
 * Gets the given property value for the specified node.
 */
PROPERTY_RESULT Graph::get_node_property(NODEID v, PROPERTY_NAME name)
{
	if (node_exists(v))
		return _nodeProperties.get(v, name);

	PROPERTY_RESULT badResult;
	badResult.type = ERROR;
	return badResult;
}

/**
 * Adds an edge property with the given name and type.
 */
bool Graph::add_edge_property(PROPERTY_NAME name, PROPERTY_TYPE type)
{
	return _edgeProperties.add(name, type);
}


/**
 * Sets the string value for the specified edge on the given property.
 */
bool Graph::set_edge_property(EDGEID e, PROPERTY_NAME name, const char* value)
{
	if (edge_exists(e))
		return _edgeProperties.set(e, name, value);
	return false;
}


/**
 * Sets the string value for the specified edge on the given property.
 */
bool Graph::set_edge_property(EDGEID e, PROPERTY_NAME name, string value)
{
	if (edge_exists(e))
		return _edgeProperties.set(e, name, value);
	return false;
}


/**
 * Sets the string value for the specified edge (given as a pair of nodes) on the given property.
 */
bool Graph::set_edge_property(NODEID v /*from*/, NODEID u /*to*/, PROPERTY_NAME name, const char* value)
{
	if (edge_exists(v, u))
		return _edgeProperties.set(get_edge_id(v, u), name, value);
	return false;
}


/**
 * Sets the string value for the specified edge (given as a pair of nodes) on the given property.
 */
bool Graph::set_edge_property(NODEID v /*from*/, NODEID u /*to*/, PROPERTY_NAME name, string value)
{
	if (edge_exists(v, u))
		return _edgeProperties.set(get_edge_id(v, u), name, value);
	return false;
}



/**
 * Deletes the given edge property.
 */
bool Graph::del_edge_property(PROPERTY_NAME name)
{
	return _edgeProperties.del(name);
}


/**
 * Deletes all edge properties.
 */
bool Graph::del_all_edge_properties()
{
	return _edgeProperties.del_all();
}


/**
 * Prints the value of all properties for the given edge (given as a pair of nodes).
 */
void Graph::print_edge_properties(NODEID v, NODEID u)
{
	if (edge_exists(v, u))
		print_edge_properties(get_edge_id(v, u));
}


/**
 * Prints the value of all properties for the given edge.
 */
void Graph::print_edge_properties(EDGEID e)
{
	if (edge_exists(e))
	{
		cout << "Edge Properties for edge " << e << " = (" << _edges[e].from << ", " << _edges[e].to << ")" << endl;
		_edgeProperties.print_properties(e);
	}
}


/**
 * Prints the name and type of all edge properties.
 */
void Graph::print_edge_properties()
{
	cout << "Edge Properties:" << endl;
	_edgeProperties.print_properties();
}


/**
 * Gets the given property value for the specified edge.
 */
PROPERTY_RESULT Graph::get_edge_property(EDGEID e, PROPERTY_NAME name)
{
	if (edge_exists(e))
		return _edgeProperties.get(e, name);

	PROPERTY_RESULT badResult;
	badResult.type = ERROR;
	return badResult;
}


/**
 * Gets the given property value for the specified edge (given a a pair of nodes).
 */
PROPERTY_RESULT Graph::get_edge_property(NODEID v /*from*/, NODEID u /*to*/, PROPERTY_NAME name)
{
	if (edge_exists(v, u))
		return _edgeProperties.get(get_edge_id(v, u), name);

	PROPERTY_RESULT badResult;
	badResult.type = ERROR;
	return badResult;
}
