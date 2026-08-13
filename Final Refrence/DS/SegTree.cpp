struct Node
{
    ll val = 0;
};
struct SegmentTree
{
    Node neutral;
    vector <Node> tree;
    vector <ll> lazy;
    SegmentTree(int n)
    {
        tree.resize(4 * n);
        lazy.resize(4 * n, 1e6);
    }
    Node single(int idx, vector <int> &a)
    {
        return Node({a[idx]});
    }
    Node merge(Node x, Node y)
    {
        return Node({x.val + y.val});
    }
    void build(int node, int s, int e, vector <int> &a)
    {
        if(s == e)
        {
            tree[node] = single(s, a);
            return;
        }

        int m = (s + e) >> 1;

        build(2 * node, s, m, a);
        build(2 * node + 1, m + 1, e, a);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void propagate(int node, int s, int e)
    {
        if(lazy[node] == (ll)1e6)
            return;
        if(s == e)
        {
            tree[node].val = aa[s + lazy[node]];
        }
        if(s != e)
        {
            lazy[2 * node] = lazy[node];
            lazy[2 * node + 1] = lazy[node];
        }
        lazy[node] = 1e6;
    }
    void update(int node, int s, int e, int l, int r, int val)
    {
        propagate(node, s, e);
        if(s > r || e < l)
            return;
        if(s >= l && e <= r)
        {
            lazy[node] = val;
            propagate(node, s, e);
            return;
        }
        int m = (s + e) >> 1;

        update(2 * node, s, m, l, r, val);
        update(2 * node + 1, m + 1, e, l, r, val);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    Node query(int node, int s, int e, int l, int r)
    {
        propagate(node, s, e);
        if(s > r || e < l)
            return neutral;
        if(s >= l && e <= r)
            return tree[node];
        int m = (s + e) >> 1;
        return merge(query(2 * node, s, m, l ,r), query(2 * node + 1, m + 1, e, l, r));
    }
};