#include <iostream>
#include <vector>
#include <utility>      // std::pair, std::make_pair
#define pi pair<int , int>
using namespace std;

int getCycleWeight(int s, int e, vector<pi> prev)
{
	int totWeight = 0;

	while (s != e)
	{
		pi tmp = prev[s];
		int w = tmp.second;
		s = tmp.first;
		totWeight += w;
	}

	return totWeight;
}

int dfs(int node,
	vector<vector<int> >& adj,
	vector<vector<int> >& cost, 
	
	vector<pi> & prev,
	bool* dad,
	bool* vis)

{
	if (vis[node] && !dad[node])
		return 0;
	else if (dad[node]) {
		// cycle
		return 1;
	}
	vis[node] = 1;
	dad[node] = 1;

	for (int i = 0; i < adj[node].size(); i++) {
		int child = adj[node][i];
		int edgeWeight = cost[node][i];

		prev[child] = {node, edgeWeight};

		int ret = dfs(child, adj, cost,
			prev, dad, vis);
		if(ret == 1) { // suspet a -ve cycle.
			// check for the cycle type
			int cycleWeight = getCycleWeight(node, child, prev) + edgeWeight;
			if (cycleWeight < 0)
				return 2;
		}
		else if (ret == 2) { // -ve cycle.
			return 2;
		}
	}

	dad[node] = 0;
	return 0;
}
int negative_cycle(vector<vector<int> >& adj, vector<vector<int> >& cost) {
	int n = adj.size();

	vector<pi>  prev(n, { -1, -1 });
	bool *dad = new bool[n];
	bool *vis= new bool[n];
	
	for (int i = 0; i < n; i++) {
		vis[i] = dad[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		if (!vis[i]) {
			int ret = dfs(i, adj, cost,
				prev, dad, vis);
			if (ret == 2)
				return 1;
		}
	}
	return 0;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	vector<vector<int> > cost(n, vector<int>());
	for (int i = 0; i < m; i++) {
		int x, y, w;
		std::cin >> x >> y >> w;
		adj[x - 1].push_back(y - 1);
		cost[x - 1].push_back(w);
	}
	std::cout << negative_cycle(adj, cost);
}
