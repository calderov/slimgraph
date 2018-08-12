#include <vector>
#include <algorithm>
#include "igraph.h"

using namespace std;

namespace GraphAlgorithms
{
	vector<NODEID> dfs(iGraph* G, NODEID root)
	{
		vector<NODEID> pending;
		vector<NODEID> visited;

		// DFS uses a stack keep
		// track of pending nodes
		pending.push_back(root);

		while (!pending.empty())
		{
			NODEID v = pending.back();
			pending.pop_back();

			// If the node has not been visited,
			// add it to the visited vector and
			// its outgoing neighbors to the stack
			if (find(visited.begin(), visited.end(), v) == visited.end())
			{
				visited.push_back(v);

				for (NODEID u: G->get_node(v).outNeighbors)
				{
					pending.push_back(u);
				}
			}
		}

		return visited;
	}
}
