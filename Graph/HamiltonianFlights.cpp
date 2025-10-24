#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> adj(n);
  for(int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    --a; --b;
    adj[a].push_back(b);
  }

  int FULL = (1 << n);
  vector<vector<ll>> dp(FULL, vector<ll>(n, 0));

  dp[1 << 0][0] = 1;

  for(int mask = 0; mask < FULL; ++mask) {
    for(int u = 0; u < n; ++u) {
      if(!(mask & (1 << u))) continue;
      ll ways = dp[mask][u];
      if(!ways) continue;

      for(int v : adj[u]) {
        if(mask & (1 << v)) continue;
        int nextMask = mask | (1 << v);
        dp[nextMask][v] = (dp[nextMask][v] + ways) % MOD;
      }
    }
  }

  cout << dp[FULL - 1][n - 1] % MOD << "\n";
  return 0;
}
