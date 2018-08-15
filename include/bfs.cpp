#include <vector>
#include <algorithm>
#include "bfs.h"

using namespace std;

namespace GraphAlgorithms
{
	vector<NODEID> bfs(DiGraph* G, NODEID root)
	{
		vector<NODEID> pending;
		vector<NODEID> visited;

		// BFS uses a queue to keep
		// track of pending nodes
		pending.insert(pending.begin(), root);

		while (!pending.empty())
		{
			NODEID v = pending.back();
		 	pending.pop_back();

			// If the node has not been visited,
			// add it to the visited vector and
			// its outgoing neighbors to the queue
		 	if (find(visited.begin(), visited.end(), v) == visited.end())
		 	{
		 		visited.push_back(v);

				for (NODEID u: G->get_node(v).outNeighbors)
				{
					pending.insert(pending.begin(), u);
				}
		 	}
		}

		return visited;
	}
}
