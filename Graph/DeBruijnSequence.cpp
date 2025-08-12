#include <bits/stdc++.h>
using namespace std;

// Generate a De Bruijn sequence for alphabet size k and substring length n.
// alphabet supports up to 36 symbols: '0'..'9' then 'A'..'Z'.
string de_bruijn(int k, int n) {
    const string alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (k <= 0 || n <= 0) return "";
    if (k > (int)alphabet.size()) {
        cerr << "k too large. Max supported is " << alphabet.size() << "\n";
        return "";
    }

    // Special case n == 1: sequence is simply all alphabet symbols once.
    if (n == 1) {
        string s;
        for (int d = 0; d < k; ++d) s.push_back(alphabet[d]);
        return s;
    }

    // number of nodes = k^(n-1)
    long long numNodes = 1;
    for (int i = 0; i < n - 1; ++i) numNodes *= k;

    // 'nextEdge[v]' is how many outgoing edges from v we've already used (range 0..k)
    vector<int> nextEdge(numNodes, 0);

    // we'll simulate a stack of pairs (node, digitUsedToEnterThisNode)
    // for the starting node we use digit = -1 (no incoming digit)
    vector<pair<int,int>> stack;
    stack.reserve(numNodes * k + 5);
    stack.push_back({0, -1});

    // circuitDigits collects the digits (edge labels) in reverse order as we backtrack
    vector<int> circuitDigits;
    circuitDigits.reserve((size_t)pow(k, n)); // optional reserve

    while (!stack.empty()) {
        int v = stack.back().first;
        if (nextEdge[v] < k) {
            // take one unused outgoing edge labeled 'd'
            int d = nextEdge[v]++;
            long long u = ( (long long)v * k + d ) % numNodes; // next node
            stack.push_back({(int)u, d});
        } else {
            // no more outgoing edges unused from v, backtrack
            auto p = stack.back();
            stack.pop_back();
            if (p.second != -1) {
                // record the digit that was used to enter this node
                circuitDigits.push_back(p.second);
            }
        }
    }

    // circuitDigits are in reverse, so reverse them
    reverse(circuitDigits.begin(), circuitDigits.end());

    // build final string: starting node (n-1 copies of the first alphabet symbol)
    // plus all k^n digits we recorded.
    string result;
    result.reserve(circuitDigits.size() + (n - 1));
    for (int i = 0; i < n - 1; ++i) result.push_back(alphabet[0]);
    for (int d : circuitDigits) result.push_back(alphabet[d]);

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    cin >> n;
    k = 2;

    string s = de_bruijn(k, n);
    cout << s << "\n";
    return 0;
}
