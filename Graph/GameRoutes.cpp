#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n,m;
	cin >> n >> m;

	vector<vector<int>> graph(n+1);

	for(int i=0; i < m; ++i) {
		int u,v;
		cin >> u >> v;
		graph[u].push_back(v);
	}

	// Topological Sort using Kahn's Algorithm
    vector<int> indeg(n + 1, 0);
    for (int u = 1; u <= n; ++u) {
        for (int v : graph[u]) {
            indeg[v]++;
        }
    }

    queue<int> q;
    vector<int> order;

    for (int i = 1; i <= n; ++i) {
        if (indeg[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : graph[u]) {
            indeg[v]--;
            if (indeg[v] == 0) {
                q.push(v);
            }
        }
    }

    const int MOD = 1e9 + 7;
	vector<int> dp(n + 1, 0);
	dp[1] = 1;

	for (int u : order) {
		for (int v : graph[u]) {
			dp[v] = (dp[v] + dp[u]) % MOD;
		}
	}

	cout << dp[n] << "\n";
}