template <typename T>
struct SegmentTree
{
    int treeSize;
    vector<T> tree;
    T neutral = T();
    SegmentTree(int n, vector<int> arr = {})
    {
        treeSize = 1;
        while (treeSize < n)
            treeSize <<= 1;
        tree.assign((treeSize << 1), neutral);
        for (int i = 0; i < arr.size(); i++)
            tree[i + treeSize] = T(arr[i]);
        for (int i = treeSize - 1; i > 0; i--)
            tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }
    inline void update(int idx, int v) // idx : (0-based)
    {
        idx += treeSize;
        tree[idx].change(v);
        for (idx >>= 1; idx > 0; idx >>= 1)
            tree[idx] = tree[idx << 1] + tree[idx << 1 | 1];
    }
    inline int get(int l, int r) // L : (inclusive), R : (exclusive)
    {
        T lf, rf;
        for (l += treeSize, r += treeSize; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                lf = lf + tree[l++];
            if (r & 1)
                rf = tree[--r] + rf;
        }
        lf = lf + rf;
        return lf;
    }
};
struct Node
{
    int sum;
    Node(int sum = INF) : sum(sum)
    {
    }
    inline void change(int sum)
    {
        this->sum = sum;
    }
    operator int() const
    {
        return this->sum;
    }
    const Node operator+(const Node &other)
    {
        return Node(min(this->sum, other.sum));
    }
};