```cpp
    int n, m, k;
    cin >> n >> m >> k;

    // f[x] = frequency of value x in the array
    vector<ll> f(m + 1);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        f[x]++;
    }

    /*
        div[i] = number of elements divisible by i.

        We iterate over multiples of i:

            i, 2i, 3i, ...

        and add their frequencies.
    */
    vector<ll> div(m + 1);

    for (int i = 1; i <= m; i++) {
        for (int j = i; j <= m; j += i) {
            div[i] += f[j];
        }
    }

    /*
        g[i] = number of NON-EMPTY subsequences
                whose gcd is exactly i.

        First:

            2^div[i] - 1

        counts all non-empty subsequences where every
        selected element is divisible by i.

        Their gcd can be:

            i, 2i, 3i, ...

        Therefore we subtract the answers for all
        proper multiples of i.
    */
    vector<ll> g(m + 1);

    for (int i = m; i >= 1; i--) {

        // All non-empty subsequences consisting of
        // elements divisible by i.
        g[i] = (modPow(2, div[i]) - 1 + MOD) % MOD;

        /*
            Remove subsequences whose gcd is a proper
            multiple of i.
        */
        for (int j = 2 * i; j <= m; j += i) {
            g[i] -= g[j];

            if (g[i] < 0)
                g[i] += MOD;
        }
    }
```
