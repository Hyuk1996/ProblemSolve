import java.util.*;

class Solution {
    
    List<Node>[] graph;
    
    public int solution(int n, int[][] costs) {
        
        graph = makeGraph(n, costs);
        
        return prim();
    }
    
    List<Node>[] makeGraph(int n, int[][] costs) {
        List<Node>[] graph = new ArrayList[n];
        for(int i = 0; i < n; ++i) {
            graph[i] = new ArrayList<>();
        }
        
        int u, v, w;
        for(int i = 0; i < costs.length; ++i) {
            u = costs[i][0];
            v = costs[i][1];
            w = costs[i][2];
            
            graph[u].add(new Node(v, w));
            graph[v].add(new Node(u, w));
        }
        
        return graph;
    }
    
    int prim() {
        boolean[] isSelected = new boolean[graph.length];
        PriorityQueue<Node> pq = new PriorityQueue<>(new Comparator<Node>() {
            @Override
            public int compare(Node o1, Node o2) {
                return o1.w - o2.w;
            }
        });
        int totalWeight = 0;
        
        pq.add(new Node(0, 0));
        while(!pq.isEmpty()) {
            Node node = pq.poll();
            if(isSelected[node.v]) {
                continue;
            }
            
            isSelected[node.v] = true;
            totalWeight += node.w;
            
            for(int i = 0; i < graph[node.v].size(); ++i) {
                int adjV = graph[node.v].get(i).v;
                int weight = graph[node.v].get(i).w;
                if(!isSelected[adjV]) {
                    pq.add(new Node(adjV, weight));
                }
            }
        }
        return totalWeight;
    }
    
    class Node {
        int v;
        int w;
        
        Node(int v, int w) {
            this.v = v;
            this.w = w;
        }
    }
}

//Kruskal 풀이
import java.util.*;

class Solution {
    public int solution(int n, int[][] costs) {
        
        //간선 배열을 가중치 기준으로 정렬
        Arrays.sort(costs, new Comparator<int[]>() {
            @Override
            public int compare(int[] o1, int[] o2) {
                return o1[2] - o2[2];
            }
        });
        
        DisjointSet set = new DisjointSet(n);
        int totalWeight = 0;
        int edgeCnt = 0;
        int u, v, w;
        for(int i = 0; i < costs.length; ++i) {
            u = costs[i][0];
            v = costs[i][1];
            w = costs[i][2];
            
            if(set.find(u) == set.find(v)) {
                continue;
            }
            set.merge(u, v);
            edgeCnt++;
            totalWeight += w;
        }
        
        return totalWeight;
    }
    
    class DisjointSet {
        int[] parent;
        
        DisjointSet(int n) {
            parent = new int[n];
            for(int i = 0; i < n; ++i) {
                parent[i] = i;
            }
        }
        
        int find(int v) {
            if(parent[v] == v) {
                return v;
            }
            return parent[v] = find(parent[v]); //경로압축
        }
        
        void merge(int u, int v) {
            int rootU = find(u);
            int rootV = find(v);
            
            if(rootU == rootV) {
                return;
            }
            parent[rootV] = rootU;
        }
    }
}
