#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> graph;
vector<int> deg;
vector<bool> seen;
vector<int> path;

void dfs(int node) {
    while(!graph[node].empty()) {
        auto edge = graph[node].back();
        graph[node].pop_back();
        if(seen[edge.second]) continue;
        seen[edge.second] = true;
        dfs(edge.first);
    }
    path.push_back(node);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    graph.resize(n+1);
    deg.resize(n+1, 0);

    for(int i=0; i<m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back({v, i});
        graph[v].push_back({u, i});
        deg[u]++;
        deg[v]++;
    }

    for(int i=1; i<=n; ++i) {
        if(deg[i] % 2 != 0) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    seen.resize(m, false);
    path.clear();

    dfs(1);

    if(path.size() != m + 1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        for(int i=path.size() - 1; i >= 0; --i) {
            cout << path[i] << " ";
        }
        cout << endl;
    }

    return 0;
}