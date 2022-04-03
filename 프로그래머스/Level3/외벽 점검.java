import java.util.*;

class Solution {
    
    List<List<Integer>> permutations = new ArrayList<>(); 
    
    public int solution(int n, int[] weak, int[] dist) {
        
        for(int answer = 1; answer <= dist.length; ++answer) {
            
            boolean[] isSelected = new boolean[dist.length];
            Integer[] tmp = new Integer[answer];
            getPermutations(dist, isSelected, tmp, 0, answer);
            
            for(List<Integer> permutation : permutations) {
                if(isPossible(permutation, dist, weak, n)) {
                    return answer;
                }
            }
            
            permutations.clear();
        }
        
        return -1;
    }
    
    void getPermutations(int[] dist, boolean[] isSelected, Integer[] tmp, int depth, int MAX) {
        if(depth == MAX) {
            permutations.add(new ArrayList<>(Arrays.asList(tmp)));
            return;
        }
        
        for(int i = 0; i < dist.length; ++i) {
            if(!isSelected[i]) {
                isSelected[i] = true;
                tmp[depth] = i;
                getPermutations(dist, isSelected, tmp, depth + 1, MAX);
                isSelected[i] = false;
            }
        }
    }
    
    boolean isPossible(List<Integer> permutation, int[] dist, int[] weak, int n) {
        int[] line = new int[weak.length];
        int idx = 0;
        for(int i = 0; i < weak.length; ++i) {
            idx = 0;
            for(int j = i; j < weak.length; ++j) {
                line[idx++] = weak[j];
            }
            for(int j = 0; j < i; ++j) {
                line[idx++] = weak[j] + n;
            }
            
            idx = 0;
            for(Integer friend : permutation) {
                int left = line[idx];
                int right = left + dist[friend];
                
                
                while(idx < line.length) {
                    if(line[idx] > right) {
                        break;
                    }
                    idx++;
                }
                
                if(idx == line.length) {
                    return true;
                }
            }
        }
        return false;
    }
}
