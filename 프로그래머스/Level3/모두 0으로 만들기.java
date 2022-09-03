import java.util.*;

class Solution {

    private List<List<Integer>> tree;
    private long answer = 0;
    private long [] weights;
    private boolean[] isVisited;

    public long solution(int[] a, int[][] edges) {

        weights = Arrays.stream(a).mapToLong(i -> (long)i).toArray();

        //모든 정점의 가중치를 0으로 만들 수 있는지 판별
        if (Arrays.stream(weights).sum() != 0L) {
            return -1;
        }

        //그래프 구현
        tree = setTree(a.length, edges);
        
        isVisited = new boolean[tree.size()];
        dfs(0);

        return answer;
    }
    
    private List<List<Integer>> setTree(int vertexCnt, int[][] edges) {
        
        List<List<Integer>> tree = new ArrayList<>();
        for (int i = 0; i < vertexCnt; ++i) {
            tree.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            int u = edge[0];
            int v = edge[1];

            tree.get(u).add(v);
            tree.get(v).add(u);
        }
        return tree;
    }

    private void dfs(int v) {

        isVisited[v] = true;

        for (int i = 0; i < tree.get(v).size(); ++i) {
            int adjV = tree.get(v).get(i);

            if (!isVisited[adjV]) {
                
                dfs(adjV);
                
                answer += Math.abs(weights[adjV]);
                weights[v] += weights[adjV];
                weights[adjV] = 0;
            }       
        }
    }
}

//위상 정렬 이용
import java.util.*;

class Solution {
    
    ArrayList<Integer>[] graph;
    int[] edgeCnt;
    long[] weights;
    
    public long solution(int[] a, int[][] edges) {
        
        //가중치들을 0으로 만들 수 없는 경우
        if(Arrays.stream(a).sum() != 0) {
            return -1;
        }
        
        graph = makeGraph(a.length, edges);
        edgeCnt = init(); //위상정렬을 위한 정보
        weights = intToLong(a);
        
        //위상정렬 순서대로 가중치 분산
        return topologicalSort();
    }
    
    ArrayList<Integer>[] makeGraph(int n, int[][] edges) {
        ArrayList<Integer>[] graph = new ArrayList[n];
        for(int i = 0; i < n; ++i) {
            graph[i] = new ArrayList<>();
        }
        
        int u, v;
        for(int i = 0; i < edges.length; ++i) {
            u = edges[i][0];
            v = edges[i][1];
            
            graph[u].add(v);
            graph[v].add(u);
        }
        return graph;
    }
    
    long[] intToLong(int[] a) {
        long[] weights = new long[a.length];
        for(int i = 0; i < a.length; ++i) {
            weights[i] = a[i];
        }
        return weights;
    }
    
    int[] init() {
        int[] edgeCnt = new int[graph.length];
        for(int i = 0; i < graph.length; ++i) {
            edgeCnt[i] = graph[i].size();
        }
        return edgeCnt;
    }
    
    long topologicalSort() {
        
        Queue<Integer> q = new LinkedList<>();
        boolean[] isVisited = new boolean[graph.length];
        long moveCnt = 0;
        
        for(int i = 0; i < edgeCnt.length; ++i) {
            if(edgeCnt[i] == 1) {
                q.add(i);
            }
        }
        
        while(!q.isEmpty()) {
            int from = q.poll();
            isVisited[from] = true;
            
            for(int i = 0; i < graph[from].size(); ++i) {
                int to = graph[from].get(i);
                if(isVisited[to]) {
                    continue;
                }
                
                //가중치 분산
                edgeCnt[to]--;
                weights[to] += weights[from];
                moveCnt += Math.abs(weights[from]);
                weights[from] = 0;
                
                if(edgeCnt[to] == 1) {
                    q.add(to);
                }
            }
        }
        
        return moveCnt;
    }
    
}
