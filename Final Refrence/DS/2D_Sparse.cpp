int g[N][N];
struct SparseTable2D
{
    int lg2[N];
    int st[N][N][LG][LG];
    void pre(int n, int m)
    {
        for (int i = 2; i < N; i++)
            lg2[i] = lg2[i >> 1] + 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                st[i][j][0][0] = g[i][j];
            }
        }
    }
    void build(int n, int m)
    {
        pre(n, m);
        for (int a = 0; a < LG; a++)
        {
            for (int b = 0; b < LG; b++)
            {
                if (a + b == 0)
                    continue;
                for (int i = 0; i + (1 << a) <= n; i++)
                {
                    for (int j = 0; j + (1 << b) <= m; j++)
                    {
                        if (!a)
                            st[i][j][a][b] = max(st[i][j][a][b - 1],

                                                 st[i][j + (1 << (b - 1))][a][b - 1]);

                        else
                            st[i][j][a][b] = max(st[i][j][a - 1][b], st[i

                                                                        + (1 << (a - 1))][j][a - 1][b]);
                    }
                }
            }
        }
    }
    int query(int x1, int y1, int x2, int y2)
    {
        x2++, y2++;
        int a = lg2[x2 - x1], b = lg2[y2 - y1];

        return max(
            max(st[x1][y1][a][b], st[x2 - (1 << a)][y1][a][b]),
            max(st[x1][y2 - (1 << b)][a][b], st[x2 - (1 << a)][y2 -

                                                               (1 << b)][a][b]));
    }
};