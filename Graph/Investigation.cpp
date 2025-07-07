#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;
const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> graph(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v, wt;
        cin >> u >> v >> wt;
        graph[u].push_back({v, wt});
    }

    vector<vector<ll>> dp(n + 1, vector<ll>(4, INF));
    // dp[i][0] = min cost
    // dp[i][1] = number of shortest paths
    // dp[i][2] = min flights
    // dp[i][3] = max flights

    dp[1][0] = 0;
    dp[1][1] = 1;
    dp[1][2] = 0;
    dp[1][3] = 0;

    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [currDist, node] = pq.top();
        pq.pop();

        if (currDist > dp[node][0]) continue;

        for (auto [nbr, weight] : graph[node]) {
            ll newDist = currDist + weight;
            if (newDist < dp[nbr][0]) {
                dp[nbr][0] = newDist;
                dp[nbr][1] = dp[node][1]; // copy number of ways
                dp[nbr][2] = dp[node][2] + 1;
                dp[nbr][3] = dp[node][3] + 1;
                pq.push({newDist, nbr});
            } else if (newDist == dp[nbr][0]) {
                dp[nbr][1] = (dp[nbr][1] + dp[node][1]) % MOD;
                dp[nbr][2] = min(dp[nbr][2], dp[node][2] + 1);
                dp[nbr][3] = max(dp[nbr][3], dp[node][3] + 1);
            }
        }
    }

    cout << dp[n][0] << " " << dp[n][1] << " " << dp[n][2] << " " << dp[n][3] << "\n";

    return 0;
}
