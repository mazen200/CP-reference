const int N = 1e5 + 5, LG = 23;
vector<int> graph[N];
int up[LG][N];
int deep[N]{};
void dfs(int cur, int par = -1, int depth = 0)
{
    deep[cur] = depth;
    for(auto &ch : graph[cur])
    {
        if(ch == par)
            continue;
        up[0][ch] = cur;
        for(int lg = 1; lg < LG and ~up[lg - 1][ch]; lg++)
            up[lg][ch] = up[lg - 1][up[lg - 1][ch]];
        dfs(ch, cur, depth +1);
    }
}
int kthAnc(int u, int k)
{
    for(int lg = 0; lg < LG and ~u; lg++)
        if((k >> lg) & 1)
            u = up[lg][u];
    return u;
}
int getLca(int u, int v)
{
    if(deep[v] > deep[u])
        swap(v, u);
    u = kthAnc(u, deep[u] - deep[v]);
    if(u == v)
        return u;
    for(int lg = LG - 1; lg >= 0; --lg)
        if(up[lg][u] != up[lg][v])
            u = up[lg][u], v = up[lg][v];
    return up[0][u];
}