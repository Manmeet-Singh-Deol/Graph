class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        vector<int> suffix(n+1, 0);
        for (int i = n-1; i >= 0; i--) {
            suffix[i] = suffix[i+1] + piles[i];
        }

        vector<vector<int>> dp(n+1, vector<int>(n+1, 0));

        function<int(int,int)> solve = [&](int i, int m) {
            if (i >= n) return 0;
            if (dp[i][m] != 0) return dp[i][m];
            if (i + 2*m >= n) return suffix[i]; // can take all remaining

            int best = 0;
            for (int x = 1; x <= 2*m; x++) {
                best = max(best, suffix[i] - solve(i+x, max(m, x)));
            }
            return dp[i][m] = best;
        };

        return solve(0, 1);
    }
};
