int c[N];
int n;
vector<int> graph[N];
int heavy[N];
int freq[N];
int subtree[N];
int answer = 0;
int ans[N];
void update(int val, int delta)
{
    answer -= (freq[val] > 0);
    freq[val] += delta;
    answer += (freq[val] > 0);
}
void compress()
{
    map<int, int> mp;
    for (int i = 1; i <= n; i++)
        if (!mp.count(c[i]))
            mp[c[i]] = mp.size() + 1;
    for (int i = 1; i <= n; i++)
        c[i] = mp[c[i]];
}
void dfs0(int cur, int par)
{
    for (auto &ch : graph[cur])
    {
        if (ch == par)
            continue;
        dfs0(ch, cur);
        if (subtree[heavy[cur]] < subtree[ch])
            heavy[cur] = ch;
        subtree[cur] += subtree[ch];
    }
    subtree[cur]++;
}
void calc(int cur, int par, int delta)
{
    update(c[cur], delta);
    for (auto &ch : graph[cur])
        if (ch != par)
            calc(ch, cur, delta);
}
void dfs(int cur, int par, int keep)
{
    for (auto &ch : graph[cur])
    {
        if (ch == par || ch == heavy[cur])
            continue;
        dfs(ch, cur, 0);
    }
    if (heavy[cur])
        dfs(heavy[cur], cur, 1);
    for (auto &ch : graph[cur])
    {
        if (ch == par || ch == heavy[cur])
            continue;
        calc(ch, cur, 1);
    }
    update(c[cur], 1);
    ans[cur] = answer;
    if (!keep)
        calc(cur, par, -1);
}