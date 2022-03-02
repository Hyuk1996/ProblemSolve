class Solution {
    
    private final long MAX_T = (long)1e15;
    int a, b;
    int[] g, s, w, t;
    
    
    public long solution(int a, int b, int[] g, int[] s, int[] w, int[] t) {
        
        init(a, b, g, s, w, t);
        
        long lo = 0;
        long hi = MAX_T;
        long mid;
        while(lo + 1 < hi) {
            mid = lo + (hi - lo) / 2;
            if(canCarry(mid)) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        
        return hi;
    }
    
    void init(int a, int b, int[]g, int[] s, int[] w, int[] t) {
        this.a = a;
        this.b = b;
        this.g = g;
        this.s = s;
        this.w = w;
        this.t = t;
    }
    
    boolean canCarry(long time) {
        
        int cityCnt = g.length;
        long carryCnt, maxW, restW;
        
        long maxGoldSum = 0;
        long minSilverSum = 0;
        long minGoldSum = 0;
        long maxSilverSum = 0;
        
        for(int i = 0; i < cityCnt; ++i) {
        
            //주어진 시간안에 운반가능 횟수 계산
            carryCnt = ((time % (t[i] * 2)) >= t[i])? time / (t[i] * 2) + 1 : time / (t[i] * 2);
            
            //주어진 시간안에 최대로 옮기는 있는 광물 양.
            maxW = carryCnt * w[i];
            
            //금을 우선적으로 가져오는 경우.
            long maxGold = 0;
            long minSilver = 0;
            if(maxW <= g[i]) {
                maxGold = maxW;
            } else {
                maxGold = g[i];
                restW = maxW - maxGold;
                
                if(restW <= s[i]) {
                    minSilver = restW;
                } else {
                    minSilver = s[i];
                }
            }
            maxGoldSum += maxGold;
            minSilverSum += minSilver;
            
            //은을 우선적으로 가져오는 경우
            long minGold = 0;
            long maxSilver = 0;
            if(maxW <= s[i]) {
                maxSilver = maxW;
            } else {
                maxSilver = s[i];
                restW = maxW - maxSilver;
                
                if(restW <= g[i]) {
                    minGold = restW;
                } else {
                    minGold = g[i];
                }
            }
            minGoldSum += minGold;
            maxSilverSum += maxSilver;
        }
        
        if(a <= maxGoldSum && b <= maxSilverSum && a + b <= minGoldSum + maxSilverSum) {
            return true;
        } else {
            return false;
        }
    }
}
