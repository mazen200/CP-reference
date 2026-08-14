struct DSU
{
    vector<int> par, sz;
    stack<pair<int &, int>> rollbacks;
    DSU(int n)
    {
        par = sz = vector<int>(n + 1, 1);
        iota(all(par), 0);
    }
    int getPar(int u)
    {
        if (par[u] == u)
            return u;
        return getPar(par[u]); // No path compression due to rollbacks
    }
    void merge(int u, int v)
    {
        u = getPar(u);
        v = getPar(v);
        rollbacks.push({par[u], par[u]});
        rollbacks.push({par[v], par[v]});
        rollbacks.push({sz[u], sz[u]});
        rollbacks.push({sz[v], sz[v]});
        if (u == v)
            return;
        if (sz[v] > sz[u])
            swap(v, u);
        sz[u] += sz[v];
        par[v] = u;
    }
    void rollback()
    {
        assert(rollbacks.size() >= 4);
        for (int i = 0; i < 4; i++)
        {
            auto [variable, value] = rollbacks.top();
            variable = value;
            rollbacks.pop();
        }
    }
    int get(int u, int v)
    {
        return getPar(u) == getPar(v);
    }
};