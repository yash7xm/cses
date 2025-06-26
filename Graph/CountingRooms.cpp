#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

int n, m;
vector<vector<char>> grid;
vector<vector<bool>> visited;

const vector<pair<int, int>> directions = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

void dfs(int x, int y) {
    visited[x][y] = true;

    for (auto [dx, dy] : directions) {
        int nextX = x + dx;
        int nextY = y + dy;

        // Check if the next cell is within bounds, is a floor ('.'), and not visited
        if (nextX >= 0 && nextX < n && nextY >= 0 && nextY < m &&
            grid[nextX][nextY] == '.' && !visited[nextX][nextY]) {
            dfs(nextX, nextY);
        }
    }
}

void bfs(int startX, int startY) {
    queue<pair<int, int>> q;
    q.push({startX, startY});
    visited[startX][startY] = true;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (auto [dx, dy] : directions) {
            int nextX = x + dx;
            int nextY = y + dy;

            // Check bounds and if it's a walkable and unvisited tile
            if (nextX >= 0 && nextX < n && nextY >= 0 && nextY < m &&
                grid[nextX][nextY] == '.' && !visited[nextX][nextY]) {
                visited[nextX][nextY] = true;
                q.push({nextX, nextY});
            }
        }
    }
}

void solve() {
    cin >> n >> m;

    grid.resize(n, vector<char>(m));
    visited.assign(n, vector<bool>(m, false));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> grid[i][j];

    int rooms = 0;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (grid[i][j] == '.' && !visited[i][j]) {
                bfs(i, j);
                rooms++;
            }

    cout << rooms << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
