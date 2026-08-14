const int sqt = 450;
int n{0}, q{0};
int lazy[sqt + 1]{};
int lazySet[sqt + 1]{};
int buckets[sqt + 1]{};
int arr[N]{};
void build(int buc_num)
{
    buckets[buc_num] = 0;
    for (int i = buc_num * sqt; i < min(n, (buc_num + 1) * sqt); i++)
    {
        if (lazySet[buc_num])
            arr[i] = lazySet[buc_num];
        if (lazy[buc_num])
            arr[i] += lazy[buc_num];
        buckets[buc_num] += arr[i];
    }
    lazySet[buc_num] = lazy[buc_num] = 0;
}
void updateSet(int l, int r, int x)
{
    build(l / sqt);
    build(r / sqt);
    for (int i = l; i <= r;)
    {
        if (i % sqt == 0 and i + sqt - 1 <= r)
        {
            buckets[i / sqt] = sqt * x;
            lazy[i / sqt] = 0;
            lazySet[i / sqt] = x;
            i += sqt;
        }
        else
        {
            buckets[i / sqt] -= arr[i];
            arr[i] = x;
            buckets[i / sqt] += arr[i];
            i++;
        }
    }
};
void update(int l, int r, int x)
{
    build(l / sqt);
    build(r / sqt);

    for (int i = l; i <= r;)
    {
        if (i % sqt == 0 and i + sqt - 1 <= r)
        {
            buckets[i / sqt] += sqt * x;
            lazy[i / sqt] += x;
            i += sqt;
        }
        else
        {
            buckets[i / sqt] -= arr[i];
            arr[i] += x;
            buckets[i / sqt] += arr[i];
            i++;
        }
    }
};
int query(int l, int r)
{
    build(l / sqt);
    build(r / sqt);
    int ret = 0;
    for (int i = l; i <= r;)
    {
        if (i % sqt == 0 and i + sqt - 1 <= r)
        {
            ret += buckets[i / sqt];
            i += sqt;
        }
        else
        {
            ret += arr[i];
            i++;
        }
    }
    return ret;
}