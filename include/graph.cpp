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
	del_edge(e);

	return true;
}