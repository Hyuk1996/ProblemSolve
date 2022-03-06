class Solution {
    
    int MOD = 20170805;
    
    public int solution(int m, int n, int[][] cityMap) {
        
        int[][] dp = new int[m][n];
        dp[0][0] = 1;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if((i == 0 && j == 0) || cityMap[i][j] != 0) {
                    continue;
                }
                
                if(i - 1 >= 0) {
                    if(cityMap[i - 1][j] != 2) {
                        dp[i][j] += dp[i - 1][j];
                    } else {
                        int curI = i - 1;
                        while(true) {
                            curI--;
                            if((curI < 0) || cityMap[curI][j] != 2) {
                                break;
                            }
                        }
                        
                        if(curI >= 0) {
                            dp[i][j] += dp[curI][j];
                        } 
                    }
                }
                
                if(j - 1 >= 0) {
                    if(cityMap[i][j - 1] != 2) {
                        dp[i][j] += dp[i][j - 1];
                    } else {
                        int curJ = j - 1;
                        while(true) {
                            curJ--;
                            if((curJ < 0) || cityMap[i][curJ] != 2) {
                                break;
                            }
                        }
                        
                        if(curJ >= 0) {
                            dp[i][j] += dp[i][curJ];
                        }
                    }
                }
                
                dp[i][j] %= MOD;
            }
        }
        
        int answer = dp[m - 1][n - 1];
        return answer;
    }
}
