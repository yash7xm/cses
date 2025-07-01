#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, q;
	cin >> n >> m >> q;

	vector<vector<long long>> dist(n, vector<long long>(n, LLONG_MAX));

	for (int i = 0; i < n; i++) {
    	dist[i][i] = 0;  // Distance from a node to itself is zero
    }
 
    for (int i = 0; i < m; i++) {
        int u, v;
        long long wt;
        cin >> u >> v >> wt;
        u--; v--;  // Adjusting for 0-based indexing
        dist[u][v] = min(dist[u][v], wt);
        dist[v][u] = min(dist[v][u], wt);  // If the graph is bidirectional
    }
 
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != LLONG_MAX && dist[k][j] != LLONG_MAX) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
 
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;  // Adjusting for 0-based indexing
        cout << (dist[x][y] == LLONG_MAX ? -1 : dist[x][y]) << endl;
    }

	return 0;
}