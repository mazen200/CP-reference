struct BiMatching {
    vector<int> colAssign;
    vector<int> vis;
    vector<vector<int>> adjMat;
    int n, m;

    BiMatching(int n, int m) : n(n), m(m) {
        adjMat = vector<vector<int>>(n, vector<int>(m));
        colAssign = vector<int>(m, -1);
    }

    bool canMatch(int i) {
        for (int j = 0; j < m; j++) {
            if (adjMat[i][j] && !vis[j]) {
                vis[j] = 1;
                if (colAssign[j] == -1 || canMatch(colAssign[j])) {
                    colAssign[j] = i;
                    return true;
                }
            }
        }
        return false;
    }

    void addEdge(int u, int v) {
        adjMat[u][v] = 1;
    }

    int maxMatching() {
        int maxFlow = 0;
        for (int i = 0; i < n; i++) {
            vis = vector<int>(m, 0);
            if (canMatch(i))
                maxFlow++;
        }
        return maxFlow;
    }
};