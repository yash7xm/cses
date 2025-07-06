#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n,m;
	cin >> n >> m;

	vector<vector<int>> graph(n+1);
	for(int i=0; i<m; ++i) {
		int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
	}

	vector<int> indeg(n+1, 0);

	for(int u = 1; u <= n; ++u) {
		for(int v : graph[u]) {
			indeg[v]++;
		}
	}

	queue<int> q;

	for(int i=1; i<=n; i++) {
		if(indeg[i] == 0) {
			q.push(i);
		}
	}

	vector<int> res;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		res.push_back(u);
		for(int v : graph[u]) {
			indeg[v]--;
			if(indeg[v] == 0) {
				q.push(v);
			}
		}
	}

	if(res.size() == n) {
		for(int node : res) {
			cout << node << " ";
		}
		cout << endl;
		return 0;
	}

	cout << "IMPOSSIBLE" << endl;
}