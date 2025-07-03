#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<ll, int>
const ll INF = 1e18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
    }

    vector<vector<ll>> dist(n + 1, vector<ll>(2, INF));
    dist[1][0] = 0;

    priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<>> pq;
    pq.push({0, 1, 0}); // cost, node, state (0 = not used discount, 1 = used)

    while (!pq.empty()) {
        auto [currDist, node, used] = pq.top();
        pq.pop();

        if (currDist > dist[node][used]) continue;

        for (auto [nbr, w] : graph[node]) {
            // No discount used yet
            if (used == 0) {
                // Go to nbr without using discount
                if (currDist + w < dist[nbr][0]) {
                    dist[nbr][0] = currDist + w;
                    pq.push({dist[nbr][0], nbr, 0});
                }
                // Use discount now
                if (currDist + w / 2 < dist[nbr][1]) {
                    dist[nbr][1] = currDist + w / 2;
                    pq.push({dist[nbr][1], nbr, 1});
                }
            } else {
                // Already used discount, must pay full price
                if (currDist + w < dist[nbr][1]) {
                    dist[nbr][1] = currDist + w;
                    pq.push({dist[nbr][1], nbr, 1});
                }
            }
        }
    }

    cout << dist[n][1] << "\n";
    return 0;
}
