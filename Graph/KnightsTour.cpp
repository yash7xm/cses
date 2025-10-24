#include <bits/stdc++.h>
using namespace std;

const int N = 8;

// Knight moves
int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

bool isValid(int x, int y, vector<vector<int>>& board) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == 0);
}

int countMoves(int x, int y, vector<vector<int>>& board) {
    int cnt = 0;
    for(int i = 0; i < 8; ++i) {
        int nx = x + dx[i], ny = y + dy[i];
        if(isValid(nx, ny, board)) cnt++;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int startX, startY;
    cin >> startX >> startY;
    
    // Convert to 0-based indices, keeping the same coordinate system
    // The input uses chess coordinates where (1,1) is bottom-left
    // We'll map it so that (0,0) in our array is position (1,1) on chessboard
    startX--; startY--;
    
    // But wait - in chess, coordinates are usually given as (column, row)
    // Let's be explicit: the first input is x (column), second is y (row)
    int x = startY;  // row index (0-7)
    int y = startX;  // column index (0-7)

    vector<vector<int>> board(N, vector<int>(N, 0));

    for(int step = 1; step <= N * N; ++step) {
        board[x][y] = step;

        int bestNextX = -1, bestNextY = -1, minDeg = 9;

        for(int i = 0; i < 8; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if(!isValid(nx, ny, board)) continue;

            int deg = countMoves(nx, ny, board);
            if(deg < minDeg || (deg == minDeg && rand() % 2 == 0)) {
                minDeg = deg;
                bestNextX = nx;
                bestNextY = ny;
            }
        }

        if(bestNextX == -1) {
            // If no valid move found but we haven't completed the tour,
            // we need to handle this case
            if(step < N * N) {
                // This shouldn't happen with a good heuristic
                // Let's try to find any valid move
                for(int i = 0; i < 8; ++i) {
                    int nx = x + dx[i], ny = y + dy[i];
                    if(isValid(nx, ny, board)) {
                        bestNextX = nx;
                        bestNextY = ny;
                        break;
                    }
                }
            }
            if(bestNextX == -1) break;
        }
        
        x = bestNextX;
        y = bestNextY;
    }

    // Output the board
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cout << board[i][j];
            if(j < N - 1) cout << " ";
        }
        cout << "\n";
    }

    return 0;
}
