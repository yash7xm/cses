#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int, ll>>> graph(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }

    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    vector<vector<ll>> dist(n + 1);
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();

        if (dist[u].size() >= k) continue;
        dist[u].push_back(d);

        for (auto [v, w] : graph[u]) {
            ll new_dist = d + w;
            pq.push({new_dist, v});
        }
    }

    for (int i = 0; i < k; ++i) {
        cout << dist[n][i] << " ";
    }
    cout << endl;

    return 0;
}