#include <bits/stdc++.h>
using namespace std;

string solve(string s, long long n) {
    vector<int> ones;
    for(int i=0; i<s.size(); ++i) {
        if(s[i] == '1') ones.push_back(i);
    }

    vector<char> result(s.size(), '0'); // Initialize with original string size

    int c = 0;
    for(int i = 0; i < ones.size() && n > 0; ++i) { // Need to iterate with index
        int pos = ones[i];
        int left = pos - c;
        int move = min((long long)left, n); // Need to cast left to long long for comparison
        n -= move;
        c++;
        int newPos = pos - move;
        ones[i] = newPos; // Update the position
    }

    // Place '1's in their new positions
    for(int pos : ones) {
        if(pos >= 0 && pos < result.size()) { // Check bounds
            result[pos] = '1';
        }
    }

    return string(result.begin(), result.end()); // Convert vector to string
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    long long n;

    cin >> s;
    cin >> n;

    cout << solve(s, n) << endl;
    
    return 0;
}