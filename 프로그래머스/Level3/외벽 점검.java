import java.util.*;

class Solution {
    
    List<List<Integer>> permutations = new ArrayList<>();
    
    public int solution(int n, int[] weak, int[] dist) {
        
        //친구들의 모든 수열 구하기 ex 1명 , 2명 순열, 3명 순열 ... 8명 순열
        boolean[] isSelected = new boolean[dist.length];
        Integer[] permutation = new Integer[dist.length];
        for(int i = 1; i <= dist.length; ++i) {
            dfs(dist, isSelected, permutation, 0, i);
        }
        
       
        //구한 친구 조합으로 모든 취약점을 조사할 수 있는지 체크
        int answer = Integer.MAX_VALUE;
        for(List<Integer> order : permutations) {
            if(possible(weak, n, dist, order)) {
                return order.size();
            }
        }
        
        return -1;
    }
    
    boolean possible(int[] weak, int n, int[] dist, List<Integer> order) {
        int[] line = new int[weak.length];
        int idx = 0;
        
        //원을 특정 점을 기준으로 직선으로 만들기
        for(int i = 0; i < weak.length; ++i) {
            idx = 0;
            
            for(int j = i; j < weak.length; ++j) {
                line[idx++] = weak[j];
            }
            
            for(int j = 0; j < i; ++j) {
                line[idx++] = weak[j] + n;
            }
            
            idx = 0;
            
            //취약점 모두 체크 가능한지 판단
            for(Integer friend : order) {
                int start = line[idx];
                int end = start + dist[friend];
                
                for(int j = start; j <= end; ++j) {
                    if(line[idx] == j) {
                        idx++;
                        if(idx >= weak.length) {
                            break;
                        }
                    }
                }
                
                if(idx >= weak.length) {
                    return true;
                }
            }
        }
        return false;
    }
    
    void dfs(int[] dist, boolean[] isSelected, Integer[] permutation, int depth, int max) {
        if(depth == max) {
            permutations.add(toList(permutation, depth));
            return;
        }
        
        for(int i = 0; i < dist.length; ++i) {
            if(!isSelected[i]) {
                isSelected[i] = true;
                permutation[depth] = i;
                dfs(dist, isSelected, permutation, depth + 1, max);
                isSelected[i] = false;
            }
        }
    }
    
    List<Integer> toList(Integer[] permutation, int size) {
        List<Integer> list = new ArrayList<>();
        for(int i = 0; i < size; ++i) {
            list.add(permutation[i]);
        }
        return list;
    }
}
