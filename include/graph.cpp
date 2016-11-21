#include <iostream>
#include "graph.h"


Graph::Graph()
{
	_edgeIdGen = 0;
	_numNodes = 0;
	_numEdges = 0;
}


Graph::~Graph()
{}


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


size_t Graph::total_nodes()
{
	return _numNodes;
}


size_t Graph::total_edges()
{
	return _numEdges;
}


size_t Graph::node_degree(NODEID v)
{
	return node_indegree(v) + node_outdegree(v);
}


size_t Graph::node_indegree(NODEID v)
{
	return _nodes[v].inNeighbors.size();
}


size_t Graph::node_outdegree(NODEID v)
{
	return _nodes[v].outNeighbors.size();
}


EDGEID Graph::get_available_edge_id()
{
	while (edge_exists(_edgeIdGen))
	{
		_edgeIdGen++;
	}

	return _edgeIdGen;
}


// NODE STRUCTURAL OPERATIONS

bool Graph::node_exists(NODEID v)
{
	if (_nodes.count(v))
		return true;
	return false;
}


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


bool Graph::del_node(NODEID v)
{
	if (node_exists(v))
	{
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

	return false;
}


// EDGE STRUCTURAL OPERATIONS

bool Graph::edge_exists(EDGEID e)
{
	if (_edges.count(e))
		return true;
	return false;
}


bool Graph::edge_exists(NODEID v, NODEID u)
{
	pair<NODEID, NODEID> e;
	e = pair<NODEID, NODEID>(v, u);

	if (!_edgeIndex.count(e))
		return false;
	return true;
}


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


bool Graph::del_edge(NODEID v, NODEID u)
{
	// If (v, u) is NOT an existing edge, return false
	if (!edge_exists(v, u))
		return false;

	EDGEID e = _edgeIndex[pair<NODEID, NODEID>(v, u)];
	return del_edge(e);
}


EDGEID Graph::get_edge_id(NODEID v, NODEID u)
{
	// If no EDGEID corresponds to the given pair, return BAD_EDGEID
	if (!edge_exists(v, u))
		return BAD_EDGEID;

	return _edgeIndex[pair<NODEID, NODEID>(v, u)];
}


// PROPERTY HANDLING FUNCTIONS
size_t Graph::total_node_properties()
{
	return _nodeProperties.total_properties();
}


size_t Graph::total_edge_properties()
{
	return _edgeProperties.total_properties();
}


bool Graph::add_node_property(PROPERTY_NAME name, PROPERTY_TYPE type)
{
	return _nodeProperties.add(name, type);
}


bool Graph::set_node_property(NODEID v, PROPERTY_NAME name, const char* value)
{
	if (node_exists(v))
		return _nodeProperties.set(v, name, value);
	return false;
}


bool Graph::set_node_property(NODEID v, PROPERTY_NAME name, string value)
{
	if (node_exists(v))
		return _nodeProperties.set(v, name, value);
	return false;
}


bool Graph::del_node_property(PROPERTY_NAME name)
{
	return _nodeProperties.del(name);
}


bool Graph::del_all_node_properties()
{
	return _nodeProperties.del_all();
}


void Graph::print_node_properties(NODEID v)
{
	if (node_exists(v))
	{
		cout << "Node Properties for node " << v << ": " << endl;
		_nodeProperties.print_properties(v);
	}
}


void Graph::print_node_properties()
{
	cout << "Node Properties:" << endl;
	_nodeProperties.print_properties();
}


PROPERTY_RESULT Graph::get_node_property(NODEID v, PROPERTY_NAME name)
{
	if (node_exists(v))
		return _nodeProperties.get(v, name);

	PROPERTY_RESULT badResult;
	badResult.type = ERROR;
	return badResult;
}


bool Graph::add_edge_property(PROPERTY_NAME name, PROPERTY_TYPE type)
{
	return _edgeProperties.add(name, type);
}


bool Graph::set_edge_property(EDGEID e, PROPERTY_NAME name, const char* value)
{
	if (edge_exists(e))
		return _edgeProperties.set(e, name, value);
	return false;
}


bool Graph::set_edge_property(EDGEID e, PROPERTY_NAME name, string value)
{
	if (edge_exists(e))
		return _edgeProperties.set(e, name, value);
	return false;
}


bool Graph::set_edge_property(NODEID v /*from*/, NODEID u /*to*/, PROPERTY_NAME name, const char* value)
{
	if (edge_exists(v, u))
		return _edgeProperties.set(get_edge_id(v, u), name, value);
	return false;
}


bool Graph::set_edge_property(NODEID v /*from*/, NODEID u /*to*/, PROPERTY_NAME name, string value)
{
	if (edge_exists(v, u))
		return _edgeProperties.set(get_edge_id(v, u), name, value);
	return false;
}


bool Graph::del_edge_property(PROPERTY_NAME name)
{
	return _edgeProperties.del(name);
}


bool Graph::del_all_edge_properties()
{
	return _edgeProperties.del_all();
}


void Graph::print_edge_properties(NODEID v, NODEID u)
{
	if (edge_exists(v, u))
		print_edge_properties(get_edge_id(v, u));
}


void Graph::print_edge_properties(EDGEID e)
{
	if (edge_exists(e))
	{
		cout << "Edge Properties for edge " << e << " = (" << _edges[e].from << ", " << _edges[e].to << ")" << endl;
		_edgeProperties.print_properties(e);
	}
}


void Graph::print_edge_properties()
{
	cout << "Edge Properties:" << endl;
	_edgeProperties.print_properties();
}


PROPERTY_RESULT Graph::get_edge_property(EDGEID e, PROPERTY_NAME name)
{
	if (edge_exists(e))
		return _edgeProperties.get(e, name);
	
	PROPERTY_RESULT badResult;
	badResult.type = ERROR;
	return badResult;
}


PROPERTY_RESULT Graph::get_edge_property(NODEID v /*from*/, NODEID u /*to*/, PROPERTY_NAME name)
{
	if (edge_exists(v, u))
		return _edgeProperties.get(get_edge_id(v, u), name);
	
	PROPERTY_RESULT badResult;
	badResult.type = ERROR;
	return badResult;
}
