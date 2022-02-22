class Solution {
    public int solution(int n, int[][] computers) {
        
        boolean[] isVisited = new boolean[n];
        int networkCnt = 0;
        for(int i = 0; i < n; ++i) {
            if(!isVisited[i]) {
                dfs(computers, i, isVisited);
                networkCnt++;
            }
        }
        return networkCnt;
    }
    
    private void dfs(int[][] computers, int v, boolean[] isVisited) {
        isVisited[v] = true;
        
        for(int i = 0; i < computers.length; ++i) {
            if(i == v || computers[v][i] == 0) {
                continue;
            }
            int adjV = i;
            if(!isVisited[i]) {
                dfs(computers, adjV, isVisited);
            }
        }
    }
}

import java.util.*;

class Solution {
    public int solution(int n, int[][] computers) {
        
        int networkCnt = 0;
        boolean[] isVisited = new boolean[n];
        for(int i = 0; i < n; ++i) {
            if(!isVisited[i]) {
                networkCnt++;
                bfs(computers, isVisited, i);
            }
        }
        return networkCnt;
    }
    
    private void bfs(int[][] computers, boolean[] isVisited, int start) {
        Queue<Integer> q = new LinkedList<>();
        
        q.add(start);
        isVisited[start] = true;
        while(!q.isEmpty()) {
            int v = q.poll();
            for(int i = 0; i < computers.length; ++i) {
                if(computers[v][i] == 1 && !isVisited[i]) {
                    q.add(i);
                    isVisited[i] = true;
                }
            }
        }
    }
}
