void preHash()
{
    auto now = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(now.time_since_epoch());
    srand(duration.count());
    int b[] = {31, 37};
    int pw[2][N];
    int inv[2][N];
    pw[0][0] = pw[1][0] = inv[0][0] = inv[1][0] = 1;
    int invB[] = {modInverse(b[0]), modInverse(b[1])};
    for (int j = 0; j < 2; j++)
        for (int i = 1; i < N; i++)
            pw[j][i] = mul(pw[j][i - 1], b[j]), inv[j][i] = mul(inv[j][i - 1], invB[j]);
}

void rabin()
{
    for (int j = 0; j < 2; j++)
        for (int i = 0; i < n; i++)
            pref[i + 1][j] = addm(pref[i][j], mul(doit(s[i]), pw[j][i]));
    function<Hash(int, int)> getHash = [&](int l, int r) -> Hash {
        Hash h = pref[r];
        h[0] = mul(addm(h[0], -pref[l - 1][0]), inv[0][l - 1]);
        h[1] = mul(addm(h[1], -pref[l - 1][1]), inv[1][l - 1]);
        return h;
    };
}