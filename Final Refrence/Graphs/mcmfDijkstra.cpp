// O(F * E log V)
struct MCMF
{
    struct Edge
    {
        int to;
        int cap, flow;
        int cost;
        int rev;
    };
 
    int n;
    vector<vector<Edge>> adj;
    vector<int> dist;
    vector<int> parent_edge, parent_node;
    vector<int> pot; // Potentials array for Dijkstra
 
    const int INF = numeric_limits<int>::max() / 2;
 
    MCMF(int n) : n(n), adj(n), pot(n, 0)
    {
    }
 
    void add_edge(int from, int to, int cap, int cost)
    {
        adj[from].push_back({to, cap, 0, cost, (int)adj[to].size()});
        // Reverse edge capacity is 0, cost is negated
        adj[to].push_back({from, 0, 0, -cost, (int)adj[from].size() - 1});
    }
 
    // Returns a pair of {max_flow, min_cost}
    pair<int, int> get_mcmf(int s, int t)
    {
        int max_flow = 0;
        int min_cost = 0;
        pot.assign(n, 0); // Initialize potentials to 0 (assumes initial costs >= 0)
 
        while (true)
        {
            dist.assign(n, INF);
            parent_node.assign(n, -1);
            parent_edge.assign(n, -1);
 
            // Priority queue for Dijkstra: {distance, node}
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
 
            dist[s] = 0;
            pq.push({0, s});
 
            while (!pq.empty())
            {
                auto [d, u] = pq.top();
                pq.pop();
 
                // Skip outdated distance pairs
                if (d > dist[u])
                    continue;
 
                for (int i = 0; i < adj[u].size(); i++)
                {
                    Edge &e = adj[u][i];
                    if (e.cap - e.flow > 0)
                    {
                        // Reduced cost calculation: cost(u,v) + pot[u] - pot[v]
                        int reduced_cost = e.cost + pot[u] - pot[e.to];
 
                        if (dist[e.to] > dist[u] + reduced_cost)
                        {
                            dist[e.to] = dist[u] + reduced_cost;
                            parent_node[e.to] = u;
                            parent_edge[e.to] = i;
                            pq.push({dist[e.to], e.to});
                        }
                    }
                }
            }
 
            // If we can't reach the sink, max flow is achieved
            if (dist[t] == INF)
                break;
 
            // Update potentials for the next iteration
            for (int i = 0; i < n; i++)
            {
                if (dist[i] != INF)
                {
                    pot[i] += dist[i];
                }
            }
 
            // Find the bottleneck capacity along the shortest path
            int push = INF;
            int curr = t;
            while (curr != s)
            {
                int p = parent_node[curr];
                int idx = parent_edge[curr];
                push = min(push, adj[p][idx].cap - adj[p][idx].flow);
                curr = p;
            }
 
            // Push flow and accumulate cost
            max_flow += push;
            // pot[t] represents the true original cost of the shortest path from s to t
            min_cost += push * pot[t];
 
            // Update residual graph
            curr = t;
            while (curr != s)
            {
                int p = parent_node[curr];
                int idx = parent_edge[curr];
                int rev_idx = adj[p][idx].rev;
                adj[p][idx].flow += push;
                adj[curr][rev_idx].flow -= push;
                curr = p;
            }
        }
 
        return {max_flow, min_cost};
    }
 
    // DFS for flow decomposition (path reconstruction)
    int dfs_path(int v, int t, int pushed, vector<int> &path, vector<int> &edge_ptr)
    {
        if (v == t)
            return pushed;
 
        for (int &cid = edge_ptr[v]; cid < adj[v].size(); ++cid)
        {
            auto &edge = adj[v][cid];
 
            // Only traverse forward edges that have positive flow
            if (edge.flow > 0)
            {
                path.push_back(edge.to);
                int tr_pushed = dfs_path(edge.to, t, min(pushed, edge.flow), path, edge_ptr);
 
                if (tr_pushed > 0)
                {
                    edge.flow -= tr_pushed; // Consume the flow to prevent reusing it
                    return tr_pushed;
                }
                path.pop_back(); // Backtrack
            }
        }
        return 0;
    }
 
    // Reconstructs all paths taking flow from s to t
    // Returns a vector of pairs: {bottleneck_flow, path_of_vertices}
    // NOTE: Calling this function consumes the flow values in the graph.
    vector<pair<int, vector<int>>> get_paths(int s, int t)
    {
        vector<pair<int, vector<int>>> paths;
        vector<int> edge_ptr(n, 0); // Optimization to skip depleted edges
 
        while (true)
        {
            vector<int> path;
            path.push_back(s);
            int pushed = dfs_path(s, t, INF, path, edge_ptr);
 
            if (pushed == 0)
                break;
            paths.push_back({pushed, path});
        }
        return paths;
    }
};
