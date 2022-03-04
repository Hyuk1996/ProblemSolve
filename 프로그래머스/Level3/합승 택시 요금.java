class Solution {
    
    int[][] dist;
    final int INF = Integer.MAX_VALUE;
    
    public int solution(int n, int s, int a, int b, int[][] fares) {
        
        initDist(n, fares);
        
        floyidWarshall(n);
        
        return getMinFare(n, s, a, b);
    }
    
    void initDist(int n, int[][]fares) {
        dist = new int[n + 1][n + 1];
        for(int i = 0; i <=n; ++i) {
            for(int j = 0; j <= n; ++j) {
                if(i == j) {
                    dist[i][j] = 0;
                } else {
                    dist[i][j] = INF;
                }
            }
        }
        
        int c, d, f;
        for(int i = 0; i < fares.length; ++i) {
            c = fares[i][0];
            d = fares[i][1];
            f = fares[i][2];
            
            dist[c][d] = f;
            dist[d][c] = f;
        }
    }
    
    void floyidWarshall(int n) {
        for(int k = 1; k <= n; ++k) {
            for(int i = 1; i <= n; ++i) {
                for(int j = 1; j <= n; ++j) {
                    if(i == j || i == k || j == k) {
                        continue;
                    }
                    
                    if(dist[i][k] != INF && dist[k][j] != INF) {
                        dist[i][j] = Math.min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
    }
    
    int getMinFare(int n, int s, int a, int b) {
        int minFare = INF;
        for(int i = 1; i <= n; ++i) {
            if(dist[s][i] == INF || dist[i][a] == INF || dist[i][b] == INF) {
                continue;
            }
            minFare = Math.min(minFare, dist[s][i] + dist[i][a] + dist[i][b]);
        }
        return minFare;
    }
    
}
