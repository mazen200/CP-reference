
const int N = 55;
vector<vector<int>> build_automaton(string &v)
{
    int m = v.size();
    vector<int> pi(m + 1);
    vector<vector<int>> nxt(26, vector<int>(N, 0));
    for (int i = 1; i < m; i++)
    {
        int j = pi[i - 1];
        while (j > 0 && v[i] != v[j])
            j = pi[j - 1];
        if (v[i] == v[j])
            j++;
        pi[i] = j;
    }
    for (int i = 0; i <= m; i++)
    {
        for (int c = 0; c < 26; c++)
        {
            if (v[i] == (char)('a' + c))
                nxt[c][i] = i + 1;
            else if (i > 0)
                nxt[c][i] = nxt[c][pi[i - 1]];
            else
                nxt[c][i] = 0;
        }
    }
    return nxt;
}

void solve()
{
    string c, s, t;
    cin >> c >> s >> t;
    int n = c.size();
    // mx s mn t
    vector<vector<int>> nxtS = build_automaton(s);
    vector<vector<int>> nxtT = build_automaton(t);
    int ssz = s.size();
    int tsz = t.size();
    vector<vector<vector<int>>> dp(1004, vector<vector<int>>(53, vector<int>(53, -1e9)));
    dp[0][0][0] = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= ssz; j++)
        {
            for (int k = 0; k <= tsz; k++)
            {
                if (dp[i][j][k] != -1e9)
                {
                    for (int ch = 0; ch < 26; ch++)
                    {
                        if (c[i] == '*' || (char)('a' + ch) == c[i])
                        {
                            int nxt1 = nxtS[ch][j];
                            int nxt2 = nxtT[ch][k];
                            dp[i + 1][nxt1][nxt2] = max(dp[i + 1][nxt1][nxt2], dp[i][j][k] + (nxt1 == ssz) - (nxt2 == tsz));
                        }
                    }
                }
            }
        }
    }
    int mx = -1e9;
    for (int j = 0; j < 51; j++)
    {
        for (int k = 0; k < 51; k++)
        {
            mx = max(mx, dp[n][j][k]);
        }
    }

    cout << mx << '\n';
}