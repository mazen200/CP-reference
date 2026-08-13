ll myFunction(ll a,ll b){
    return a;
}
struct SparseTable {
    vector<vector<ll>> table;
    vector<int> lgs;

    SparseTable(vector<ll>& arr) {
        int n = arr.size();
        table = vector<vector<ll>>(n + 1, vector<ll>(20));
        lgs = vector<int>(n + 1);

        for (int i = 0; i < n; i++)
            table[i][0] = arr[i];
        for (int i = 2; i <= n; i++)
            lgs[i] = lgs[i / 2] + 1;
        for (int lg = 1; lg <= lgs[n]; lg++)
            for (int i = 0; i + (1ll << lg) - 1 < n; i++)
                table[i][lg] =
                    myFunction(table[i][lg - 1], table[i + (1ll << (lg - 1))][lg - 1]);
    }

    ll get(int l, int r) {
        return myFunction(table[l][lgs[r - l + 1]],
                          table[r - (1 << lgs[r - l + 1]) + 1][lgs[r - l + 1]]);
    }
};