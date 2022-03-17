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
