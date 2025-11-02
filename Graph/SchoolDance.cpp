#include <bits/stdc++.h>
using namespace std;

struct Edge {
  int to;
  long long cap;
  int rev; // index of reverse edge in g[to]
  Edge(int _to, long long _cap, int _rev) : to(_to), cap(_cap), rev(_rev) {}
};

struct Dinic {
  int n;
  vector<vector<Edge>> g;
  vector<int> level, it;

  Dinic(int n = 0) { init(n); }

  void init(int n_) {
    n = n_;
    g.assign(n, {});
    level.assign(n, 0);
    it.assign(n, 0);
  }

  // add directed edge u -> v with capacity cap
  // returns index of the edge in g[u] (so caller can rember it)
  int add_edge(int u, int v, long long cap) {
    int idx_u = (int)g[u].size();
    int idx_v = (int)g[v].size();
    g[u].emplace_back(v, cap, idx_v);
    g[v].emplace_back(u, 0, idx_u);
    
    return idx_u; // index of forward edge in g[u]
  }

  bool bfs(int s, int t) {
    fill(level.begin(), level.end(), -1);
    queue<int> q;
    level[s] = 0;
    q.push(s);

    while(!q.empty()) {
      int u = q.front(); q.pop();
      for(auto &e : g[u]) {
        if(e.cap > 0 && level[e.to] == -1) {
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
      if(e.cap > 0 && level[e.to] == level[u] + 1) {
        long long pushed = dfs(e.to, t, min(f, e.cap));
        if(pushed > 0) {
          e.cap -= pushed;
          g[e.to][e.rev].cap += pushed;
          return pushed;
        }
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

  int n, m, k;
  cin >> n >> m >> k;

  int S = 0;
  int offsetB = 1;        // boys: 1..n
  int offsetG = 1 + n;    // girls: n+1 .. n+m 
  int T = 1 + n + m;
  int N = T + 1;

  Dinic dinic(N);

  // edgesToCheck will store(boyNode, edgeIndexInG[boy]) for each boy -> girl added 
  // so we can test later if that forward edge was used.
  vector<tuple<int, int, int>> edges_list; // store (boyNode, girlNode, edgeIndex
  
  // connect source -> boys 
  for(int b = 0; b < n; ++b) {
    dinic.add_edge(S, offsetB + b, 1);
  }

  // read possible pairs and add boy -> girl edges (cap 1)
  for(int i = 0; i < k; ++i) {
    int a, b; // a = boy (1..n), b = girl (1..m)   
    cin >> a >> b;
    --a; --b;
    int boyNode = offsetB + a;
    int girlNode = offsetG + b;
    int idx = dinic.add_edge(boyNode, girlNode, 1);
    // record to inspect later: boyNode, idx, girlNode 
    edges_list.emplace_back(boyNode, idx, girlNode);
  }

  // connect girls -> sink 
  for(int g = 0; g < m; ++g) {
    dinic.add_edge(offsetG + g, T, 1);
  }

  // compute max flow
  long long flow = dinic.max_flow(S, T);

  // extract matching by checking for each recorded forward edge whether its cap is 0
  // (meaning it carried flow 1). The forward edge is g[boyNode][idx].
  
  vector<pair<int, int>> matching;
  for(auto &tup : edges_list) {
    int boyNode, idx, girlNode;
    tie(boyNode, idx, girlNode) = tup;

    Edge &e = dinic.g[boyNode][idx];
    
    if(e.cap == 0) { // forward edge was saturated -> matched
      int boyId = boyNode - offsetB + 1;
      int girlId = girlNode - offsetG + 1;
      matching.emplace_back(boyId, girlId);
    }
  }

  // output
  cout << matching.size() << "\n";
  for(auto &p : matching) 
    cout << p.first << " " << p.second << "\n";

  return 0;
}
