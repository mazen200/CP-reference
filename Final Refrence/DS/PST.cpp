struct Node
{
    int sum;
    // int lx, rx; // lx (inclusive), rx(exclusive)
    Node *l, *r;
    Node() : sum(0), l(NULL), r(NULL)
    {
    }
    Node(int sum) : sum(sum), l(NULL), r(NULL)
    {
    }
};
const int R = 1e9 + 1;
int mul(int a, int b)
{
    return (a * b) % mod;
}
void merge(Node *ret)
{
    ret->sum = 1;
    ret->sum = mul(ret->sum, ret->l ? ret->l->sum : 0);
    ret->sum = mul(ret->sum, ret->r ? ret->r->sum : 0);
}
Node *merge(Node *lf, Node *rf)
{
    Node *ret = NULL;
    if (!lf and !rf)
        return NULL;
    ret = new Node();
    ret->sum = 1;
    if (lf)
    {
        ret->sum = mul(ret->sum, lf->sum);
        delete lf;
        lf = NULL;
    }
    if (rf)
    {
        ret->sum = mul(ret->sum, rf->sum);
        delete rf;
        rf = NULL;
    }
    return ret;
}
Node *root;
void upd(int idx, int delta, Node *cur, int lx, int rx)
{

    if (rx - lx == 1)
    {
        cur->sum += delta;
        return;
    }
    int mid = (lx + rx) / 2;
    if (idx < mid)
    {
        if (!cur->l)
            cur->l = new Node();
        upd(idx, delta, cur->l, lx, mid);
    }
    else
    {
        if (!cur->r)
            cur->r = new Node();
        upd(idx, delta, cur->r, mid, rx);
    }
    merge(cur);
}
void upd(int idx, int delta)
{
    upd(idx, delta, root, 0, R);
}
Node *get(int l, int r, Node *cur, int lx, int rx)
{
    if (lx >= r or rx <= l)
        return NULL;
    if (!cur)
        return new Node(0);
    if (l <= lx and rx <= r)
        return new Node(cur->sum);
    int mid = (lx + rx) / 2;
    auto lf = get(l, r, cur->l, lx, mid);
    auto rf = get(l, r, cur->r, mid, rx);
    auto ret = merge(lf, rf);
    return ret;
}
int get(int l, int r)
{
    Node *ret = get(l, r, root, 0, R);
    if (!ret)
        return 0;
    int ret_sum = ret->sum;
    delete ret;
    ret = NULL;
    return ret_sum;
}
void clear(Node *cur)
{
    if (cur->l)
        clear(cur->l);
    if (cur->r)
        clear(cur->r);
    delete cur;
    cur = NULL;
}