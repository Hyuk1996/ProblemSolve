import java.util.*;

class Solution {

    List<List<Integer>> graph;
    long[] vertexW;
    boolean[] isVisited;

    long answer = 0;

    public long solution(int[] a, int[][] edges) {

        if(!canMakeZero(a)) {
            return -1;
        }

        makeGraph(a.length, edges);
        vertexW = copyA(a);

        //dfs 이용해 모든 트리 정점 0으로 만들기
        isVisited = new boolean[a.length];
        dfs(0);

        return answer;
    }

    boolean canMakeZero(int[] a) {
        long sum = 0;
        for(int i = 0; i < a.length; ++i) {
            sum += a[i];
        }
        return sum == 0;
    }

    void makeGraph(int n, int[][] edges) {
        graph = new ArrayList<>();
        for(int i = 0; i < n; ++i) {
            graph.add(new ArrayList<>());
        }

        int u, v;
        for(int i = 0; i < edges.length; ++i) {
            u = edges[i][0];
            v = edges[i][1];
            graph.get(u).add(v);
            graph.get(v).add(u);
        }
    }

    long[] copyA(int[] a) {
        long[] tmp = new long[a.length];
        for(int i = 0; i < a.length; ++i) {
            tmp[i] = (long) a[i];
        }
        return tmp;
    }

    void dfs(int v) {
        isVisited[v] = true;
        int parent = -1;
        for(int i = 0; i < graph.get(v).size(); ++i) {
            int adjV = graph.get(v).get(i);
            if(isVisited[adjV]) {
                parent = adjV;
                continue;
            }
            dfs(adjV);
        }

        if(parent == -1) { //부모가 없는 경우(루트노드)
            return;
        }

        answer += Math.abs(vertexW[v]);
        vertexW[parent] += vertexW[v];
        vertexW[v] = 0;
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
