#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <vector>
#define Kero                                                                                                           \
    ios_base::sync_with_stdio(0);                                                                                      \
    cout.tie(0);                                                                                                       \
    cin.tie(0)
#define ll long long
#define ull unsigned long long
#define all(x) x.begin(), x.end()
#define allr(x) x.rbegin(), x.rend()
#define int ll
#define ld long double
#define pii pair<int, int>
#define endl '\n'
#define see(x) " [" << #x << " = " << (x) << "] "
using namespace std;
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
// order_of_key (k) : Number of items strictly smaller than k
// find_by_order(k) : K-th element in a set (counting from zero)
const int INF = 1e18, N = 2e5 + 5, mod = 1e9 + 7, LG = 20;
const ld pi = 2 * acos(0), eps = 1e-6;

void fileIO()
{
#ifndef ONLINE_JUDGE
    freopen("io/input.txt", "r", stdin);
    freopen("io/output.txt", "w", stdout);
#endif
}

// Coding is so easy if you simulate on paper first
map<int, int> facts;
int addm(int a)
{
    return ((a % mod) + mod) % mod;
}
template <typename... Args>
int addm(int a, Args... args)
{
    return (addm(a) + addm(args...)) % mod;
}
int subtm(int a, int b)
{
    return ((a % mod) - (b % mod) + mod) % mod;
}
int mul(int a)
{
    return ((a % mod) + mod) % mod;
}
template <typename... Args>
int mul(int a, Args... args)
{
    return (mul(a) * mul(args...)) % mod;
}
int fastpow(int b, int p)
{
    if (p == 0 || b == 1)
        return 1;
    int sub = fastpow(b, p / 2);
    if (p % 2 == 0)
        return mul(sub, sub);
    return mul(mul(sub, sub), b);
}
inline int modInverse(int a)
{
    return fastpow(a, mod - 2);
}
inline int divi(int a, int b)
{
    return mul(a, modInverse(b));
}
ll fact(ll a)
{
    if (a == 0ll)
        return 1;
    if (!facts.count(a))
        facts[a] = mul(fact(a - 1), a);
    return facts[a];
}
inline int nPr(int n, int r)
{
    if (n < r)
        return 0;
    return divi(fact(n), fact(n - r));
}
inline int nCr(int n, int r)
{
    if (n < r)
        return 0;
    return divi(nPr(n, r), fact(r));
}
inline int starsNbars(int n, int r)
{
    return nCr(n + r - 1, r);
}
int b[] = {31, 37};
int pw[N][2];
int inv[N][2];
inline void precalc()
{
    pw[0][0] = pw[0][1] = inv[0][0] = inv[0][1] = 1;
    int invB[] = {modInverse(b[0]), modInverse(b[1])};
    for (int i = 1; i < N; i++)
        for (int j = 0; j < 2; j++)
            pw[i][j] = mul(pw[i - 1][j], b[j]), inv[i][j] = mul(inv[i - 1][j], invB[j]);
}
inline int doit(char c)
{
    return (c - 'a' + 1);
}
struct Hash
{
    int sum[2];
    int len;
    Hash()
    {
        sum[0] = sum[1] = 0;
        len = 0;
    }
    Hash(char c)
    {
        sum[0] = doit(c) * b[0];
        sum[1] = doit(c) * b[1];
        len = 1;
    }
    Hash operator+(const Hash &other) const
    {
        Hash ret = *this;
        ret.len = len + other.len;
        for (int i = 0; i < 2; i++)
        {
            ret.sum[i] = mul(ret.sum[i], pw[other.len][i]);
            ret.sum[i] = addm(ret.sum[i], other.sum[i]);
        }
        return ret;
    }
    // subtract The Sufix
    Hash operator-(const Hash &other) const
    {
        Hash ret = *this;
        ret.len = len - other.len;
        for (int i = 0; i < 2; i++)
        {
            ret.sum[i] = addm(ret.sum[i], -other.sum[i]);
            ret.sum[i] = mul(ret.sum[i], inv[other.len][i]);
        }
        return ret;
    }
    bool operator==(const Hash &other) const
    {
        return len == other.len and sum[0] == other.sum[0] and sum[1] == other.sum[1];
    }
    Hash sub_pref(const Hash &other) const
    {
        Hash ret = *this;
        ret.len = len - other.len;
        for (int i = 0; i < 2; i++)
        {
            ret.sum[i] = addm(ret.sum[i], -mul(other.sum[i], pw[ret.len][i]));
        }
        return ret;
    }
    static vector<Hash> getHash(string &str)
    {
        vector<Hash> ret;
        ret[0] = Hash(str[0]);
        for (int i = 1; i < str.size(); i++)
            ret[i] = ret[i - 1] + Hash(str[i]);
        return ret;
    }
    static Hash getRange(vector<Hash> &hsh, int l, int r)
    {
        l--;
        Hash ret = hsh[r];
        if (l)
            ret = ret - hsh[l];
        return ret;
    }
};


string str;
int deep[N];
Hash deepHash[N];
Hash deepHash2[N];
vector<int> g[N];
int up[N][LG];
void init(int n)
{
    for(int i = 0; i <= n; i++)
    {
        memset(up[i], 0, sizeof up[i]);
        deepHash[i] = Hash();
        deepHash2[i] = Hash();
        g[i].clear();
    }
}
void dfs(int cur)
{
    for (auto &ch : g[cur])
    {
        if (ch == up[cur][0])
            continue;
        deep[ch] = deep[cur] + 1;
        up[ch][0] = cur;
        deepHash[ch] = deepHash[cur] + Hash(str[ch]);
        deepHash2[ch] = Hash(str[ch]) + deepHash2[cur];
        for (int lg = 1; lg < LG and up[ch][lg - 1]; lg++)
            up[ch][lg] = up[up[ch][lg - 1]][lg - 1];
        dfs(ch);
    }
}
inline int kthAnc(int u, int k)
{
    for (int lg = LG - 1; lg >= 0; lg--)
        if ((k >> lg) & 1)
            u = up[u][lg];
    return u;
}
inline int getLca(int u, int v)
{
    if (deep[v] > deep[u])
        swap(v, u);
    u = kthAnc(u, deep[u] - deep[v]);
    if (u == v)
        return u;
    for (int lg = LG - 1; lg >= 0; lg--)
        if (up[u][lg] != up[v][lg])
            u = up[u][lg], v = up[v][lg];
    return up[u][0];
}
inline int getDist(int u, int v)
{
    return deep[u] + deep[v] - 2 * deep[getLca(u, v)];
}
inline Hash getPath(int u, int v)
{
    int lca = getLca(u, v);
    Hash hsh_v = deepHash[v].sub_pref(deepHash[up[lca][0]]);
    Hash hsh_u = deepHash2[u] - deepHash2[lca];
    // cout << see(lca) << endl;
    // cout << hsh_u.sum[0] << endl;
    return hsh_u + hsh_v;
}
inline int kthInPath(int u, int v, int k)
{
    int lca = getLca(u, v);
    int dist = deep[u] + deep[v] - 2 * deep[lca];
    if (deep[u] - deep[lca] < k)
        return kthAnc(v, dist - k);
    else
        return kthAnc(u, k);
}
inline int query(int a, int b, int c, int d)
{
    int d1 = getDist(a, b);
    int d2 = getDist(c, d);
    int dist = min(d1, d2);
    // cout << getPath(a, b).sum[0] << endl;
    // cout << getPath(c, d).sum[0] << endl;
    int l = 0, r = dist, mid, ans = -1;
    while(l <= r)
    {
        mid = l + (r - l) / 2;
        Hash hsh_a = getPath(a, kthInPath(a, b, mid));
        Hash hsh_c = getPath(c, kthInPath(c, d, mid));
        if(hsh_a == hsh_c)
        {
            l = mid + 1;    
        }
        else
        {
            ans = mid;
            r = mid - 1;
        }
    }
    if(ans == -1)
    {
        if(d1 > d2)
            return 1;
        else if (d1 < d2)
            return 2;
        return 0;
    }
    int kth_a = kthInPath(a, b, ans);
    int kth_c = kthInPath(c, d, ans);
    if(str[kth_a] > str[kth_c])
        return 1;
    return 2;
}
inline void solve()
{
    int n;
    cin >> n;
    init(n);
    // Hash hsh;
    // str = "bab";
    // for(int i = 0; i < 3; i++)
    //     hsh = hsh + Hash(str[i]);
    // cout << hsh.sum[0] << endl;
    // hsh = hsh - Hash();
    // cout << hsh.sum[0] << endl;
    // cout << endl;
    cin >> str;
    str = " "+ str;
    for(int i = 2, u, v; i <= n; i++)
        cin >> u >> v, g[u].push_back(v), g[v].push_back(u);
    deep[1] = 0;
    deepHash[1] = Hash(str[1]);
    deepHash2[1] = Hash(str[1]);
    dfs(1);
    // cout << getPath(1, 3).sum[0] << endl;
    int q;
    cin >> q;
    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        cout << query(a, b, c, d) << endl;
    }
}

signed main()
{
    Kero;
    fileIO();
    precalc();
    int t = 1;
    cin >> t;
    while (t--)
        solve();
    return 0;
}