// You have some elements the max ouccurace of each element is m and you want to generate array of size of k of this elements
// the answer is fact[k] * sum(ifact of all possible frequencies of each element using ntt or fft with mod)

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> p(m + 1);
    p[m] = fp(fact[m], mod - 2);
    for (int i = m - 1; i >= 0; i--)
        p[i] = 1LL * p[i + 1] * (i + 1) % mod;
    p = poly_pw(p, n);
    int q;
    cin >> q;
    while (q--)
    {
        int k;
        cin >> k;
        cout << (1LL * fact[k] * p[k] % mod)<<' ';
    }
}