import java.util.*;

class Solution {
    public int solution(int N, int[][] road, int K) {
        
        //그래프 표현하기
        List<List<Node>> graph = new ArrayList<>();
        for(int i = 0; i <= N; ++i) {
            graph.add(new ArrayList<>());
        }
        
        int a, b, c;
        for(int[] info : road) {
            a = info[0];
            b = info[1];
            c = info[2];
        
            graph.get(a).add(new Node(b, c));
            graph.get(b).add(new Node(a, c));
        }
        
        //다익스트라 이용해 최단거리 구하기
        int[] dist = new int[N + 1];
        Arrays.fill(dist, Integer.MAX_VALUE);
        
        Queue<Node> pq = new PriorityQueue<>((n1, n2) -> Integer.compare(n1.w, n2.w));
        pq.offer(new Node(1, 0));
        dist[1] = 0;
        while (!pq.isEmpty()) {
            Node node = pq.poll();
            int vertex = node.v;
            int totalWeight = node.w;
            
            if(totalWeight > dist[vertex]) {
                continue;
            }
            
            for(int i = 0; i < graph.get(vertex).size(); ++i) {
                int adjVertex = graph.get(vertex).get(i).v;
                int weight = graph.get(vertex).get(i).w;
                
                if(dist[adjVertex] > totalWeight + weight) {
                    dist[adjVertex] = totalWeight + weight;
                    pq.add(new Node(adjVertex, dist[adjVertex]));
                }
            }
        }        
        
        //정답 구하기 (1 포함)
        int answer = 0;
        for(int i = 1; i <= N; ++i) {
            if(dist[i] <= K) {
                ++answer;
            }
        }
        return answer;
    }
    
    static class Node {
        
        int v;
        int w;
        
        Node(int v, int w) {
            this.v = v;
            this.w = w;
        }
    }
}
