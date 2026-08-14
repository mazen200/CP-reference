bool CheckOddCycle()
{
    int vis[N + 2];
    memset(vis, -1, sizeof vis);
    vis[1] = 1;
    queue<int> q;
    q.push(1);
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        for (auto it : v[node])
        {
            if (vis[it] == -1)
            {
                vis[it] = 1 - vis[node];
                q.push(it);
            }
            else if (vis[it] == vis[node])
                return true;
        }
    }
    return false;
}