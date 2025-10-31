#include <bits/stdc++.h>
using namespace std;

struct Edge {
  int to;
  long long cap;
  int rev;
  Edge(int _to, long long _cap, int _rev) : to(_to), cap(_cap), rev(_rev) {}
};

struct Dinic {
  int n;
  vector<vector<Edge>> g;
  vector<int> level;
  vector<int> it;

  Dinic(int n) : n(n), g(n), level(n), it(n) {}

  void add_edge(int u, int v, long long cap) {
    g[u].emplace_back(v, cap, (int)g[v].size());
    g[v].emplace_back(u, 0LL, (int)g[u].size() - 1);
  }

  bool bfs(int s, int t) {
    fill(level.begin(), level.end(), -1);
    queue<int> q;
    level[s] = 0;
    q.push(s);

    while(!q.empty()) {
      int u = q.front(); q.pop();
      for(const Edge &e : g[u]) {
        if(e.cap > 0 && level[e.to] < 0) {
          level[e.to] = level[u] + 1;
          q.push(e.to);
        }
      }
    }

    return level[t] != -1;
  }

  long long dfs(int u, int t, long long f) {
    if(u == t) return f;

    for(int &i = it[u]; i < (int)g[u].size(); ++i) {
      Edge &e = g[u][i];
      if(e.cap <= 0) continue;
      if(level[e.to] != level[u] + 1) continue;
      long long pushed = dfs(e.to, t, min(f, e.cap));
      if(pushed > 0) {
        e.cap -= pushed;
        g[e.to][e.rev].cap += pushed;
        return pushed;
      }
    }

    return 0;
  }

  long long max_flow(int s, int t) {
    long long flow = 0;
    const long long INF = (long long)4e18;
    while(bfs(s, t)) {
      fill(it.begin(), it.end(), 0);
      while(true) {
        long long pushed = dfs(s, t, INF);
        if(pushed == 0) break;
        flow += pushed;
      }
    }
    return flow;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  Dinic dinic(n);

  for(int i = 0; i < m; ++i) {
    int a, b;
    long long c;
    cin >> a >> b >> c;
    --a;  --b;
    dinic.add_edge(a, b, c);
  }

  long long maxFlow = dinic.max_flow(0, n - 1);
  cout << maxFlow << "\n";
  return 0;
}
