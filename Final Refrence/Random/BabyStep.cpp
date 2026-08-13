int d_log(int a, int b, int mod) {
    int n = sqrt(mod) + 1;
    // store b * a ^ q  for all 0 <= q < n
    hash_map<int, int> mp;
    for (int i = 0, cur = b; i <= n ;i++, cur = 1LL * cur * a % mod)
        mp[cur] = i;
    int an = fp(a, n, mod);
    // lets try all a ^ (n * i) == b * a ^ q for all q values using the hash map
    for (int i = 1, cur = an; i <= n; i++, cur = 1LL * cur * an % mod)
        if (mp.find(cur) != mp.end())
                return n * i - mp[cur];
    return -1;
}