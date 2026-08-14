int main()
{
    int n, m;
    cin >> n >> m;
    vector<edge> edges;
    for (int i = 0, u, v, w; i < m; i++)
        cin >> u >> v >> w, edges.emplace_back(edge(u, v, w, i));
    dsu.init(n);
    int mst = kruskal(edges); // also fills the graph with the mst
    up[1][0] = 1;
    mx[1][0] = INT_MIN;
    dfs(1, 1);
    int lca, val, u, v;
    int secondMst = INT_MAX;
    for (auto &edge : edges) // try all edges
    {
        if (usedInMst[edge.id])
            continue;
        u = edge.u, v = edge.v;
        lca = LCA(u, v);
        val = mst - max(getMax(edge.u, lca), getMax(edge.v, lca)) +
              edge.w;
        if (val > mst)
            secondMst = min(secondMst, val);
    }
    cout << secondMst;
}