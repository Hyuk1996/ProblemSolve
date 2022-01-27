import java.util.*;

class Solution {
    public int solution(String skill, String[] skill_trees) {
        int answer = 0;
        
        Map<Character, Integer> dict = getDict(skill);
        
        for(int i=0; i < skill_trees.length; ++i) { 
            if(isPossible(skill_trees[i], dict)) {
                answer++;
            }
        }
        
        return answer;
    }
    
    private Map<Character, Integer> getDict(String skill) {
        Map<Character, Integer> dict = new HashMap<>();
        for(int i = 0; i < skill.length(); ++i) {
            dict.put(skill.charAt(i), i);
        }
        return dict;
    }
    
    private boolean isPossible(String skill_tree, Map<Character, Integer> dict) {
        int recentPriority = -1;
        
        for(int i=0; i < skill_tree.length(); ++i) {
            Integer priority = dict.get(skill_tree.charAt(i));
            if(priority == null) {
                continue;
            } else {
                if(priority == recentPriority + 1) {
                    recentPriority = priority;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
    
}

//간결하지만 수행시간은 오래걸리는 풀이
class Solution {
    public int solution(String skill, String[] skill_trees) {
        int answer = 0;
        
        for(String skill_tree : skill_trees) {
            if(skill.indexOf(skill_tree.replaceAll("[^"+ skill + "]", "")) == 0) {
                answer++;
            }
        }
        return answer;
    }
}
