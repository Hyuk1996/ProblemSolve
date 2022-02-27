import java.util.*;

class Solution {
    public int[] solution(String[] gems) {
        
        int jewelTypeCnt = getJewelTypeCnt(gems);
        
        //슬라이딩 윈도우로 구간 구하기
        int[] answer = new int[2];
        int left = 0, right = 0;
        int range = gems.length + 1;
        Map<String, Integer> jewel = new HashMap<>();
        while(right < gems.length) {
            
            //슬라이딩 윈도우 넓히기
            while(right < gems.length) {
                jewel.put(gems[right], jewel.getOrDefault(gems[right], 0) + 1);
                right++;
                if(jewel.size() == jewelTypeCnt) {
                    break;
                }
            }
            
            while(jewel.size() == jewelTypeCnt) {
                //더 작은 구간을 찾으면 update
                int tmpRange = right - left;
                if(tmpRange < range) {
                    range = tmpRange;
                    answer[0] = left + 1;
                    answer[1] = right;
                }
                
                // 슬라이딩 윈도우 좁히기.
                if(jewel.get(gems[left]) > 1) {
                    jewel.put(gems[left], jewel.get(gems[left]) - 1);
                } else {
                    jewel.remove(gems[left]);
                }
                left++;
            }
        }
        
        return answer;
    }
    
    private int getJewelTypeCnt(String[] gems) {
        Set<String> set = new HashSet<>();
        for(String gem : gems) {
            set.add(gem);
        }
        return set.size();
    }
    
}
