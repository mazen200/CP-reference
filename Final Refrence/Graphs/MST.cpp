DSU dsu(n);
vector<edge> edges;
for (int i = 0; i < m; i++)
{
    int c, u, v;
    cin >> u >> v >> c;
    edges.push_back({c, u, v});
}
sort(all(edges));
int sum = 0;
for (auto &[c, u, v] : edges)
{
    if (dsu.get(u, v))
        continue;
    sum += c;
    dsu.merge(u, v);
}