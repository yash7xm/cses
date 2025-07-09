#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n,m;
	cin >> n >> m;

	vector<vector<pair<int, int>>> graph(n+1);
	vector<int> visited(n+1, false);

	for(int i=0; i<m; ++i) {
		int u, v, wt;
		cin >> u >> v >> wt;
		graph[u].push_back({v, wt});
		graph[v].push_back({u, wt});
	}

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	pq.push({0, 1});

	long long res = 0;

	while(!pq.empty()) {
		auto [cost, node] = pq.top();
		pq.pop();

		if(visited[node]) continue;
		visited[node] = true;

		res += cost;

		for(auto [nbr, wt] : graph[node]) {
			if(!visited[nbr]) {
				pq.push({wt, nbr});
			}
		}
	}

	for(int i=1; i<=n; ++i) {
		if(!visited[i]) {
			cout << "IMPOSSIBLE" << endl;
			return 0;
		}
	}

	cout << res << endl;
	return 0;
}