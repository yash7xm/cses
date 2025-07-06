#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    // Step 1: Topological Sort using Kahn's Algorithm
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

    // Step 2: Longest path DP on topological order
    vector<int> dp(n + 1, INT_MIN); // distance
    vector<int> parent(n + 1, -1);
    dp[1] = 0;

    for (int u : order) {
        if (dp[u] == INT_MIN) continue;
        for (int v : graph[u]) {
            if (dp[v] < dp[u] + 1) {
                dp[v] = dp[u] + 1;
                parent[v] = u;
            }
        }
    }

    // Step 3: Check if path exists
    if (dp[n] == INT_MIN) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    // Step 4: Reconstruct the path
    vector<int> path;
    int curr = n;
    while (curr != -1) {
        path.push_back(curr);
        curr = parent[curr];
    }

    reverse(path.begin(), path.end());

    cout << path.size() << '\n';
    for (int node : path) {
        cout << node << ' ';
    }
    cout << '\n';

    return 0;
}
