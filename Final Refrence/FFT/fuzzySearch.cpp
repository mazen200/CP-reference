const string chars = "ATGC";

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    string s, t;
    cin >> s >> t;
    int shift = m - 1;
    vector<int> ans(n);
    for (auto &ch : chars)
    {
        vector<int> p1(n + 1), p2(shift + 1);
        int cnt = 0;

        for (int i = 0; i < n; i++)
            if (s[i] == ch)
                p1[max(0, i - k)]++, p1[min(n, i + k + 1)]--, cnt++;
        for (int i = 0; i < n; i++)
            p1[i + 1] += p1[i];
        p1.pop_back();
        for (int i = 0; i < n; i++)
            p1[i] = bool(p1[i]);
        for (int i = 0; i < m; i++)
            p2[shift - i] = t[i] == ch;
        auto mult = multiply(p1, p2);
        for (int i = 0; i < n; i++)
            ans[i] += mult[i + shift];
    }
    cout << count(all(ans), m) << endl;
}
