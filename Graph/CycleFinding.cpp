#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, int, ll> Edge;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<Edge> edges;

    for (int i = 0; i < m; ++i) {
        int u, v;
        ll wt;
        cin >> u >> v >> wt;
        edges.push_back({u, v, wt});
    }

    // Add dummy node 0 connected to all nodes with weight 0
    for (int i = 1; i <= n; ++i) {
        edges.push_back({0, i, 0});
    }

    vector<ll> dist(n + 1, LLONG_MAX);
    vector<int> relaxant(n + 1, -1);
    dist[0] = 0;

    int x = -1;
    for (int i = 0; i <= n; ++i) {
        x = -1;
        for (auto [u, v, w] : edges) {
            if (dist[u] != LLONG_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                relaxant[v] = u;
                x = v;
            }
        }
    }

    if (x == -1) {
        cout << "NO\n";
        return 0;
    }

    // Move x back n times to ensure we are in the cycle
    for (int i = 0; i < n; ++i) {
        x = relaxant[x];
    }

    vector<int> cycle;
    for (int curr = x;; curr = relaxant[curr]) {
        cycle.push_back(curr);
        if (curr == x && cycle.size() > 1) {
            break;
        }
    }

    reverse(cycle.begin(), cycle.end());

    cout << "YES\n";
    for (int node : cycle) {
        cout << node << " ";
    }
    cout << "\n";

    return 0;
}