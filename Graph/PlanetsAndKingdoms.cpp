#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph, reversedGraph;
stack<int> finishOrder;
vector<bool> visited;

void dfsOriginal(int u) {
    visited[u] = true;
    for (int v : graph[u]) {
        if (!visited[v])
            dfsOriginal(v);
    }
    finishOrder.push(u);
}

void dfsReversed(int u, vector<int>& component) {
    visited[u] = true;
    component.push_back(u);
    for (int v : reversedGraph[u]) {
        if (!visited[v])
            dfsReversed(v, component);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    graph.resize(n + 1);
    reversedGraph.resize(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        reversedGraph[v].push_back(u);
    }

    visited.assign(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (!visited[i])
            dfsOriginal(i);
    }

    visited.assign(n + 1, false);
    vector<int> kingdom(n + 1, 0);
    int currentLabel = 1;

    while (!finishOrder.empty()) {
        int u = finishOrder.top();
        finishOrder.pop();

        if (!visited[u]) {
            vector<int> component;
            dfsReversed(u, component);
            for (int node : component) {
                kingdom[node] = currentLabel;
            }
            currentLabel++;
        }
    }

    cout << currentLabel - 1 << '\n';
    for (int i = 1; i <= n; ++i) {
        cout << kingdom[i] << ' ';
    }
    cout << '\n';

    return 0;
}
