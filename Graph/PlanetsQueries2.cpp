#include <bits/stdc++.h>
using namespace std;

const int MAX_HEIGHT = 20;
vector<vector<int>> binaryLifting;
vector<int> arr;
vector<int> len;
vector<bool> visited;

void dfs(int node) {
    if (visited[node]) return;
    visited[node] = true;

    dfs(arr[node]);

    binaryLifting[node][0] = arr[node];
    len[node] = len[binaryLifting[node][0]] + 1;

    for (int level = 1; level < MAX_HEIGHT; level++) {
        binaryLifting[node][level] = binaryLifting[binaryLifting[node][level - 1]][level - 1];
    }
}

int jump(int a, int dist) {
    if (dist < 0) return -1;
    for (int level = 0; dist > 0; level++, dist >>= 1) {
        if (dist & 1) {
            a = binaryLifting[a][level];
        }
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    arr.resize(n + 1);
    binaryLifting.assign(n + 1, vector<int>(MAX_HEIGHT));
    len.assign(n + 1, 0);
    visited.assign(n + 1, false);

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    // DEBUG: print binary lifting table
    cout << "\nBinary Lifting Table:\n";
    for (int i = 1; i <= n; i++) {
        cout << "Node " << i << ": ";
        for (int j = 0; j < MAX_HEIGHT; j++) {
            cout << binaryLifting[i][j] << " ";
        }
        cout << "\n";
    }

    // Queries (optional)
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        int cycle_entry_a = jump(a, len[a]);

        int answer;
        if (jump(a, len[a] - len[b]) == b) {
            answer = len[a] - len[b];
        } else if (jump(cycle_entry_a, len[cycle_entry_a] - len[b]) == b) {
            answer = (len[cycle_entry_a] - len[b]) + len[a];
        } else {
            answer = -1;
        }

        cout << answer << "\n";
    }

    return 0;
}
