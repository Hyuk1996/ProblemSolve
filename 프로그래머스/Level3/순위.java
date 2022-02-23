import java.util.*;

class Solution {
    
    private List<List<Integer>> graph;
    private int[] win;
    private int[] lose;
    private int winCnt;
    
    public int solution(int n, int[][] results) {
        
        makeGraph(n, results);
        
        win = new int[n + 1];
        lose = new int[n + 1];
        
        //각 정점을 시작점으로 DFS 순회하면서, 자기보다 못하는 선수 카운트
        for(int i = 1; i <= n; ++i) {
            boolean[] isVisited = new boolean[n + 1];
            winCnt = 0;
            dfs(i, isVisited);
            
            win[i] = winCnt;
        }
        
        int answer = 0;
        for(int i = 1; i <= n; ++i) {
            if(win[i] + lose[i] == (n - 1)) {
                answer++;
            }
        }
        return answer;
    }
    
    private void makeGraph(int n, int[][] results) {
        graph = new ArrayList<>();
        for(int i = 0; i <= n; ++i) {
            graph.add(new ArrayList<>());
        }
        
        for(int i = 0; i < results.length; ++i) {
            graph.get(results[i][0]).add(results[i][1]);
        }
    }
    
    private void dfs(int v, boolean[] isVisited) {
        isVisited[v] = true;
        
        for(int i = 0; i < graph.get(v).size(); ++i) {
            int adjV = graph.get(v).get(i);
            if(!isVisited[adjV]) {
                lose[adjV]++; // 자기보다 잘하는 선수 카운트
                winCnt++;
                dfs(adjV, isVisited);
            }
        }
    }
}


//플로이드 와셔 풀이
class Solution {
    
    private boolean[][] graph;
    
    public int solution(int n, int[][] results) {
        int answer = 0;
        
        makeGraph(n, results);
        
        floydWarshall(n);
        
        for(int i = 1; i <= n; ++i) {
            boolean isAnswer = true;
            for(int j = 1; j <= n; ++j) { 
                if(i != j && !graph[i][j] && !graph[j][i]) {
                    isAnswer = false;
                    break;
                }
            }
            if(isAnswer) {
                answer++;
            }
        }
        return answer;
    }
    
    private void makeGraph(int n, int[][] results) {
        graph = new boolean[n + 1][n + 1];
        
        for(int i = 0; i < results.length; ++i) {
            graph[results[i][0]][results[i][1]] = true;
        }
    }
    
    private void floydWarshall(int n) {
        for(int k = 1; k <= n; ++k) {
            for(int i = 1; i <= n; ++i) {
                for(int j = 1; j <= n; ++j) {
                    if(i == k || j == k || i == j) {
                        continue;
                    }
                    
                    if(graph[i][k] && graph[k][j]) {
                        graph[i][j] = true;
                    }
                }
            }
        }
    }
}
