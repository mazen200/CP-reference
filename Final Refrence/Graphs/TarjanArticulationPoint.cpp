int tarjan(vector<vector<int>> &graph)
{
    int n = graph.size() - 1;
    vector<int> dfsn(n + 1, -1);
    vector<int> low(n + 1, -1);
    vector<int> isArt(n + 1, 0);
    int timer = 0;
    function<void(int, int)> dfs = [&](int cur, int par) {
        low[cur] = dfsn[cur] = timer++;
        bool rootEdge = false;
        for (auto &ch : graph[cur])
        {
            if (dfsn[ch] == -1)
            {
                dfs(ch, cur);
                low[cur] = min(low[cur], low[ch]);
                if (low[ch] >= dfsn[cur])
                {
                    if(dfsn[cur] == 0 and !rootEdge)
                        rootEdge = true;
                    else
                        isArt[cur] = true;
                }
            }
            else if (ch != par)
            {
                low[cur] = min(low[cur], dfsn[ch]);
            }
        }
    };
    dfs(1, -1);
    vector<int> artPoints;
    for (int i = 1; i <= n; i++)
        if (isArt[i])
            artPoints.push_back(i);
    return artPoints.size();
}