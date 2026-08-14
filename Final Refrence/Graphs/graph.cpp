bool visited[N]{};
void dfs(vector<vector<int>> &graph, int st)
{
    visited[st] = true;
    for (auto &child : graph[st])
        if (!visited[child])
            dfs(graph, child);
}

vector<int> bfs(vector<vector<int>> &graph, int st)
{
    vector<int> dist(graph.size(), INF);
    queue<int> nextToVisit;
    dist[st] = 0;
    nextToVisit.push(st);
    while (!nextToVisit.empty())
    {
        auto cur = nextToVisit.front();
        nextToVisit.pop();
        for (auto &ch : graph[cur])
        {
            if (dist[ch] == INF)
            {
                dist[ch] = dist[cur] + 1;
                nextToVisit.push(ch);
            }
        }
    }
    return dist;
}

vector<int> dijk(vector<vector<pii>> &graph, int st)
{
    vector<int> dist(graph.size(), INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> nextToVisit;
    dist[st] = 0;
    nextToVisit.push({0, st});
    while (nextToVisit.size())
    {
        auto [curCost, curDist] = nextToVisit.top();
        nextToVisit.pop();
        if (curCost > dist[curDist])
            continue;
        for (auto &[cw, cd] : graph[curDist])
        {
            if (dist[cd] > cw + curCost)
            {
                dist[cd] = cw + curCost;
                nextToVisit.push({dist[cd], cd});
            }
        }
    }
    return dist;
}

void kahn(vector<vector<int>> &graph, int &n)
{
    vector<int> degree(n + 1, 0);
    vector<bool> visited(n + 1, false);
    for (int i = 1; i <= n; i++)
    {
        for (auto &j : graph[i])
        {
            degree[j]++;
        }
    }
    queue<int> nextToVisit;
    for (int i = 1; i <= n; i++)
    {
        if (!degree[i])
        {
            nextToVisit.push(i);
            visited[i] = true;
        }
    }
    vector<int> result;
    while (nextToVisit.size())
    {
        int cur = nextToVisit.front();
        nextToVisit.pop();
        result.push_back(cur);
        for (auto &j : graph[cur])
        {
            degree[j]--;
            if (!degree[j])
                nextToVisit.push(j);
        }
    }
    if (result.size() != n)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        for (auto &j : result)
            cout << j << ' ';
        cout << endl;
    }
}

vector<int> BellmanFord(vector<vector<pii>> &graph, int &V, int st)
{
    vector<int> dist(V + 1, INF);
    dist[st] = 0;
    bool flag = false;
    for (int edgesUsed = 1; edgesUsed <= V; edgesUsed++)
    {
        for (int u = 1; u <= V; u++)
        {
            if (dist[u] == INF)
                continue;
            for (auto &[cost, v] : graph[u])
            {
                if(dist[v] > dist[u] + cost)
                    dist[v] = dist[u] + cost, flag |= (v == V and edgesUsed == V);
            }
        }
    }
    if(flag)
        return {};
    return dist;
}
void floyd()
{
    int d[N][N];
    for(int k = 1; k <= n; k++)
        for(int u = 1; u <= n; u++)
            for(int v = 1; v <= n; v++)
                d[u][v] = max(d[u][v], d[u][k] + d[k][v]);
}