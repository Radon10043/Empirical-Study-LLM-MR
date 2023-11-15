#include<vector>
#include<string>

 int numDistinct(std::string s, std::string t) {
        int m = s.size(), n = t.size();
        std::vector< std::vector<long> > dp(n + 1, std::vector<long>(m + 1));
        for (int j = 0; j <= m; ++j) dp[0][j] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                dp[i][j] = dp[i][j - 1] + (t[i - 1] == s[j - 1] ? dp[i - 1][j - 1] : 0);
            }
        }
        return dp[n][m];
}
