#include <unordered_map>
#include <string>
#include <map>
#include <set>

using namespace std;

#define NODEID unsigned long
#define EDGEID unsigned long

typedef struct NODE
{
	NODEID nodeId;
	set<NODEID> inNeighbors;
	set<NODEID> outNeighbors;
} NODE;

typedef struct EDGE
{
	EDGEID edgeId;
	NODEID from;	
	NODEID to;
} EDGE;