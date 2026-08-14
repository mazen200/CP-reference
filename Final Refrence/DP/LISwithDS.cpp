void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    int mx = 0;
    for (auto &x : v)
        cin >> x, mx = max(mx, x);
    vector<BIT> dp(k + 1, BIT(mx + 1));
    
    for (int i = 0; i < n; i++)
    {
        dp[1].update(v[i] + 1, 1);
        for (int j = 1; j < k; j++)
        {
            int add = dp[j].pref(v[i]);
            dp[j + 1].update(v[i] + 1, add);
        }
    }
    cout << dp[k].pref(mx + 1);
}
