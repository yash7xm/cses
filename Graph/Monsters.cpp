#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

using pii = pair<int, int>;

const vector<char> DIR = {'U', 'D', 'R', 'L'};
const vector<int> DX = {-1, 1, 0, 0};  // U D R L
const vector<int> DY = {0, 0, 1, -1};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    for (int i = 0; i < n; i++)
        cin >> grid[i];

    vector<vector<int>> monster_time(n, vector<int>(m, INT_MAX));
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<vector<char>> parent(n, vector<char>(m));

    queue<pii> q;

    // Step 1: Multi-source BFS for all Monsters
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'M') {
                q.push({i, j});
                monster_time[i][j] = 0;
            }
        }
    }

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();

        for (int d = 0; d < 4; d++) {
            int nx = x + DX[d];
            int ny = y + DY[d];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                grid[nx][ny] != '#' &&
                monster_time[nx][ny] > monster_time[x][y] + 1) {

                monster_time[nx][ny] = monster_time[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    // Step 2: BFS from 'A' while avoiding monster reach
    pii start, exit_point = {-1, -1};

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j] == 'A')
                start = {i, j};

    q.push(start);
    visited[start.first][start.second] = true;
    vector<vector<int>> dist(n, vector<int>(m, 0));

    bool escaped = false;

    while (!q.empty() && !escaped) {
        auto [x, y] = q.front(); q.pop();

        // Check if on boundary
        if (x == 0 || x == n - 1 || y == 0 || y == m - 1) {
            exit_point = {x, y};
            escaped = true;
            break;
        }

        for (int d = 0; d < 4; d++) {
            int nx = x + DX[d];
            int ny = y + DY[d];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                grid[nx][ny] != '#' && !visited[nx][ny] &&
                dist[x][y] + 1 < monster_time[nx][ny]) {

                visited[nx][ny] = true;
                dist[nx][ny] = dist[x][y] + 1;
                parent[nx][ny] = DIR[d];
                q.push({nx, ny});
            }
        }
    }

    if (!escaped) {
        cout << "NO" << endl;
        return 0;
    }

    // Step 3: Reconstruct path
    string path;
    pii curr = exit_point;

    while (curr != start) {
        char dir = parent[curr.first][curr.second];
        path.push_back(dir);

        int idx = find(DIR.begin(), DIR.end(), dir) - DIR.begin();
        curr.first -= DX[idx];
        curr.second -= DY[idx];
    }

    reverse(path.begin(), path.end());

    cout << "YES" << endl;
    cout << path.size() << endl;
    cout << path << endl;

    return 0;
}
