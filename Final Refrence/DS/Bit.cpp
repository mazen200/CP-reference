struct BIT {
    int n;
    vector<int> tree;
 
    BIT(int n) : n(n) {
        tree.resize(n + 1);
    }
 
    void update(int idx, int delta) {
        for (; idx <= n; idx += (idx & -idx))
            tree[idx] += delta;
    }
 
    int pref(int idx) {
        int ret = 0;
        for (; idx > 0; idx -= (idx & -idx))
            ret += tree[idx];
        return ret;
    }
 
    int get(int l, int r) {
        return pref(r) - pref(l - 1);
    }
};