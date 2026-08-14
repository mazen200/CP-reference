// sum (a[i] * b[i] % mod) but sum is not under mod

const int P = 200003;
int to[P];
void solve()
{
    ll cur = 1;
    for (int i = 0; i < P; i++, (cur *= 2) %= P)
        to[cur] = i;
    vector<int> p(P);
    ll sum = 0;
    int n;
    cin >> n;
    for (int i = 0, x; i < n; i++)
        cin >> x, p[to[x]] += (x > 0), sum -= 1ll * x * x % P;
    auto ans = multiply(p, p);
    for (int i = 0; i < ans.size(); i++)
        if (ans[i])
            sum += 1ll * fp(2, i, P) * ans[i];
    cout << sum / 2 << endl;
}