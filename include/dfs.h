#pragma once

#include <vector>
#include "igraph.h"

using namespace std;

namespace GraphAlgorithms
{
	vector<NODEID> dfs(iGraph* G, NODEID root);
}
