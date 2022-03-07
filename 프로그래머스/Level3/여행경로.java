import java.util.*;

class Solution {
    
    Map<String, List<String>> graph;
    Map<String, List<Boolean>> isVisited;
    List<String> path;
    
    public String[] solution(String[][] tickets) {
        
        //그래프 만들기.
        makeGraph(tickets);
        
        //탐색 전 필요한 변수 설정.
        isVisited = new HashMap<>();
        for(String key : graph.keySet()) {
            int edgeCnt = graph.get(key).size();
            List<Boolean> list = new ArrayList<>();
            for(int i = 0; i < edgeCnt; ++i) {
                list.add(false);
            }
            isVisited.put(key, list);
        }
        path = new ArrayList<>();
        path.add("ICN");
        
        //탐색
        dfs("ICN",1 + tickets.length);
        
        String[] answer = new String[path.size()];
        path.toArray(answer);
        return answer;
    }
    
    void makeGraph(String[][] tickets) {
        graph = new HashMap<>();
        for(int i = 0; i < tickets.length; ++i) {
            if(!graph.containsKey(tickets[i][0])) {
                graph.put(tickets[i][0], new ArrayList<>());
            }
            List<String> list = graph.get(tickets[i][0]);
            list.add(tickets[i][1]);
        }
        
        // 인접 정점을 알파벳 순으로 정렬
        for(String key : graph.keySet()) {
            List<String> list = graph.get(key);
            Collections.sort(list);
        }
    }
    
    boolean dfs(String v, int max) {
        //탐색 종료.
        if(path.size() == max) {
            return true;
        }
        
        //탐색
        if(!graph.containsKey(v)) {
            return false;
        }
        for(int i = 0; i < graph.get(v).size(); ++i) {
            if(!isVisited.get(v).get(i)) {
                isVisited.get(v).set(i, true);
                String nextV = graph.get(v).get(i);
                path.add(nextV);
                if(dfs(nextV, max)) {
                    return true;
                }
                path.remove(path.size() - 1);
                isVisited.get(v).set(i, false);
            }
        }
        return false;
    }
}
