struct BIT
{
    vector<int> tree;
    vector<int> tree2;
    int treeSize;
    BIT(int n) : treeSize(n)
    {
        tree.assign(n + 1, 0);
        tree2.assign(n + 1, 0);
    }
    void add(int idx, int delta, vector<int> &tree)
    {
        while (idx <= treeSize)
        {
            tree[idx] += delta;
            idx += (idx & -idx);
        }
    }
    int query(int idx, vector<int> &tree)
    {
        int ret = 0;
        while (idx > 0)
        {
            ret += tree[idx];
            idx -= (idx & -idx);
        }
        return ret;
    }
    void update(int l, int r, int delta)
    {
        add(l, delta, tree);
        add(r + 1, -delta, tree);
        add(l, delta * (l - 1), tree2);
        add(r + 1, -delta * r, tree2);
    }
    int pref(int idx)
    {
        return query(idx, tree) * idx - query(idx, tree2);
    }
    int get(int l, int r)
    {
        return pref(r) - pref(l - 1);
    }
};