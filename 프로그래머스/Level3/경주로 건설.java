import java.util.*;

class Solution {
    
    final int[] dr = {0, 1, 0, -1};
    final int[] dc = {1, 0, -1, 0};
    
    public int solution(int[][] board) {
        
        int N = board.length;
        int[][][] dp = new int[N][N][4];
        init(dp, N);
        
        //BFS
        Queue<Tuple> q = new LinkedList<>();
        
        q.add(new Tuple(0, 0, 0));
        for(int i = 0; i < 4; ++i) {
            dp[0][0][i] = 0;
        }
        while(!q.isEmpty()) {
            Tuple t = q.poll();
            
            for(int i = 0; i < 4; ++i) {
                int nextR = t.r + dr[i];
                int nextC = t.c + dc[i];
                int dir = i;
                int cost;
                
                if(t.r == 0 && t.c == 0) {
                    cost = 100;
                } else {
                    if((t.d % 2) == (i % 2)) {
                        cost = 100;
                    } else {
                        cost = 600;
                    }
                }
                
                if(nextR < 0 || nextR >= N || nextC < 0 || nextC >= N) {
                    continue;
                }
                if(board[nextR][nextC] == 1) {
                    continue;
                }
                
                if(dp[t.r][t.c][t.d] + cost < dp[nextR][nextC][dir]) {
                    dp[nextR][nextC][dir] = dp[t.r][t.c][t.d] + cost;
                    q.add(new Tuple(nextR, nextC, dir));
                }
            }
        }
        
        int answer = Integer.MAX_VALUE;
        for(int i = 0; i < 4; ++i) {
            answer = Math.min(answer, dp[N - 1][N - 1][i]);
        }
        return answer;
    }
    
    void init(int[][][] dp, int N) {
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                for(int k = 0; k < 4; ++k) {
                    dp[i][j][k] = Integer.MAX_VALUE;
                }
            }
        }
    }
    
    class Tuple {
        int r, c, d;
        
        Tuple(int r, int c, int d) {
            this.r = r;
            this.c = c;
            this.d = d;
        }
    }
}

//DFS + DP
import java.util.*;

class Solution {
    
    final int[] dr = {0, 1, 0, -1};
    final int[] dc = {1, 0, -1, 0};
    int[][][] dp;
    
    public int solution(int[][] board) {
        
        int N = board.length;
        initDp(N);
        
        dfs(0, 0, 0, board, N);
        
        int answer = Integer.MAX_VALUE;
        for(int i = 0; i < 4; ++i) {
            answer = Math.min(answer, dp[N - 1][N - 1][i]);
        }
        return answer;
    }
    
    void dfs(int r, int c, int d, int[][] board, int N) {
        for(int i = 0; i < 4; ++i) {
            int nextR = r + dr[i];
            int nextC = c + dc[i];
            int cost;
            if(r == 0 && c == 0) {
                cost = 100;
            } else {
                if((d % 2) == (i % 2)) {
                    cost = 100;
                } else {
                    cost = 600;
                }
            }
            
            if(nextR < 0 || nextR >= N || nextC < 0 || nextC >= N) {
                continue;
            }
            if(board[nextR][nextC] == 1) {
                continue;
            }
            
            if(dp[r][c][d] + cost < dp[nextR][nextC][i]) {
                dp[nextR][nextC][i] = dp[r][c][d] + cost;
                dfs(nextR, nextC, i, board, N);
            }
        }
    }
    
    void initDp(int N) {
        dp = new int[N][N][4];
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                for(int k = 0; k < 4; ++k) {
                    dp[i][j][k] = Integer.MAX_VALUE;
                }
            }
        }
        
        for(int k = 0; k < 4; ++k) {
            dp[0][0][k] = 0;
        }
    }
}
