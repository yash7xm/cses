#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> graph;
vector<bool> visited;
vector<bool> recStack;
vector<int> parent;
int cycleStart = -1;
int cycleEnd = -1;

bool dfs(int u) {
    visited[u] = true;
    recStack[u] = true;

    for (int v : graph[u]) {
        if (!visited[v]) {
            parent[v] = u;
            if (dfs(v))
                return true;
        } else if (recStack[v]) {
            cycleEnd = u;
            cycleStart = v;
            return true;
        }
    }

    recStack[u] = false;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    graph.resize(n + 1);
    visited.resize(n + 1, false);
    recStack.resize(n + 1, false);
    parent.resize(n + 1, -1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    for (int u = 1; u <= n; ++u) {
        if (!visited[u] && dfs(u))
            break;
    }

    if (cycleStart == -1) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    vector<int> cycle;
    cycle.push_back(cycleStart);
    for (int v = cycleEnd; v != cycleStart; v = parent[v]) {
        cycle.push_back(v);
    }
    cycle.push_back(cycleStart);
    reverse(cycle.begin(), cycle.end());

    cout << cycle.size() << endl;
    for (int node : cycle) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}