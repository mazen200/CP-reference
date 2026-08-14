int tarjan(vector<vector<int>> &graph)
{
    int n = graph.size() - 1;
    vector<int> dfsn(n + 1, -1), low(n + 1, -1);
    int ret = 0;
    int timer = 0;
    set<pii> bridges;
    function<void(int, int)> dfs = [&](int cur, int par) {
        dfsn[cur] = low[cur] = timer++;
        for (auto &ch : graph[cur])
        {
            if (dfsn[ch] == -1)
            {
                dfs(ch, cur);
                low[cur] = min(low[cur], low[ch]);
                if (low[ch] == dfsn[ch])
                    bridges.insert({cur, ch});
            }
            else if (ch != par)
                low[cur] = min(low[cur], dfsn[ch]);
        }
    };
    dfs(1, -1);
    vector<int> comp(n + 1, -1);
    vector<vector<int>> bridgesTree(n + 1);
    timer = 1;
    function<void(int)> calcComp = [&](int cur) {
        for (auto &ch : graph[cur])
            if (comp[ch] == -1 and !bridges.count({cur, ch}) and !bridges.count({ch, cur}))
                comp[ch] = comp[cur], calcComp(ch);
    };
    for (int i = 1; i <= n; i++)
        if (comp[i] == -1)
            comp[i] = timer++, calcComp(i);
    for (auto &[u, v] : bridges)
    {
        int cmpU = comp[u];
        int cmpV = comp[v];
        bridgesTree[cmpU].push_back(cmpV);
        bridgesTree[cmpV].push_back(cmpU);
    }
    int mx = -1, node = -1;
    function<void(int, int , int)> dfs2 = [&](int cur, int par, int depth)
    {
        if(depth > mx)
            node = cur, mx = depth;
        for(auto &ch : bridgesTree[cur])
            if(ch != par)
                dfs2(ch, cur, depth + 1);
    };
    dfs2(1, -1, 0);
    mx = -1;
    dfs2(node, -1, 0);
    return mx;
}