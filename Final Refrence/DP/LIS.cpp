int n, mx = 0;
int arr[N] = {};
vector<int> dp(N, INF);
void solve()
{
    // memset(dp, -1, sizeof dp);
    cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    dp[0] = -INF;
    for (int i = 0; i < n; i++)
    {
        int l = upper_bound(dp.begin(), dp.end(), arr[i]) - dp.begin();
        if (dp[l - 1] < arr[i] && arr[i] < dp[l])
            dp[l] = arr[i];
    }
    for (int l = 0; l <= n; l++)
    {
        if (dp[l] < INF)
            mx = l;
    }
    cout << mx << endl;
}