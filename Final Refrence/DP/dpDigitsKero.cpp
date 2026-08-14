void solve()
{
    string l, r;
    int k;
    cin >> l >> r >> k;
    if(r.size() > l.size())
        l = string(r.size() - l.size(), '0') + l;
    k = min(k, 99ll);
    int dp[r.size()][2][2][100][100];
    int n = r.size();
    memset(dp, -1, sizeof(dp));
    function<int(int, int , int , int, int)> sol = [&](int i, int canExceed, int canDown, int remNum, int remSum)->int
    {
        if(i == n)
            return !(remSum or remNum);
        auto &ret = dp[i][canExceed][canDown][remNum][remSum];
        if(~ret)
            return ret;
        ret = 0;
        for(int d = 0; d < 10; d++)
        {
            if(!canExceed and d > (r[i] - '0'))
                continue;
            if(!canDown and d < (l[i] - '0'))
                continue;
            ret += sol(i + 1, canExceed | (d != r[i] - '0'), canDown | (d != l[i] - '0'), (remNum + (d * (int)powl(10, n - i - 1))) % k, (remSum + d) % k);
        }
        return ret;
    };
    cout << sol(0, 0, 0, 0, 0) << endl;

}