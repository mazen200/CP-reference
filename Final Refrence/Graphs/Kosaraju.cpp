int kosaraju(vector<vector<int>> &graph, vector<vector<int>> &revGraph)
{
    stack<int> st;
    int n = graph.size() - 1;
    vector<int> visited(n + 1, 0);
    function<void(int)> dfs1 = [&](int cur)
    {
        if (visited[cur])
            return;
        visited[cur] = 1;
        for (auto &ch : graph[cur])
            dfs1(ch);
        st.push(cur);
    };
    function<void(int)> dfs2 = [&](int cur)
    {
        if (!visited[cur])
            return;
        visited[cur] = 0;
        for (auto &ch : revGraph[cur])
            dfs2(ch);
    };
    for (int i = 1; i <= n; i++)
        if (!visited[i])
            dfs1(i);
    int sccCount = 0;
    while (st.size())
    {
        int cur = st.top();
        st.pop();
        if (visited[cur])
        {
            dfs2(cur);
            sccCount++;
        }
    }
    return (sccCount == 1);
};