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

/* bfs 활용 */
import java.util.*;

class Solution {
    
    private long[] weights;
    private List<List<Integer>> tree;
    private int[] outDegree;
    
    public long solution(int[] a, int[][] edges) {
        
        weights = Arrays.stream(a).mapToLong(i -> (long)i).toArray();
        if (Arrays.stream(weights).sum() != 0L) {
            return -1;
        }
        
        setTreeAndOutDegree(edges);
        
        return makeWeightToZero();
    }
    
    private void setTreeAndOutDegree(int[][] edges) {
        outDegree = new int[weights.length];
        
        tree = new ArrayList<>();
        for (int i = 0; i < weights.length; ++i) {
            tree.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            int u = edge[0];
            int v = edge[1];
            
            tree.get(u).add(v);
            tree.get(v).add(u);
            
            outDegree[u]++;
            outDegree[v]++;
        } 
    }
    
    private long makeWeightToZero() {
        //위상 정렬 아이디어 활용
        boolean[] isVisited = new boolean[weights.length];
        Queue<Integer> q = new ArrayDeque<>();
        long answer = 0;
        
        for (int i = 0; i < outDegree.length; ++i) {
            if (outDegree[i] == 1) {
                q.offer(i);
            }
        }
        
        while (!q.isEmpty()) {
            int v = q.poll();
            isVisited[v] = true;
            
            for (int i = 0; i < tree.get(v).size(); ++i) {
                int adjV = tree.get(v).get(i);
                if (isVisited[adjV]) {
                    continue;
                }
                
                weights[adjV] += weights[v];
                answer += Math.abs(weights[v]);
                weights[v] = 0;
                
                outDegree[adjV]--;
                if (outDegree[adjV] == 1) {
                    q.offer(adjV);
                }
            }
        }
        return answer;
    }
}
