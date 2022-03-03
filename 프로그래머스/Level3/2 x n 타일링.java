class Solution {
    
    private final int CONST_MOD = (int)(1e9 + 7);
    
    public int solution(int n) {
        int answer = 0;
        
        if(n == 1) {
            return 1;
        } else if(n == 2) {
            return 2;
        } else {
            int[] dp = new int[n + 1];
            dp[1] = 1;
            dp[2] = 2;
            for(int i = 3; i <=n; ++i) {
                dp[i] = (dp[i - 1] + dp[i - 2]) % CONST_MOD;
            }
            return dp[n];
        }

    }
}
