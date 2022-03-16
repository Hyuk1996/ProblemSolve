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
