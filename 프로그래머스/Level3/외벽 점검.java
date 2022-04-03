import java.util.*;

class Solution {
    
    List<List<Integer>> permutations = new ArrayList<>();
    List<int[]> weakList = new ArrayList<>();
    
    public int solution(int n, int[] weak, int[] dist) {
        
        Integer[] tmpDist = Arrays.stream(dist).boxed().toArray(Integer[]::new);
        Arrays.sort(tmpDist, Collections.reverseOrder());
        dist = Arrays.stream(tmpDist).mapToInt(Integer::intValue).toArray();
        
        makeWeakList(weak, n);
        
        for(int answer = 1; answer <= dist.length; ++answer) {
            
            getPermutations(dist, new boolean[answer], new Integer[answer], 0, answer);
            
            for(List<Integer> permutation : permutations) {
                if(isPossible(permutation, dist)) {
                    return answer;
                }
            }
            
            permutations.clear();
        }
        return -1;
    }
    
    void makeWeakList(int[] weak, int n) {
        for(int i = 0; i < weak.length; ++i) {
            int[] line = new int[weak.length];
            int idx = 0;
            
            for(int j = i; j < weak.length; ++j) {
                line[idx++] = weak[j];
            }
            for(int j = 0; j < i; ++j) {
                line[idx++] = weak[j] + n;
            }
            
            weakList.add(line);
        }
    }
    
    void getPermutations(int[] dist, boolean[] isSelected, Integer[] tmp, int depth, int MAX) {
        if(depth == MAX) {
            permutations.add(new ArrayList<>(Arrays.asList(tmp)));
            return;
        }
        
        for(int i = 0; i < MAX; ++i) {
            if(!isSelected[i]) {
                isSelected[i] = true;
                tmp[depth] = i;
                getPermutations(dist, isSelected, tmp, depth + 1, MAX);
                isSelected[i] = false;
            }
        }
    }
    
    boolean isPossible(List<Integer> permutation, int[] dist) {
        
        for(int[] weak : weakList) {
            int weakIdx = 0;
            for(Integer friend : permutation) {
                int left = weak[weakIdx];
                int right = left + dist[friend];
                
                while(weakIdx < weak.length) {
                    if(weak[weakIdx] > right) {
                        break;
                    }
                    weakIdx++;
                }
                
                if(weakIdx == weak.length) {
                    return true;
                }
            }
        }
        return false;
    }
}
