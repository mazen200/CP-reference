template <typename T>
struct SparseTable
{
    vector<vector<T>> table;
    vector<int> lgs;
    function<T(T, T)> myFunction;

    void build(T arr[], function<T(T, T)> fun, int n)
    {
        myFunction = fun;
        table = vector<vector<T>>(n + 1, vector<T>(20));
        lgs = vector<T>(n + 1);
        for (int i = 0; i < n; i++)
            table[i][0] = arr[i];
        for (int i = 2; i <= n; i++)
            lgs[i] = lgs[i / 2] + 1;
        for (int lg = 1; lg <= lgs[n]; lg++)
            for (int i = 0; i + (1 << lg) - 1 < n; i++)
                table[i][lg] = myFunction(table[i][lg - 1], table[i + (1 << (lg - 1))][lg - 1]);
    }
    T get(int l, int r)
    {
        return myFunction(table[l][lgs[r - l + 1]], table[r - (1 << lgs[r - l + 1]) + 1][lgs[r - l + 1]]);
    }
};
SparseTable<int> sp;
vector<int> graph[N];
int first[N];
int eular[2 * N];
int deep[N];
int timer = 0;
void eular_tour(int cur, int par = -1, int depth = 0)
{
    deep[cur] = depth;
    eular[timer] = cur;
    first[cur] = timer++;
    for (auto &ch : graph[cur])
        if (ch != par)
            eular_tour(ch, cur, depth + 1), eular[timer++] = cur;
}
#define getLca(x, y) sp.get(min(first[x], first[y]), max(first[x], first[y]))
#define getDist(x, y) deep[x] + deep[y] - ((deep[getLca(x, y)]) << 1)