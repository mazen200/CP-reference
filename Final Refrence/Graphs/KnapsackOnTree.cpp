vector <int> adj[N];
ll dp[N][N], val[N], sub[N];
int n;
void dfs(int node, int p)
{
    sub[node] = 1;
    vector <ll> curDP(n+5, -1e18), prvDP(n+5, -1e18);
    prvDP[0] = 0;
    prvDP[1] = val[node];
    for (auto &child : adj[node]) {
        if (child == p)
            continue;
        dfs(child, node);

        for (int sz1 = 1; sz1 <= sub[node]; sz1++)
            for (int sz2 = 0; sz2 <= sub[child]; sz2++)
                curDP[sz1+sz2] = max(curDP[sz1+sz2], prvDP[sz1] + dp[child][sz2]);
        curDP[0] = 0;
        sub[node] += sub[child];
        prvDP = curDP;
    }

    for (int i = 0; i <= sub[node]; i++)
        dp[node][i] = prvDP[i];
}