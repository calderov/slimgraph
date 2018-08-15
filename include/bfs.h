#pragma once

#include <vector>
#include "digraph.h"

using namespace std;

namespace GraphAlgorithms
{
	vector<NODEID> bfs(DiGraph* G, NODEID root);
}
