const char chrs[] = {'A', 'C', 'T', 'G'};
int stringMinMismatch(string str, string pattern)
{
    int n = str.size();
    int m = pattern.size();
    int shift = m - 1;
    vector<int> ans(n + m + 5);
    for (auto &ch : chrs)
    {
        vector<int> p1(n);
        vector<int> p2(m);
        for (int i = 0; i < n; i++)
            p1[i] = str[i] == ch;
        for (int i = 0; i < m; i++)
            p2[shift - i] = pattern[i] == ch;
        auto mult = multiply(p1, p2);
        for (int i = 0; i < n; i++)
            ans[i + shift] += mult[i + shift];
    }
    int mn = m;
    for (int i = 0; i <= n - m; i++)
        mn = min(mn, m - ans[i + shift]);
    return mn;
}
void solve()
{
    string s, p;
    cin >> s >> p;
    cout << stringMinMismatch(s, p) << endl;
}