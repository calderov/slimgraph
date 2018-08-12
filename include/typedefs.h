#pragma once

#include <unordered_map>
#include <climits>
#include <string>
#include <map>
#include <set>

using namespace std;

// Graph structure definitions
#define NODEID unsigned long
#define EDGEID unsigned long
#define BAD_NODEID ULONG_MAX
#define BAD_EDGEID ULONG_MAX


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


// Property management definitions
#define ELEMID unsigned long
#define PROPERTY_NAME  const char*
#define PROPERTY_MAP unordered_map<PROPERTY_NAME, VALUE_MAP>

enum PROPERTY_TYPE
{
	DOUBLE,
	STRING,
	ERROR
};


typedef struct PROPERTY_VALUE
{
	string valueStr;
	double valueNum;
} PROPERTY_VALUE;


typedef struct VALUE_MAP
{
	PROPERTY_TYPE type;
	unordered_map<ELEMID, PROPERTY_VALUE> element;
} VALUE_MAP;


typedef struct PROPERTY_RESULT
{
	PROPERTY_TYPE type;
	PROPERTY_VALUE value;

	string to_string()
	{
		switch (type)
		{
			case DOUBLE:
				return std::to_string(value.valueNum);
			case STRING:
				return value.valueStr;
			default:
				return "Error: Invalid value!";
		}
	}
} PROPERTY_RESULT;
