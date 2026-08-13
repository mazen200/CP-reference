#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;

struct Matrix {

    int n;

    vector<vector<ll>> a;

    Matrix(int n, bool identity = false)
        : n(n),
          a(n, vector<ll>(n, 0)) {

        if (identity) {
            for (int i = 0; i < n; i++) {
                a[i][i] = 1;
            }
        }
    }

    Matrix operator*(const Matrix& other) const {

        Matrix res(n);

        for (int i = 0; i < n; i++) {

            for (int k = 0; k < n; k++) {

                if (a[i][k] == 0)
                    continue;

                for (int j = 0; j < n; j++) {

                    if (other.a[k][j] == 0)
                        continue;

                    res.a[i][j] +=
                        a[i][k] * other.a[k][j];

                    res.a[i][j] %= MOD;
                }
            }
        }

        return res;
    }
};


// ======================================================
// Matrix exponentiation
// ======================================================

Matrix power(Matrix base, long long exp) {

    Matrix res(base.n, true);

    while (exp > 0) {

        if (exp & 1) {
            res = res * base;
        }

        base = base * base;

        exp >>= 1;
    }

    return res;
}


// ======================================================
// Aho-Corasick
// ======================================================

struct AhoCorasick {

    static const int K = 26;

    struct Node {

        int nxt[K];

        int fail;

        // Is this state forbidden?
        bool bad;

        Node() {

            memset(nxt, -1, sizeof(nxt));

            fail = 0;
            bad = false;
        }
    };

    vector<Node> trie;

    AhoCorasick() {

        trie.emplace_back();
    }

    // --------------------------------------------------
    // Add forbidden pattern
    // --------------------------------------------------

    void addString(const string& s) {

        int v = 0;

        for (char ch : s) {

            int c = ch - 'a';

            if (trie[v].nxt[c] == -1) {

                trie[v].nxt[c] =
                    trie.size();

                trie.emplace_back();
            }

            v = trie[v].nxt[c];
        }

        trie[v].bad = true;
    }

    // --------------------------------------------------
    // Build automaton
    // --------------------------------------------------

    void build() {

        queue<int> q;

        // Root
        for (int c = 0; c < K; c++) {

            int u = trie[0].nxt[c];

            if (u == -1) {

                trie[0].nxt[c] = 0;

            } else {

                trie[u].fail = 0;

                q.push(u);
            }
        }

        // BFS
        while (!q.empty()) {

            int v = q.front();
            q.pop();

            // If failure state is bad,
            // this state is also bad.
            if (trie[trie[v].fail].bad) {

                trie[v].bad = true;
            }

            for (int c = 0; c < K; c++) {

                int u = trie[v].nxt[c];

                if (u == -1) {

                    trie[v].nxt[c] =
                        trie[trie[v].fail].nxt[c];

                } else {

                    trie[u].fail =
                        trie[trie[v].fail].nxt[c];

                    q.push(u);
                }
            }
        }
    }

    // --------------------------------------------------
    // Build transition matrix
    // --------------------------------------------------

    Matrix getMatrix() {

        int states = trie.size();

        Matrix M(states);

        for (int v = 0; v < states; v++) {

            // We never use bad states.
            if (trie[v].bad)
                continue;

            for (int c = 0; c < K; c++) {

                int u = trie[v].nxt[c];

                // Don't transition into a bad state.
                if (trie[u].bad)
                    continue;

                /*
                    v --character--> u

                    Therefore:
                        M[v][u]++

                    ++ is important because multiple
                    characters can lead to the same
                    pair of states.
                */

                M.a[v][u]++;

                if (M.a[v][u] >= MOD)
                    M.a[v][u] -= MOD;
            }
        }

        return M;
    }

    // --------------------------------------------------
    // Solve
    // --------------------------------------------------

    ll solve(long long L) {

        int states = trie.size();

        Matrix M = getMatrix();

        // M^L
        Matrix P = power(M, L);

        /*
            Initially:

                dp = [1, 0, 0, ...]

            Therefore after L characters:

                dp[j] = P[0][j]
        */

        ll ans = 0;

        for (int state = 0; state < states; state++) {

            // Bad states are not reachable anyway,
            // but skipping them makes the meaning clear.
            if (trie[state].bad)
                continue;

            ans += P.a[0][state];

            if (ans >= MOD)
                ans -= MOD;
        }

        return ans;
    }
};


int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;

    long long L;

    cin >> n >> L;

    AhoCorasick ac;

    for (int i = 0; i < n; i++) {

        string s;

        cin >> s;

        ac.addString(s);
    }

    ac.build();

    cout << ac.solve(L) << '\n';

    return 0;
}