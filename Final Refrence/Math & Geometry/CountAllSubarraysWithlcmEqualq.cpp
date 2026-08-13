//count all arrays with lcm(a[i], a[i+1]) == k

inline vector<int> getPrimeFactors(int x)
{
    map<int, int> freq;
    vector<int> ret;
    for (int i = 2; i * i <= x; i++)
        while (x % i == 0)
            freq[i]++, x /= i;
    if(x > 1)
        freq[x]++;
    for(auto &[p, frq] : freq)
        ret.push_back(frq);
    return ret;
}
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int> factors = getPrimeFactors(k);
    ll ans = 1;
    Matrix S, T;
    for(auto &frq : factors)
    {
        S = {{0, 1}};
        T = {{0, 1},
             {frq, 1}};
        T = power(T, n);
        S = mul(S, T);
        S[0][1]  = (1LL * S[0][0] + S[0][1]) % mod;
        ans *= S[0][1];
        ans %= mod;
    }
    cout << ans << endl;
}