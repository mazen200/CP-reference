
struct Edge {
    int u, v;
    long long w;
};

void solve() {
    int n , m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) 
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    // source 0 linked with each nodes
    vector<ll> dist(n + 1, 0);

    for (int i = 1; i < n; ++i) {
        bool changed = false;
        for (const auto& e : edges) {
            if (dist[e.v] > dist[e.u] + e.w) {
                dist[e.v] = dist[e.u] + e.w;
                changed = true;
            }
        }
        if (!changed) 
            break;
    }

    for (Edge e : edges) 
        if (dist[e.v] > dist[e.u] + e.w) 
            return void(cout << "-inf\n");
        
    ll min_dist = 1e18;
    for (int i = 1; i <= n; ++i) 
        min_dist = min(min_dist, dist[i]);

    cout << min_dist << endl;
}