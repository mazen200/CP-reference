void update(int x1, int y1, int x2, int y2, int val)
{
    p_sum[x1][y1] += val;
    p_sum[x2 + 1][y2 + 1] += val;
    p_sum[x1][y2 + 1] -= val;
    p_sum[x2 + 1][y1] -= val;
}

for (int i = 1; i < 1004; i++)
{
    for (int j = 1; j < 1004; j++)
    {
        pref[i][j] += pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
    }
}
while (q--)
{
    ll la, lb, pa, pb;
    cin >> la >> lb >> pa >> pb;
    cout << pref[pa - 1][pb - 1] - pref[la][pb - 1] - pref[pa - 1][lb] + pref[la][lb] << endl;
}