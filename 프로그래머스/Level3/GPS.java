import java.util.*;

class Solution {
    
    final int INF = 101;
    
    public int solution(int n, int m, int[][] edge_list, int k, int[] gps_log) {
        int answer = 0;
        
        boolean[][] graph = makeGraph(n, m, edge_list);
        
        //dp
        int[][] dp = new int[k][n + 1];
        init(dp);
        dp[0][gps_log[0]] = 0;
        for(int i = 1; i < k; ++i) {
            for(int j = 1; j <= n; ++j) {
                
                dp[i][j] = Math.min(dp[i][j], dp[i - 1][j]);
                for(int v = 1; v <= n; ++v) {
                    if(graph[v][j]) {
                        dp[i][j] = Math.min(dp[i][j], dp[i - 1][v]);
                    }
                }
                
                if(j != gps_log[i] && dp[i][j] != INF) {
                    dp[i][j]++;
                } 
            }
        }
        
        answer = (dp[k - 1][gps_log[k - 1]] == INF)? -1 : dp[k - 1][gps_log[k - 1]];
        return answer;
    }
    
    boolean[][] makeGraph(int n, int m, int[][] edge_list) {
        boolean[][] graph = new boolean[n + 1][n + 1];
        int u, v;
        for(int i = 0; i < m; ++i) {
            u = edge_list[i][0];
            v = edge_list[i][1];
            
            graph[u][v] = true;
            graph[v][u] = true;
        }
        return graph;
    }
    
    void init(int[][] dp) {
        for(int i = 0; i < dp.length; ++i) {
            for(int j = 0; j < dp[i].length; ++j) {
                dp[i][j] = INF;
            }
        }
    }
    
}
