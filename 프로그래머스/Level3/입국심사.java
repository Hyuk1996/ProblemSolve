class Solution {

    private int n;
    private int[] times;

    public long solution(int n, int[] times) {

        long min = 1;
        long max = (long)(1e9) * n;

        this.n = n;
        this.times = times;

        return binarySearch(min, max);
    }

    private long binarySearch(long min, long max) {
        long lo = 0;
        long hi = max;
        long mid;
        while(lo + 1 < hi) {
            mid = lo + (hi - lo) / 2;
            if(possible(mid)) {
                hi = mid;
            } else {
                lo = mid;
            }
        }
        return hi;
    }

    private boolean possible(long hour) {
        long cnt = 0;
        for(int time : times) {
            cnt += hour / time;
        }
        return cnt >= n;
    }
}
