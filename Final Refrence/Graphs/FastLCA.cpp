vector<int> g[N];
vector<pair<int, int>> queries[N]; // queries[u] contains {v, idx}
int ancestor[N], lca_answer[N];
bool visited[N];

void dfs(int u, int p, DSU &dsu) {
    ancestor[u] = u;
    visited[u] = true;

    for (int v : g[u]) {
        if (v == p) continue;
        dfs(v, u, dsu);
        dsu.merge(u, v);
        ancestor[dsu.getPar(u)] = u;
    }

    for (auto [v, idx] : queries[u]) {
        if (visited[v]) {
            lca_answer[idx] = ancestor[dsu.getPar(v)];
        }
    }
}