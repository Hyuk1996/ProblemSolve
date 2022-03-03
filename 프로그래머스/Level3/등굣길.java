class Solution {
    
    final int CONST_MOD = (int)(1e9 + 7);
    final int INF = Integer.MAX_VALUE;
    
    public int solution(int m, int n, int[][] puddles) {
        int answer = 0;
        
        int[][] dp = new int[n + 1][m + 1];
        
        //dp 초기화
        dp[1][1] = 1;
        for(int i = 0; i < puddles.length; ++i) {
            dp[puddles[i][1]][puddles[i][0]] = INF;
        }
        
        
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <=m; ++j) {
                if((i == 1 && j == 1) || dp[i][j] == INF) {
                    continue;
                }
                
                if(dp[i - 1][j] != INF) {
                    dp[i][j] += dp[i - 1][j];
                }
                if(dp[i][j - 1] != INF) {
                    dp[i][j] = (dp[i][j] + dp[i][j - 1]) % CONST_MOD;
                }
            }   
        }
        
        return dp[n][m];
    }
}
