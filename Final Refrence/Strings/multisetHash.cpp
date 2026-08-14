int b[2];
int pw[2][N];
int inv[2][N];
void precalc()
{
    b[0] = rand() + 2;
    b[1] = rand() + 2;
    pw[0][0] = pw[1][0] = inv[0][0] = inv[1][0] = 1;
    int invB[] = {modInverse(b[0]), modInverse(b[1])};
    for (int j = 0; j < 2; j++)
        for (int i = 1; i < N; i++)
            pw[j][i] = mul(pw[j][i - 1], b[j]), inv[j][i] = mul(inv[j][i - 1], invB[j]);
}
int doit(char c)
{
    return (c - 'a' + 1);
}
typedef array<int, 2> Hash;
void solve()
{
    int n;
    vector<Hash> prefa(n + 1), prefb(n + 1);
    // A Hashing
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 2; j++)
            prefa[i + 1][j] = addm(prefa[i][j], pw[j][a[i]]);
    // B Hashing
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 2; j++)
            prefb[i + 1][j] = addm(prefb[i][j], pw[j][b[i]]);   
}