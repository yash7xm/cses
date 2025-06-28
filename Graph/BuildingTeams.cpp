#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

int n, m;
vector<vector<int>> graph;
vector<int> team;

bool bfs(int start) {
    queue<int> q;
    q.push(start);
    team[start] = 1; // Team 1

    while (!q.empty()) {
        int node = q.front(); q.pop();

        for (int neighbor : graph[node]) {
            if (team[neighbor] == -1) {
                team[neighbor] = 3 - team[node]; // Switch between 1 and 2
                q.push(neighbor);
            } else if (team[neighbor] == team[node]) {
                return false; // Conflict → same team for adjacent nodes
            }
        }
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    graph.resize(n + 1);
    team.assign(n + 1, -1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i) {
        if (team[i] == -1) {
            if (!bfs(i)) {
                cout << "IMPOSSIBLE" << endl;
                return 0;
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << team[i] << " ";
    }
    cout << endl;

    return 0;
}
