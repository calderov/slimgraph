#pragma once

#include <vector>
#include "digraph.h"

using namespace std;

namespace GraphAlgorithms
{
	vector<NODEID> dfs(DiGraph* G, NODEID root);
}
