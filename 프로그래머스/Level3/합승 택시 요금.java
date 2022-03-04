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

//다익스트라 풀이
import java.util.*;

class Solution {
    
    private int INF;
    
    List<List<Node>> graph;
    
    public int solution(int n, int s, int a, int b, int[][] fares) {
        
        INF = 100000 * n;
        makeGraph(n, fares);
        
        int[] startADist = dijkstra(s, n);
        int[] startBDist = dijkstra(a, n);
        int[] startSDist = dijkstra(b, n);
        
        int answer = 100000 * n * 2;
        for(int i = 1; i <= n; ++i) {
            answer = Math.min(answer, startSDist[i] + startADist[i] + startBDist[i]); //양방향 그래프라 가능한 풀이.
        }
        return answer;
    }
    
    void makeGraph(int n, int[][] fares) {
        graph = new ArrayList<>();
        for(int i = 0; i <= n; ++i) {
            graph.add(new ArrayList<>());
        }
        
        int c, d, f;
        for(int i = 0; i < fares.length; ++i) {
            c = fares[i][0];
            d = fares[i][1];
            f = fares[i][2];
            
            graph.get(c).add(new Node(d, f));
            graph.get(d).add(new Node(c, f));
        }
    }
    
    int[] dijkstra(int startV, int n) {
        PriorityQueue<Node> pq = new PriorityQueue<>();
        int[] dist = new int[n + 1];
        Arrays.fill(dist, INF);
        
        dist[startV] = 0;
        pq.add(new Node(startV, 0));
        while(!pq.isEmpty()) {
            int curV = pq.peek().v;
            int curDist = pq.peek().w;
            pq.remove();
            
            if(curDist > dist[curV]) {
                continue;
            }
            for(int i = 0; i < graph.get(curV).size(); ++i) {
                int nextV = graph.get(curV).get(i).v;
                int weight = graph.get(curV).get(i).w;
                
                if(curDist + weight < dist[nextV]) {
                    dist[nextV] = curDist + weight;
                    pq.add(new Node(nextV, dist[nextV]));
                }
            }
        }
        return dist;
    }
    
    class Node implements Comparable<Node> {
        int v;
        int w;
        
        Node(int v, int w) {
            this.v = v;
            this.w = w;
        }
        
        @Override
        public int compareTo(Node o) {
            if(this.w > o.w) {
                return 1;
            } else if (this.w == o.w) {
                return 0;
            } else {
                return -1;
            }
        }
    }
}
