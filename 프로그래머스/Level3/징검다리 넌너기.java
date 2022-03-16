class Solution {
    
    final int MAX = (int)(2e8 + 1);
    
    public int solution(int[] stones, int k) {
        
        int lo = 1;
        int hi = MAX;
        
        while(lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;
            if(check(mid, stones, k)) { //mid명이 징검다리를 건널 수 있는 경우
                lo = mid;
            } else { //mid명이 징검다리를 건널 수 없는 경우
                hi = mid;
            }
        }
        
        return lo;
    }
    
    boolean check(int mid, int[] stones, int k) {
        int tmp[] = new int[stones.length];
        for(int i = 0; i < stones.length; ++i) {
            tmp[i] = stones[i] - (mid - 1);
        }
        
        int maxEmptyLen = 0;
        int emptyLen = 0;
        for(int i = 0; i < tmp.length; ++i) {
            if(tmp[i] <= 0) {
                emptyLen++;
            } else {
                maxEmptyLen = Math.max(maxEmptyLen, emptyLen);
                emptyLen = 0;
            }
        }
        maxEmptyLen = Math.max(maxEmptyLen, emptyLen);
        
        return maxEmptyLen < k;
    }
}

//윈도우를 활용한 풀이
import java.util.*;

class Solution {
    public int solution(int[] stones, int k) {
        int answer = Integer.MAX_VALUE;
        
        Deque<Stone> window = new ArrayDeque<>();
        for(int i = 0; i < stones.length; ++i) {
            Stone stone = new Stone(i, stones[i]);
            
            //window의 스톤 개수가 k가 넘을 경우
            if(!window.isEmpty() && window.getFirst().idx <= i - k) {
                window.poll();
            }
            
            //window에서 자기보다 작은 값은 삭제
            while(!window.isEmpty() && window.getLast().val <= stone.val) {
                window.removeLast();
            }
            
            window.addLast(stone);
            
            //해당 윈도우에서 최대값과 정답을 비교
            if(answer > window.getFirst().val && i >= k - 1) {
                answer = window.getFirst().val;
            }
        }
        
        return answer;
    }
    
    class Stone {
        int idx;
        int val;
        
        Stone (int idx, int val) {
            this.idx = idx;
            this.val = val;
        }
    }
}
