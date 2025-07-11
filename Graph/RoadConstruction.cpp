#include <bits/stdc++.h>
using namespace std;

vector<int> parent, ranks, len;
int comp_count, max_size;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void merge(int x, int y) {
    int lx = find(x);
    int ly = find(y);

    if (lx != ly) {
        if (ranks[lx] > ranks[ly]) {
            parent[ly] = lx;
            len[lx] += len[ly];
        } else if (ranks[lx] < ranks[ly]) {
            parent[lx] = ly;
            len[ly] += len[lx];
        } else {
            parent[lx] = ly;
            ranks[ly]++;
            len[ly] += len[lx];
        }
        comp_count--;
        max_size = max(max_size, max(len[lx], len[ly]));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    parent.resize(n + 1);
    ranks.resize(n + 1, 0);
    len.resize(n + 1, 1);

    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
    }

    comp_count = n;
    max_size = 1;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;

        merge(u, v);

        cout << comp_count << " " << max_size << '\n';
    }
}
