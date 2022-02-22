class Solution {
    public int solution(int[][] triangle) {
        
        int h = triangle.length;
        int[][] dp = new int[h][h];
        bottomUp(dp, triangle, h);
        
        int maxSum = Integer.MIN_VALUE;
        for(int i = 0; i < h; ++i) {
            maxSum = Math.max(maxSum, dp[h - 1][i]);
        }
        return maxSum;
    }
    
    private void bottomUp(int[][] dp, int[][] triangle, int h) {
        dp[0][0] = triangle[0][0];
        for(int i = 1; i < h; ++i) {
            for(int j = 0; j <= i; ++j) {
                if(j == 0) {
                    dp[i][j] = dp[i - 1][j];
                } else if(j == i) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = Math.max(dp[i - 1][j - 1], dp[i - 1][j]);
                }
                dp[i][j] += triangle[i][j];
            }
        }
    }
}

//top-down 풀이 (재귀이용)
class Solution {
    
    private int[][] cache;
    
    public int solution(int[][] triangle) {
        
        int h = triangle.length;
        cache = new int[h][h];
        
        int answer = 0;
        for(int i = 0; i < h; ++i) {
            answer = Math.max(answer, topDown(triangle, h - 1, i));
        }
        return answer;
    }
    
    private int topDown(int[][] triangle, int height, int row) {
        //baseCase
        if(height == 0) {
            return triangle[0][0];
        }
        
        if(row == 0) {
            if(cache[height - 1][row] == 0) {
                cache[height - 1][row] = topDown(triangle, height - 1, row);
            }
            return cache[height - 1][row] + triangle[height][row];
        } else if(row == height) {
            if(cache[height - 1][row - 1] == 0) {
                cache[height - 1][row - 1] = topDown(triangle, height - 1, row - 1);
            }
            return cache[height - 1][row - 1] + triangle[height][row];
        } else {
            if(cache[height - 1][row - 1] == 0) {
                cache[height - 1][row - 1] = topDown(triangle, height - 1, row - 1);
            }
            if(cache[height - 1][row] == 0) {
                cache[height - 1][row] = topDown(triangle, height - 1, row);
            }
            
            return Math.max(cache[height - 1][row - 1], cache[height - 1][row]) + triangle[height][row];
        }
    }
}
