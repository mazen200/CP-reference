int c[N];
vector<int> graph[N];
set<int> s[N];
int ans[N];
void dfs(int cur,int par)
{
    s[cur].insert(c[cur]);
    for(auto &ch : graph[cur])
    {
        if(ch == par)
            continue;
        dfs(ch, cur);
        if(s[ch].size() > s[cur].size())
            swap(s[ch], s[cur]);
        for(auto &x : s[ch])
            s[cur].insert(x);
    }
    ans[cur] = s[cur].size();
}