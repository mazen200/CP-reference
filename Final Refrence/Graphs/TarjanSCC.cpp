int tarjan(vector<vector<int>> &graph)
{
    int n = graph.size() - 1;
    vector<int> low(n + 1, -1), inStack(n + 1, 0), dfsn(n + 1, -1), comp(n + 1, -1);
    vector<vector<int>> comps;
    stack<int> st;
    int timer = 0;
    function<void(int)> dfs = [&](int cur) {
        low[cur] = dfsn[cur] = timer++;
        inStack[cur] = 1;
        st.push(cur);
        for (auto &ch : graph[cur])
        {
            if (dfsn[ch] == -1)
            {
                dfs(ch);
                low[cur] = min(low[cur], low[ch]);
            }
            else if (inStack[ch])
            {
                low[cur] = min(low[cur], dfsn[ch]);
            }
        }
        if (low[cur] == dfsn[cur])
        {
            comps.emplace_back(); // Add New Comp
            int node = -1;
            while (node != cur)
            {
                node = st.top();
                st.pop();
                inStack[node] = 0;
                comps.back().push_back(node);
                comp[node] = comps.back().size() - 1;
            }
        }
        
    };
    for (int i = 1; i <= n; i++)
        if (dfsn[i] == -1)
            dfs(i);
    return (comps.size() == 1);
}