
const int mod = 1e9 + 7;
const int N = 1e6;
pair<int, int> pw[N], inv[N];

int add(int a, int b)
{
    return (1ll * a + b + mod) % mod;
}
int mul(int a, int b)
{
    return (1ll * a * b) % mod;
}
int fastpow(int a, int b)
{
    if (!b)
        return 1;
    int hp = fastpow(a, b >> 1);
    hp = mul(hp, hp);
    return (b & 1 ? mul(hp, a) : hp);
}
int modInverse(int a)
{
    return fastpow(a, mod - 2);
}
void preHash()
{
    vector<int> primes;
    for (int i = 1; i <= 293; i++)
    {
        bool p = true;
        for (int j = 2; j * j <= i; j++)
        {
            if (i % j == 0)
                p = false;
        }
        if (p)
            primes.push_back(i);
    }
    srand(time(0));
    int b1 = primes[rand() % 62], b2 = primes[rand() % 62];
    pw[0] = inv[0] = {1, 1};
    int invB1 = modInverse(b1), invB2 = modInverse(b2);
    for (int i = 1; i < N; i++)
    {
        pw[i] = {mul(b1, pw[i - 1].first), mul(b2, pw[i - 1].second)};
        inv[i] = {mul(invB1, inv[i - 1].first), mul(invB2, inv[i - 1].second)};
    }
}
struct Hash
{
    vector<pair<int, int>> pre;
    pair<int, int> h(int num, int p)
    {
        return {mul(num, pw[p].first), mul(num, pw[p].second)};
    }
    int fa7l(char a)
    {
        return (a - 'a' + 1);
    }
    Hash(string &s)
    {
        pre.resize(s.size());
        for (int i = 0; i < s.size(); i++)
        {
            pre[i] = h(fa7l(s[i]), i);
            if (i)
                pre[i] = {add(pre[i].first, pre[i - 1].first), add(pre[i].second, pre[i - 1].second)};
        }
    }
    pair<int, int> getPrefix(int l, int r)
    {
        if (!l)
            return pre[r];
        return {mul(add(pre[r].first, -pre[l - 1].first), inv[l].first), mul(add(pre[r].second, -pre[l - 1].second), inv[l].second)};
    }
};