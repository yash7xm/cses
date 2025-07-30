#include <bits/stdc++.h>
using namespace std;

vector<int> value, component, topOrder;
vector<vector<int>> graph, graphRev, sccGraph;
vector<long long> sccValue;
vector<bool> visited;
stack<int> finishStack;

void dfsForward(int node) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfsForward(neighbor);
        }
    }
    finishStack.push(node);
}

void dfsReverse(int node, int compId, long long &sum) {
    component[node] = compId;
    sum += value[node];
    for (int neighbor : graphRev[node]) {
        if (component[neighbor] == -1) {
            dfsReverse(neighbor, compId, sum);
        }
    }
}

void buildCondensedGraph(int n, int numComponents) {
    sccGraph.assign(numComponents, vector<int>());
    for (int u = 1; u <= n; u++) {
        for (int v : graph[u]) {
            if (component[u] != component[v]) {
                sccGraph[component[u]].push_back(component[v]);
            }
        }
    }
}

void computeTopologicalSort(int numComponents) {
    vector<int> indegree(numComponents, 0);
    for (int u = 0; u < numComponents; u++) {
        for (int v : sccGraph[u]) {
            indegree[v]++;
        }
    }

    queue<int> q;
    for (int u = 0; u < numComponents; u++) {
        if (indegree[u] == 0) {
            q.push(u);
        }
    }

    while (!q.empty()) {
        int node = q.front(); q.pop();
        topOrder.push_back(node);
        for (int neighbor : sccGraph[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    value.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> value[i];
    }

    graph.assign(n + 1, vector<int>());
    graphRev.assign(n + 1, vector<int>());

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graphRev[v].push_back(u);
    }

    visited.assign(n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfsForward(i);
        }
    }

    component.assign(n + 1, -1);
    int numComponents = 0;
    sccValue.clear();

    while (!finishStack.empty()) {
        int node = finishStack.top();
        finishStack.pop();
        if (component[node] == -1) {
            long long sum = 0;
            dfsReverse(node, numComponents++, sum);
            sccValue.push_back(sum);
        }
    }

    buildCondensedGraph(n, numComponents);
    computeTopologicalSort(numComponents);

    vector<long long> dp(numComponents, 0);
    for (int u : topOrder) {
        dp[u] += sccValue[u];
        for (int v : sccGraph[u]) {
            dp[v] = max(dp[v], dp[u]);
        }
    }

    cout << *max_element(dp.begin(), dp.end()) << "\n";
    return 0;
}
