#include <bits/stdc++.h>
using namespace std;

#define endl "\n"

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<int>> graph;
    vector<bool> visited;
    vector<int> parent;

    int n, m;
    cin >> n >> m;

    graph.resize(n+1);
    visited.assign(n+1, false);
    parent.assign(n+1, -1);

    for(int i=0; i<m; i++) {
    	int u, v;
    	cin >> u >> v;

    	graph[u].push_back(v);
    	graph[v].push_back(u);
    }

    queue<int> q;
    q.push(1);

    visited[1] = true;

    bool found = false;

    while(!q.empty() && !found) {
    	int u = q.front(); 
    	q.pop();

    	for(int v : graph[u]) {
    		if(!visited[v]) {
    			visited[v] = true;	
    			parent[v] = u;
    			q.push(v);

    			if(v == n) {
    				found = true;
    				break;
    			}
    		}
    	}
    }

    if(!found) {
    	cout << "IMPOSSIBLE" << endl;
    	return 0;
    }

    vector<int> path;
    int curr = n;
    while(curr != -1) {
    	path.push_back(curr);
    	curr = parent[curr];
    }

    reverse(path.begin(), path.end());

    cout << path.size() << endl;
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}