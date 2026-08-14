void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    int mn = 0;
    for (int i = 0; i < n; i++)
        cin >> a[i], mn = min(a[i], mn);
    const int shift = 5e4;
    vector<int> p1(4 *shift + 1);
    int zeros = 0;
    for (int i = 0; i < n; i++)
        p1[a[i] + shift]++, zeros += (a[i] == 0);
    auto pw = multiply(p1, p1);
    for (int i = 0; i < n; i++)
            pw[2 * a[i] + 2 * shift]--;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {

        ans += pw[a[i] + 2 * shift] - 2 * (zeros - (a[i] == 0));
    }
    cout << ans << endl;
}