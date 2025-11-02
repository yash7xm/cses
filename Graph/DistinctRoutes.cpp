#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev;
    int cap, flow;
};

struct Dinic {
    int n;
    vector<vector<Edge>> adj;
    vector<int> level, it;

    Dinic(int n) : n(n), adj(n), level(n), it(n) {}

    void add_edge(int u, int v, int cap) {
        Edge a = {v, (int)adj[v].size(), cap, 0};
        Edge b = {u, (int)adj[u].size(), 0, 0};
        adj[u].push_back(a);
        adj[v].push_back(b);
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : adj[u]) {
                if (e.cap - e.flow > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    int dfs(int u, int t, int f) {
        if (u == t) return f;
        for (int &i = it[u]; i < (int)adj[u].size(); i++) {
            Edge &e = adj[u][i];
            if (e.cap - e.flow > 0 && level[e.to] == level[u] + 1) {
                int pushed = dfs(e.to, t, min(f, e.cap - e.flow));
                if (pushed > 0) {
                    e.flow += pushed;
                    adj[e.to][e.rev].flow -= pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    int maxflow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (int pushed = dfs(s, t, 1e9))
                flow += pushed;
        }
        return flow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    Dinic dinic(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        dinic.add_edge(a, b, 1);
    }

    int maxPaths = dinic.maxflow(1, n);
    cout << maxPaths << "\n";

    // Extract paths using DFS on residual network
    vector<vector<int>> routes;
    
    for (int i = 0; i < maxPaths; i++) {
        vector<int> path;
        int cur = 1;
        path.push_back(cur);
        
        while (cur != n) {
            bool found = false;
            for (auto &e : dinic.adj[cur]) {
                // If there's flow in forward direction, use it
                if (e.flow > 0 && e.to >= 1 && e.to <= n) {
                    e.flow = 0; // Mark this edge as used
                    cur = e.to;
                    path.push_back(cur);
                    found = true;
                    break;
                }
            }
            if (!found) break; // Shouldn't happen if flow is valid
        }
        routes.push_back(path);
    }

    for (auto &path : routes) {
        cout << path.size() << "\n";
        for (int x : path) cout << x << " ";
        cout << "\n";
    }
    
    return 0;
}
