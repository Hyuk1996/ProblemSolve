import java.util.*;

class Solution {
    
    private List<List<Integer>> graph;
    
    public int solution(int n, int[][] edge) {
        
        makeGraph(n, edge);
        
        int[] dist = new int[n + 1];
        bfs(dist);
        
        return getAnswer(dist);
    }
    
    private void makeGraph(int n, int[][] edge) {
        graph = new ArrayList<>();
        for(int i = 0; i <= n; ++i) {
            graph.add(new ArrayList<>());
        }
        
        int u, v;
        for(int i = 0; i < edge.length; ++i) {
            u = edge[i][0];
            v = edge[i][1];
            
            graph.get(u).add(v);
            graph.get(v).add(u);
        }
    }
    
    private void bfs(int[] dist) {
        Queue<Integer> q = new LinkedList<>();
        
        q.add(1);
        while(!q.isEmpty()) {
            int v = q.poll();
            
            for(int i = 0; i < graph.get(v).size(); ++i) {
                int adjV = graph.get(v).get(i);
                if(dist[adjV] == 0) {
                    dist[adjV] = dist[v] + 1;
                    q.add(adjV);
                }
            }
        }
    }
    
    private int getAnswer(int[] dist) {
        int answer = 0;
        int maxDist = 0;
        for(int i = 2; i < dist.length; ++i) {
            if(maxDist < dist[i]) {
                maxDist = dist[i];
                answer = 1;
            } else if(maxDist == dist[i]) {
                answer++;
            }
        }
        return answer;
    }
}
