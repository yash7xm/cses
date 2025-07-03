#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, pair<int, int>> Edge;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    vector<vector<int>> graph(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v, wt;
        cin >> u >> v >> wt;
        edges[i] = {u, {v, wt}};
        graph[u].push_back(v);
    }

    vector<ll> dist(n + 1, LLONG_MIN);
    dist[1] = 0;

    // Bellman-Ford to find longest path
    for (int i = 0; i < n - 1; ++i) {
        for (auto [u, vw] : edges) {
            int v = vw.first, wt = vw.second;
            if (dist[u] != LLONG_MIN && dist[u] + wt > dist[v]) {
                dist[v] = dist[u] + wt;
            }
        }
    }

    // Detect positive cycles
    set<int> cycle_nodes;
    for (auto [u, vw] : edges) {
        int v = vw.first, wt = vw.second;
        if (dist[u] != LLONG_MIN && dist[u] + wt > dist[v]) {
            cycle_nodes.insert(v);
        }
    }

    // BFS from node 1 to find reachable cycle nodes
    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(1);

    queue<int> cycle_q;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (visited[u]) continue;
        visited[u] = true;

        if (cycle_nodes.count(u)) {
            cycle_q.push(u);
        }

        for (int v : graph[u]) {
            if (!visited[v]) {
                q.push(v);
            }
        }
    }

    // Check if any cycle node can reach node n
    visited.assign(n + 1, false);
    bool can_reach_n = false;

    while (!cycle_q.empty()) {
        int u = cycle_q.front(); cycle_q.pop();
        if (visited[u]) continue;
        visited[u] = true;
        if (u == n) {
            can_reach_n = true;
            break;
        }
        for (int v : graph[u]) {
            if (!visited[v]) {
                cycle_q.push(v);
            }
        }
    }

    if (can_reach_n)
        cout << "-1\n";
    else
        cout << dist[n] << "\n";

    return 0;
}
