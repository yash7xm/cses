#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

int n, m;
vector<vector<int>> graph;
vector<int> parent;
vector<bool> visited;
int cycle_start = -1, cycle_end;

bool dfs(int node, int par) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (neighbor == par) continue;  // don't go back via the same edge
        if (visited[neighbor]) {
            cycle_start = neighbor;
            cycle_end = node;
            return true;
        } else {
            parent[neighbor] = node;
            if (dfs(neighbor, node)) return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    graph.resize(n + 1);
    parent.assign(n + 1, -1);
    visited.assign(n + 1, false);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i) {
        if (!visited[i] && dfs(i, -1)) break;
    }

    if (cycle_start == -1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        vector<int> cycle;
        cycle.push_back(cycle_start);
        int curr = cycle_end;
        while (curr != cycle_start) {
            cycle.push_back(curr);
            curr = parent[curr];
        }
        cycle.push_back(cycle_start);  // close the cycle

        reverse(cycle.begin(), cycle.end());  // to print in correct order

        cout << cycle.size() << endl;
        for (int node : cycle) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}
