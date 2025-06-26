#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

const vector<char> DIRECTIONS = {'U', 'R', 'D', 'L'};
const vector<int> dRow = {-1, 0, 1, 0}; // U, R, D, L
const vector<int> dCol = {0, 1, 0, -1}; // U, R, D, L

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<string> grid(n);
    for (int i = 0; i < n; ++i)
        cin >> grid[i];

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<vector<char>> previousDirection(n, vector<char>(m, 0));

    pii start, end;
    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < m; ++col) {
            if (grid[row][col] == 'A')
                start = {row, col};
            else if (grid[row][col] == 'B')
                end = {row, col};
        }
    }

    queue<pii> q;
    visited[start.first][start.second] = true;
    q.push(start);

    bool found = false;

    while (!q.empty() && !found) {
        auto [row, col] = q.front(); q.pop();

        for (int d = 0; d < 4; ++d) {
            int newRow = row + dRow[d];
            int newCol = col + dCol[d];

            if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < m &&
                !visited[newRow][newCol] && grid[newRow][newCol] != '#') {

                visited[newRow][newCol] = true;
                previousDirection[newRow][newCol] = DIRECTIONS[d];
                q.push({newRow, newCol});

                if (make_pair(newRow, newCol) == end) {
                    found = true;
                    break;
                }
            }
        }
    }

    if (!visited[end.first][end.second]) {
        cout << "NO\n";
        return 0;
    }

    // Reconstruct the path
    string path;
    pii current = end;

    while (current != start) {
        char dir = previousDirection[current.first][current.second];
        path.push_back(dir);

        int index = find(DIRECTIONS.begin(), DIRECTIONS.end(), dir) - DIRECTIONS.begin();
        current.first -= dRow[index];
        current.second -= dCol[index];
    }

    reverse(path.begin(), path.end());

    cout << "YES\n";
    cout << path.size() << '\n';
    cout << path << '\n';

    return 0;
}
