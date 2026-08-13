struct XB
{
    static constexpr int B = 60;
    array<ll, B + 1> base{};
    int rank = 0;
    XB(int val = 0)
    {
        if (val)
            insert(val);
    }
    void insert(ll x)
    {
        for (int i = B; i >= 0; --i)
        {
            if (((x >> i) & 1LL) == 0)
                continue;
            if (base[i] == 0)
            {
                base[i] = x;
                ++rank;
                return;
            }
            x ^= base[i];
        }
    }
 
    // Check if x can be formed as XOR of some inserted numbers
    bool canRepresent(ll x) const
    {
        for (int i = B; i >= 0; --i)
        {
            if (((x >> i) & 1LL) && base[i])
                x ^= base[i];
        }
        return x == 0;
    }
 
    // Maximum XOR value achievable from any subset (starting from 0 by default)
    ll getMax(ll start = 0) const
    {
        ll res = start;
        for (int i = B; i >= 0; --i)
        {
            if (!base[i])
                continue;
            res = max(res, res ^ base[i]);
        }
        return res;
    }
    ll getKth(ll k)
    {
        if(k > (1ll << rank))
            return -1;
        k--;
        ll res = 0;
        for (int i = B, j = rank - 1; i >= 0; --i)
        {
            if (!base[i])
                continue;
            if ((k >> j) & 1)
                res = max(res, res ^ base[i]);
            else
                res = min(res, res ^ base[i]);
            j--;
        }
        return res;
    }
 
    int getRank() const
    {
        return rank;
    }
    const XB operator+(const XB &other) const
    {
        XB ret = *this;
        for (int i = B; i >= 0; --i)
        {
            if (other.base[i])
                ret.insert(other.base[i]);
        }
        return ret;
    }
};


// Xor Basis in Range (Offline precompute)


constexpr int B = 60;
 
ll basis[B + 1];
int closest[B + 1];
void insert(ll x, int idx)
{
    for (int i = B; i >= 0; i--)
    {
        if (!(x >> i & 1))
            continue;
        if (closest[i] < idx)
        {
            swap(x, basis[i]);
            swap(closest[i], idx);
        }
        x ^= basis[i];
    }
}
bool canRepresent(int l, ll x)
{
    for (int i = B; i >= 0; i--)
    {
        if (!(x >> i & 1))
            continue;
        if (closest[i] < l)
            return false;
        x ^= basis[i];
    }
    return true;
}