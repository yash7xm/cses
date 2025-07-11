#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<vector<int>>& graph, vector<bool>& visited) {
    if (visited[node]) return;
    visited[node] = true;
    
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);
    vector<vector<int>> reversed_graph(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        reversed_graph[v].push_back(u);
    }

    vector<bool> visited(n + 1, false);
    dfs(1, graph, visited);

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            cout << "NO\n";
            cout << "1 " << i << "\n";
            return 0;
        }
    }

    fill(visited.begin(), visited.end(), false);
    dfs(1, reversed_graph, visited);

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            cout << "NO\n";
            cout << i << " 1\n";
            return 0;
        }
    }

    cout << "YES\n";
    return 0;
}