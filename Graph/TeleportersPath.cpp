#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> adj(n + 1);
  vector<int> indeg(n + 1), outdeg(n + 1);

  for(int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    outdeg[a]++;
    indeg[b]++;
  }

  if (outdeg[1] - indeg[1] != 1 || indeg[n] - outdeg[n] != 1) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }

  for(int i = 2; i < n; ++i) {
    if(indeg[i] != outdeg[i]) {
      cout << "IMPOSSIBLE\n";
      return 0;
    }
  }

  vector<int> path;
  stack<int> st;
  st.push(1);

  while(!st.empty()) {
    int v = st.top();
    if(!adj[v].empty()) {
      int u = adj[v].back();
      adj[v].pop_back();
      st.push(u);
    } else {
      path.push_back(v);
      st.pop();
    }
  }

  reverse(path.begin(), path.end());

  if((int)path.size() != m + 1 || path.front() != 1 || path.back() != n) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }

  for(int v : path) cout << v << " ";
  cout << "\n";
}
