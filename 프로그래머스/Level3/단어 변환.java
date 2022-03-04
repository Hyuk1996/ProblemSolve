import java.util.*;

class Solution {
    public int solution(String begin, String target, String[] words) {
        //bfs
        boolean[] isVisited = new boolean[words.length];
        Queue<String> q = new LinkedList<>();
        
        q.add(begin);
        int depth = 0;
        while(!q.isEmpty()) {
            int qSize = q.size();
            depth++;
            
            for(int i = 0; i < qSize; ++i) {
                String curWord = q.poll();
                
                for(int j = 0; j < words.length; ++j) {
                    if(!isVisited[j] && canChange(curWord, words[j])) {
                        if(words[j].equals(target)) {
                            return depth;
                        }
                        isVisited[j] = true;
                        q.add(words[j]);
                    }
                }
            }
        }
        return 0;
    }
    
    boolean canChange(String a, String b) {
        int diffCnt = 0;
        for(int i = 0; i < a.length(); ++i) {
            if(a.charAt(i) != b.charAt(i)) {
                diffCnt++;
            }
        }
        return (diffCnt == 1)? true : false;
    }

}

//DFS
class Solution {
    
    int answer = Integer.MAX_VALUE;
    boolean[] isVisited;
    
    public int solution(String begin, String target, String[] words) {
        
        isVisited = new boolean[words.length];
        dfs(words, begin, 0, target);
        return (answer == Integer.MAX_VALUE)? 0 : answer;
    }
    
    void dfs(String[] words, String curWord, int depth, String target) {
        if(curWord.equals(target)) {
            answer = Math.min(answer, depth);
            return;
        }
        
        for(int i = 0; i < words.length; ++i) {
            if(!isVisited[i] && canChange(curWord, words[i])) {
                isVisited[i] = true;
                dfs(words, words[i], depth + 1, target);
                isVisited[i] = false;
            }
        }
    }
    
    boolean canChange(String a, String b) {
        int diffCnt = 0;
        for(int i = 0; i < a.length(); ++i) {
            if(a.charAt(i) != b.charAt(i)) {
                diffCnt++;
            }
        }
        return (diffCnt == 1)? true : false;
    }
}
