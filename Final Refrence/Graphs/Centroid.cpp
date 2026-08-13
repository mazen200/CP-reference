#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;
const int N = 2e5 + 3;
vector<int> g[N];
int sz[N];
int cnt[N];
bool isRem[N]{};
int n, k;
ll ans = 0;
void dfsSz(int u, int p)
{
    sz[u] = 1;
    for (auto &v : g[u])
        if (v != p and !isRem[v])
            dfsSz(v, u), sz[u] += sz[v];
}
 
int getCent(int u, int p, int cur_sz)
{
    for (auto &v : g[u])
        if (v != p and !isRem[v])
            if (2 * sz[v] > cur_sz)
                return getCent(v, u, cur_sz);
    return u;
}
 
void dfsAdd(int u, int p, int depth)
{
    cnt[depth]++;
    for (auto &v : g[u])
        if (v != p and !isRem[v])
            dfsAdd(v, u, depth + 1);
}
void getAns(int u, int p, int depth)
{
    if (depth <= k)
        ans += cnt[k - depth];
    for (auto &v : g[u])
        if (v != p and !isRem[v])
            getAns(v, u, depth + 1);
}
void decompose(int u)
{
    dfsSz(u, -1);
    int cent = getCent(u, -1, sz[u]);
 
    // Logic For Answer Here
    cnt[0] = 1;
    for (auto &v : g[cent])
        if (!isRem[v])
            getAns(v, cent, 1), dfsAdd(v, cent, 1);
    // clear
    memset(cnt, 0, sz[u] * (sizeof cnt[0]));
 
    // Solving for other subtrees 
    isRem[cent] = 1;
    for (auto &v : g[cent])
        if (!isRem[v])
            decompose(v);
}
 
void solve()
{
    cin >> n >> k;
    int m = n - 1;
    while (m--)
    {
        int u, v;
        cin >> u >> v, u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    decompose(0);
    cout << ans << endl;
}
 
signed main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int t{1};
    // cin >> t;
    while (t--)
        solve();
}