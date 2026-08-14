int phi[N + 1];
int mu[N + 1];
bool vis[N + 1];
vector<int> divs[N + 1];

void pre()
{
    for (int i = 1; i <= N; i++)
        phi[i] = i, mu[i] = 1;
    for (int i = 2; i <= N; i++)
        if (phi[i] == i)
            for (int j = i; j <= N; j += i)
                phi[j] -= phi[j] / i;
    for (int i = 2; i <= N; i++)
        if (!vis[i])
            for (int j = i; j <= N; j += i)
                vis[j] = 1, mu[j] = (j % (i * i) == 0 ? 0 : (mu[j] * -1));
}