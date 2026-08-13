#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define int ll

struct AhoCorasick {
    static const int K = 26;

    struct Node {
        int nxt[K];
        int fail;

        // Pattern IDs ending at this node
        vector<int> ids;

        // Number of times this state is visited
        ll cnt = 0;

        ll match_cnt = 0;

        // Used in forbidden-pattern problems
        bool bad = false;

        Node() {
            memset(nxt, -1, sizeof(nxt));
            fail = 0;
        }
    };

    vector<Node> trie;

    AhoCorasick() {
        trie.emplace_back(); // root
    }

    // Add pattern with ID
    void addString(const string& s, int id) {
        int v = 0;

        for (char ch : s) {
            int c = ch - 'a';

            if (trie[v].nxt[c] == -1) {
                trie[v].nxt[c] = trie.size();
                trie.emplace_back();
            }

            v = trie[v].nxt[c];
    
        }

        trie[v].ids.push_back(id);
        trie[v].match_cnt++;
        trie[v].bad = true;// if this is a forbidden pattern
    }

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

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            // If failure state is bad,
            // current state is also bad.
            trie[v].match_cnt += trie[trie[v].fail].match_cnt;

            if (trie[trie[v].fail].bad) {
                trie[v].bad = true;
            }

            for (int c = 0; c < K; c++) {

                int u = trie[v].nxt[c];

                if (u == -1) {
                    // Follow failure transition
                    trie[v].nxt[c] =
                        trie[trie[v].fail].nxt[c];
                }
                else {
                    // Calculate failure link
                    trie[u].fail =
                        trie[trie[v].fail].nxt[c];

                    q.push(u);
                }
            }
        }
    }

};

void solve()
{
    string t;
    cin>>t;
    
    int n;
    cin>>n;

    AhoCorasick ac_forward;
    AhoCorasick ac_backward;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        
        ac_forward.addString(s,i);
        
        reverse(s.begin(), s.end());
        ac_backward.addString(s,i);
    }

    ac_forward.build();
    ac_backward.build();

    int len = t.length();
    vector<int> ends_at(len, 0);
    vector<int> starts_at(len, 0);

    int v = 0;
    for (int i = 0; i < len; i++) {
        v = ac_forward.trie[v].nxt[t[i] - 'a'];
        ends_at[i] = ac_forward.trie[v].match_cnt;
    }

    v = 0;
    for (int i = len - 1; i >= 0; i--) {
        v = ac_backward.trie[v].nxt[t[i] - 'a'];
        starts_at[i] = ac_backward.trie[v].match_cnt;
    }

    ll tot = 0;
    for (int i = 0; i < len - 1; i++) {
        tot += 1LL * ends_at[i] * starts_at[i + 1];
    }

    cout << tot << "\n";
   
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
  
    int t = 1;
   // cin >> t;
    while (t--)
    {
        solve();
    }
}