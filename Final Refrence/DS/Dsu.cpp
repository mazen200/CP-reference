struct DSU
{
    vector<int> par, sz;
    DSU(int n)
    {
        sz = par = vector<int>(n + 1, 1);
        iota(par.begin(), par.end(), 0);
    }
    void merge(int u, int v)
    {
        u = getPar(u);
        v = getPar(v);
        if (u == v)
            return;
        if (sz[v] > sz[u])
            swap(v, u);
        par[v] = u;
        sz[u] += sz[v];
    }
    int getPar(int u)
    {
        if (par[u] == u)
            return u;
        return par[u] = getPar(par[u]);
    }
    bool get(int u, int v)
    {
        return (getPar(u) == getPar(v));
    }
};