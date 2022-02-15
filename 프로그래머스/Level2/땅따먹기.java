import java.util.*;

class Solution {
    int solution(int[][] land) {

        int N = land.length;

        int[][] dp = new int[N][4];
        for(int i = 0; i < 4; ++i) {
            dp[0][i] = land[0][i];
        }
        
        for(int i = 1; i < N; ++i) {
            for(int j = 0; j < 4; ++j) {
                for(int k = 0; k < 4; ++k) {
                    if(k == j) {
                        continue;
                    }
                    dp[i][j] = Math.max(dp[i][j], dp[i - 1][k]);
                }
                dp[i][j] += land[i][j];
            }
        }

        int answer = 0;
        for(int i = 0; i < 4; ++i) {
            answer = Math.max(answer, dp[N - 1][i]);
        }
        return answer;
    }
}
