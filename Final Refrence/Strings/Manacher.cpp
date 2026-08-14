vector<int> manacher(string &orginal)
{
    int n = size(orginal);
    string s = string(2 * n + 1, '#');
    for (int i = 0; i < n; i++)
        s[2 * i + 1] = orginal[i];
    n = 2 * n + 1;
    s.insert(s.begin(), '$');
    s.push_back('^');
    vector<int> p(n + 2);
    int l = 0, r = 1;
    for (int i = 1; i <= n; i++)
    {
        p[i] = min(r - i, p[l + r - i]);
        while (s[i - p[i]] == s[i + p[i]])
            p[i]++;
        if (i + p[i] > r)
            r = i + p[i], l = i - p[i];
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}