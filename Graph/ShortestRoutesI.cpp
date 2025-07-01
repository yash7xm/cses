#include <bits/stdc++.h>
using namespace std;

#define int long long
const long long INF = 1e18;

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Graph: adjacency list of (neighbor, cost)
    vector<vector<pair<int, int>>> graph(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        graph[u].push_back({v, cost}); // directed edge
    }

    // Distance from node 1 to all others
    vector<long long> dist(n + 1, INF);
    dist[1] = 0;

    // Min-heap of (current_dist, node)
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [currDist, node] = pq.top();
        pq.pop();

        // Skip if we already have a better distance
        if (currDist > dist[node]) continue;

        for (auto [neighbor, weight] : graph[node]) {
            if (dist[node] + weight < dist[neighbor]) {
                dist[neighbor] = dist[node] + weight;
                pq.push({dist[neighbor], neighbor});
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << dist[i] << " ";
    }

    return 0;
}
