class Solution {
public:
    
    int maxTotalReward(vector<int>& a) {
        int n = a.size();
        a.push_back(-1);
        sort(a.begin(), a.end());
        const int MX = 1e5;
        bitset<MX> dp, allones;
        dp[0] = 1;
        int j = 0;
        for(int i = 1; i <= n; i++)
        {
            // for(int j = 0; j < MX; j++)
            // {
            //     dp[i][j] = dp[i - 1][j];
            //     if(2 * a[i] > j and j - a[i]>=0 )
            //     dp[i][j] = max(dp[i][j], dp[i - 1][j - a[i]] + a[i]);
            // }
            while(a[i] != j)
                allones[j++]=1;
            dp |= ((dp & allones) << a[i]);
        }
        for(int i = MX - 1; ~i; i--)
            if(dp[i])
                return i;
        return 0;
    }
};