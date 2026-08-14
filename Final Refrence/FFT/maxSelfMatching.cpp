const char chrs[] = {'a', 'b', 'c'};
vector<int> stringMaxSelfMatching(string s)
{
    string p = s;
    int n = s.size();
    s = s + string(n, '#');
    int shift = n - 1;
    vector<int> ans(2 * n + 5);
    for(auto &ch : chrs)
    {
        vector<int> p1(2 * n);
        vector<int> p2(n);
        for(int i = 0; i < 2 * n; i++)
            p1[i] = s[i] == ch;
        for(int i = 0; i < n; i++)
            p2[shift - i] = s[i] == ch;
        auto mult = multiply(p1, p2);
        for(int i = 1;i < n; i++)
            ans[i + shift] += mult[i + shift];
    }
    return vector<int>(ans.begin() + shift, ans.begin() + shift + n);
}
void solve()
{
    string s;
    cin >> s;
    auto ans = stringMaxSelfMatching(s);
    int mx = *max_element(all(ans));
    cout << mx << endl;
    for(int i = 1; i < s.size(); i++)
        if(ans[i] == mx)
            cout << i << endl;
}