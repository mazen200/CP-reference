void solve()
{
    int m;
    cin >> m;
    vector<vector<ll>> polys(m + 1);
    priority_queue<pii,vector<pii>, greater<>> pq; // (size, idx)
    polys[0] = {1};
    pq.push({1, 0});
    for(int i = 1; i <= m; i++)
    {
        int n;
        cin >> n;
        polys[i].resize(n + 1);
        for(auto &x : polys[i])
            cin >> x;
        pq.push({n + 1, i});
    }
    while(pq.size() > 1)
    {
        int nIdx = pq.top().second;
        auto &p1 = polys[pq.top().second];
        pq.pop();
        auto &p2 = polys[pq.top().second];
        pq.pop();
        int nSz = p1.size() + p2.size() - 1;
        p1 = conv(p1, p2);
        pq.push({nSz, nIdx});
    }
    auto &ans = polys[pq.top().second];
    for(auto & x :ans)
        cout << x << ' ';
}