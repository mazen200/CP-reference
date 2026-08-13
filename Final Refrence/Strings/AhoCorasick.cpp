#include <bits/stdc++.h>
using namespace std;

struct AhoCorasick
{
    static const int K = 26;

    struct Node
    {
        int nxt[K];
        int fail;

        // Pattern IDs ending at this node
        vector<int> ids;

        // Number of times this state is visited
        long long cnt = 0;

        // Used in forbidden-pattern problems
        bool bad = false;

        Node()
        {
            memset(nxt, -1, sizeof(nxt));
            fail = 0;
        }
    };

    vector<Node> trie;

    AhoCorasick()
    {
        trie.emplace_back(); // root
    }

    // Add pattern with ID
    void addString(const string &s, int id)
    {
        int v = 0;

        for (char ch : s)
        {
            int c = ch - 'a';

            if (trie[v].nxt[c] == -1)
            {
                trie[v].nxt[c] = trie.size();
                trie.emplace_back();
            }

            v = trie[v].nxt[c];
        }

        trie[v].ids.push_back(id);
        trie[v].bad = true; // if this is a forbidden pattern
    }

    void build()
    {
        queue<int> q;

        // Root
        for (int c = 0; c < K; c++)
        {
            int u = trie[0].nxt[c];

            if (u == -1)
            {
                trie[0].nxt[c] = 0;
            }
            else
            {
                trie[u].fail = 0;
                q.push(u);
            }
        }

        while (!q.empty())
        {
            int v = q.front();
            q.pop();

            // If failure state is bad,
            // current state is also bad.
            if (trie[trie[v].fail].bad)
            {
                trie[v].bad = true;
            }

            for (int c = 0; c < K; c++)
            {

                int u = trie[v].nxt[c];

                if (u == -1)
                {
                    // Follow failure transition
                    trie[v].nxt[c] =
                        trie[trie[v].fail].nxt[c];
                }
                else
                {
                    // Calculate failure link
                    trie[u].fail =
                        trie[trie[v].fail].nxt[c];

                    q.push(u);
                }
            }
        }
    }

    vector<long long> countOccurrences(const string &text, int n)
    {

        // Visit states
        int v = 0;

        for (char ch : text)
        {
            int c = ch - 'a';

            v = trie[v].nxt[c];

            trie[v].cnt++;
        }

        /*
            Propagate counts through failure links.

            If:
                fail[v] = u

            then every occurrence represented by v
            is also an occurrence represented by u.
        */

        vector<int> order;
        order.reserve(trie.size());

        queue<int> q;
        q.push(0);

        while (!q.empty())
        {
            int v = q.front();
            q.pop();

            order.push_back(v);

            for (int c = 0; c < K; c++)
            {
                int u = trie[v].nxt[c];

                if (trie[u].fail == v && u != 0)
                {
                    q.push(u);
                }
            }
        }

        // Reverse BFS order = deeper nodes first
        reverse(order.begin(), order.end());

        for (int v : order)
        {
            if (v == 0)
                continue;

            trie[trie[v].fail].cnt += trie[v].cnt;
        }

        // Answer for each pattern
        vector<long long> ans(n);

        for (int v = 0; v < (int)trie.size(); v++)
        {
            for (int id : trie[v].ids)
            {
                ans[id] = trie[v].cnt;
            }
        }

        return ans;
    }

    ll solve(int L)
    {

        int states = trie.size();

        /*
            dp[state]

            Number of valid strings of current
            length ending in 'state'.
        */

        vector<ll> dp(states);
        vector<ll> ndp(states);

        dp[0] = 1;

        for (int len = 0; len < L; len++)
        {

            fill(ndp.begin(), ndp.end(), 0);

            for (int v = 0; v < states; v++)
            {

                if (dp[v] == 0)
                    continue;

                for (int c = 0; c < K; c++)
                {

                    int u = trie[v].nxt[c];

                    // This creates a forbidden pattern
                    if (trie[u].bad)
                        continue;

                    ndp[u] += dp[v];

                    if (ndp[u] >= MOD)
                        ndp[u] -= MOD;
                }
            }

            dp.swap(ndp);
        }

        ll ans = 0;

        for (int v = 0; v < states; v++)
        {
            ans += dp[v];

            if (ans >= MOD)
                ans -= MOD;
        }

        return ans;
    }
};
