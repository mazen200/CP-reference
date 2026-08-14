struct HK
{
    vector<vector<int>> adjList;
    vector<int> BtoA;
    HK(int n, int m)
    {
        adjList = vector<vector<int>>(n);
        BtoA = vector<int>(m, -1);
    }
    bool dfs(int a, int L, vector<int> &A, vector<int> &B)
    {
        if (A[a] != L)
            return 0;
        A[a] = -1;
        for (auto b : adjList[a])
        {
            if (B[b] == L + 1)
            {
                B[b] = 0;
                if (BtoA[b] == -1 or dfs(BtoA[b], L + 1, A, B))
                {
                    BtoA[b] = a;
                    return 1;
                }
            }
        }
        return 0;
    }
    inline void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
    }
    inline int maxMatching()
    {
        int res = 0;
        vector<int> A(adjList.size()), B(BtoA.size()), cur, next;
        while (true)
        {
            fill(all(A), 0);
            fill(all(B), 0);
            cur.clear();
            for (auto a : BtoA)
                if (~a)
                    A[a] = -1;
            for (int a = 0; a < adjList.size(); a++)
                if (!A[a])
                    cur.push_back(a);
            for (int lay = 1;; lay++)
            {
                bool islast = 0;
                next.clear();
                for (auto a : cur)
                    for (auto b : adjList[a])
                    {
                        if (BtoA[b] == -1)
                            B[b] = lay, islast = 1;
                        else if (BtoA[b] != a and !B[b])
                            B[b] = lay, next.push_back(BtoA[b]);
                    }
                if (islast)
                    break;
                if (next.empty())
                    return res;
                for (auto a : next)
                    A[a] = lay;
                cur.swap(next);
            }
            for (int a = 0; a < adjList.size(); a++)
                res += dfs(a, 0, A, B);
        }
    }
};
