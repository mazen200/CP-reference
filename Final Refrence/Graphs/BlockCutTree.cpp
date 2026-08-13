const int N = 4e5 + 3, LG = 23;

// ---- Tarjan & Block Cut Tree Part ----
vector<int> graph[N];
vector<int> BCT[N];
int isArt[N];
int low[N];
int dfsn[N];
int n, timer = 0, m, q;
int inBCT[N], valInBCT[N];

stack<int> st;
vector<vector<int>> comps;
bool rootEdge = false;
void tarjan(int cur = 1, int par = -1)
{
    low[cur] = dfsn[cur] = timer++;
    st.push(cur);
    for (auto &ch : graph[cur])
    {
        if (dfsn[ch] == -1)
        {
            tarjan(ch, cur);
            low[cur] = min(low[cur], low[ch]);
            if (low[ch] >= dfsn[cur])
            {
                if (dfsn[cur] == 0 and !rootEdge)
                    rootEdge = true;
                else
                    isArt[cur] = true;
                comps.push_back({cur});
                while (comps.back().back() != ch)
                    comps.back().push_back(st.top()), st.pop();
            }
        }
        else if (ch != par)
        {
            low[cur] = min(low[cur], dfsn[ch]);
        }
    }
}

inline void addEdgeTree(int u, int v)
{
    BCT[u].push_back(v), BCT[v].push_back(u);
}

inline void buildBCT()
{
    timer = 0;
    for (int i = 1; i <= n; i++)
        if (isArt[i])
            inBCT[i] = ++timer, valInBCT[inBCT[i]] = 1;
    for (auto &comp : comps)
    {
        int id = ++timer;
        for (auto &cur : comp)
            (isArt[cur]) ? (addEdgeTree(id, inBCT[cur])) : (inBCT[cur] = id, void());
    }
}

// ---- LCA  Part ----
int up[N][LG];
int deep[N];
int deepVal[N];
void dfs(int cur, int par)
{
    for (auto &ch : BCT[cur])
    {
        if (ch == par)
            continue;
        up[ch][0] = cur;
        deep[ch] = deep[cur] + 1;
        deepVal[ch] = deepVal[cur] + valInBCT[ch];
        for (int lg = 1; lg < LG and ~up[ch][lg - 1]; lg++)
            up[ch][lg] = up[up[ch][lg - 1]][lg - 1];
        dfs(ch, cur);
    }
}
inline int kthAnc(int u, int k)
{
    for (int lg = LG - 1; lg >= 0 and ~u; lg--)
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