#pragma once

#include <vector>
#include "graph.h"

using namespace std;

namespace GraphAlgorithms
{
	vector<NODEID> dfs(Graph* G, NODEID root);
}
