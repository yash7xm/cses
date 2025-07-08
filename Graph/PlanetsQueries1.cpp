#include <bits/stdc++.h>
using namespace std;

const int LOG = 30; // Enough for k up to 1e9 (2^30 > 1e9)
vector<vector<int>> up; // up[i][j] = planet after 2^i jumps from j

void build(const vector<int>& parents) {
    int n = parents.size();
    up.assign(LOG, vector<int>(n));
    
    // Base case: 2^0 = 1 jump
    for (int j = 0; j < n; j++) {
        up[0][j] = parents[j];
    }
    
    // Fill the binary lifting table
    for (int i = 1; i < LOG; i++) {
        for (int j = 0; j < n; j++) {
            up[i][j] = up[i-1][up[i-1][j]];
        }
    }
}

int query(int start, int jumps) {
    int current = start;
    for (int i = 0; i < LOG; i++) {
        if (jumps & (1 << i)) { // If the i-th bit is set
            current = up[i][current];
        }
    }
    return current;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    
    vector<int> parents(n);
    for (int i = 0; i < n; i++) {
        cin >> parents[i];
        parents[i]--; // Convert to 0-based
    }
    
    build(parents);
    
    while (q--) {
        int a, k;
        cin >> a >> k;
        a--; // Convert to 0-based
        cout << query(a, k) + 1 << '\n'; // Convert back to 1-based for output
    }
    
    return 0;
}