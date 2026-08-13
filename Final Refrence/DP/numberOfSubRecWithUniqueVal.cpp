vector<vector<int>> height(n, vector<int>(m, 1)); // num of elements top of a[i]
[j] that equal to it
    vector<vector<int>>
        dp(n, vector<int>(m, 0)); // num of subrectangles that
a[i][j] is its bottom right corner
    // setting height for each element
    for (int i = 1; i < n; i++)
{
    for (int j = 0; j < m; j++)
    {
        if (a[i][j] == a[i - 1][j])
            height[i][j] += height[i - 1][j];
    }
}
for (int i = 0; i < n; i++)
{
    vector<int> st;
    for (int j = 0; j < m; j++)
    {
        int k = -1;
        while (st.size())
        {
            int col = st.back();
            if (a[i][col] != a[i][j] || height[i][col] < height[i][j])
                break;
            st.pop_back();
        }
        // if k = -1: means that all colums behind: same element and their hieght > height[i][j]
        // if k = val: means that all columns between [k+1:j] are valid
        // k = val because of: a[i][k]!=a[i][j] or height[i][k] < height[i][j]
        if (st.size())
            k = st.back();
        // each col in [k+1:j] has at least height[i][j], so all of them can end
        at a[i][j] as bot - right corner
                                dp[i][j] = height[i][j] * (j - k);
        if (k != -1)
        {
            // here: k = val because of height[i][k] < height[i][j]
            // so all subrectangles that endes at i,k -> can end at i,j. As
            height[i][k] < height[i][j] if (a[i][j] == a[i][k])
                               dp[i][j] += dp[i][k];
        }
        st.push_back(j);
    }
}