#include <bits/stdc++.h>
using namespace std;
 
vector<vector<int>> adj, adjRev;
vector<int> component;
vector<bool> assignment, vis;
stack<int> st;
int n, m;
 
int negateVar(int x) {
    return x < n ? x + n : x - n;
}
 
void addClause(int x, int y) {
    adj[negateVar(x)].push_back(y);
    adj[negateVar(y)].push_back(x);
    adjRev[y].push_back(negateVar(x));
    adjRev[x].push_back(negateVar(y));
}
 
void dfs1(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            dfs1(v);
        }
    }
    st.push(u);
}
 
void dfs2(int u, int comp) {
    component[u] = comp;
    for (int v : adjRev[u]) {
        if (component[v] == -1) {
            dfs2(v, comp);
        }
    }
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    cin >> m >> n;
 
    adj.resize(2 * n);
    adjRev.resize(2 * n);
    for (int i = 0; i < m; i++) {
        string sign1, sign2;
        int x, y;
        cin >> sign1 >> x >> sign2 >> y;

        // Convert 1-based to 0-based
        x--, y--;

        if (sign1 == "-") x = negateVar(x);
        if (sign2 == "-") y = negateVar(y);

        addClause(x, y);
    }
 
    vis.resize(2 * n, false);
    for (int i = 0; i < 2 * n; i++) {
        if (!vis[i]) {
            dfs1(i);
        }
    }
 
    component.resize(2 * n, -1);
    int comp = 0;
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        if (component[u] == -1) {
            dfs2(u, comp++);
        }
    }
 
    assignment.resize(n);
    for (int i = 0; i < n; i++) {
        if (component[i] == component[negateVar(i)]) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
 
        assignment[i] = component[i] > component[negateVar(i)];
    }
 
 
    for (int i = 0; i < n; i++) {
        cout << (assignment[i] ? "+ " : "- ");
    }
    cout << endl;
 
    return 0;
}