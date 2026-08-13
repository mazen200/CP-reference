int n, m;
vector<int> a[N];
int dfsn[N], lowLink[N], inStack[N], comp[N], repr[N], dtime, scc;
stack<int> st;
void tarjan(int node)
{
    dfsn[node] = lowLink[node] = dtime++, inStack[node] = 1;
    st.push(node);
    for (auto &i : a[node])
    {
        if (dfsn[i] == -1)
        {
            tarjan(i);
            lowLink[node] = min(lowLink[node], lowLink[i]);
        }
        else if (inStack[i])
            lowLink[node] = min(lowLink[node], dfsn[i]);
    }
    if (dfsn[node] == lowLink[node])
    {
        int x = -1;
        while (x != node)
        {
            x = st.top(), st.pop();
            inStack[x] = 0;
            comp[x] = scc;
        }
        repr[scc] = node;
        scc++;
    }
}
int NOT(int x)
{
    return 2 * m - x + 1;
}
void add(int x, int y)
{
    a[NOT(x)].push_back(y);
    a[NOT(y)].push_back(x);
}
void doWork()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        char op;
        int x, y;
        cin >> op >> x;
        if (op == '-')
            x = NOT(x);
        cin >> op >> y;
        if (op == '-')
            y = NOT(y);
        add(x, y);
    }
    memset(dfsn, -1, sizeof dfsn);
    for (int i = 1; i <= 2 * m; i++)
    {
        if (dfsn[i] == -1)
            tarjan(i);
    }
    for (int i = 1; i <= m; i++)
    {
        if (comp[i] == comp[NOT(i)])
        {
            cout << "IMPOSSIBLE";
            return;
        }
    }
    vector<int> comp_values(scc + 1, -1), ans(m + 1);
    for (int i = 0; i < scc; i++)
    {
        if (comp_values[i] == -1)
        {
            comp_values[i] = 1;
            int dual = comp[NOT(repr[i])];
            comp_values[dual] = 0;
        }
    }
    for (int i = 1; i <= m; i++)
        ans[i] = comp_values[comp[i]];
}