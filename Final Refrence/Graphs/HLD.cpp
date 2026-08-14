struct HLD
{
    int n, timer;
    vector<int> flat, sz, tp, dep, par;
    vector<vector<int>> graph;
    FenwickTree bit;
    HLD(vector<vector<int>> &graph) : graph(graph), n(graph.size() - 1)
    {
        timer = 0;
        sz = flat = tp = dep = par = vector<int>(n + 1, 0);
        preDfs(1);
        dfs(1);
        bit.resize(n + 1);
        for(int i = 1; i <= n;i++)
            update(i, 1);
    }
    void preDfs(int cur)
    {
        sz[cur] = 1;
        for (auto &ch : graph[cur])
        {
            graph[ch].erase(find(all(graph[ch]), cur));
            dep[ch] = dep[cur] + 1;
            par[ch] = cur;
            preDfs(ch);
            sz[cur] += sz[ch];
        }
        auto __cmp = [&](int u, int v) { return (sz[u] < sz[v]); };
        int heavy = max_element(all(graph[cur]), __cmp) - graph[cur].begin();
        if (graph[cur].size())
        {
            swap(graph[cur][0], graph[cur][heavy]);
        }
    }
    void dfs(int cur, int top = 1)
    {
        flat[cur] = ++timer, tp[cur] = top;
        for (int i = 0; i < graph[cur].size(); i++)
        {
            auto &ch = graph[cur][i];
            dfs(ch, !i ? top : ch);
        }
    }
    void update(int cur, int val)
    {
        bit.update(flat[cur], val);
    }
    int query(int u, int v)
    {
        int ret = 0;
        for (; tp[u] != tp[v]; u = par[tp[u]])
        {
            if (dep[tp[u]] < dep[tp[v]])
                swap(u, v);
            ret += bit.get(flat[tp[u]], flat[u]);
        }
        if (dep[u] < dep[v])
            swap(u, v);
        ret += bit.get(flat[v], flat[u]);
        return ret;
    }
};