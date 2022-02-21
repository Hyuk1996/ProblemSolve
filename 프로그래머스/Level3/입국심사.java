class Solution {
    public long solution(int n, int[] times) {
        long answer = 0;
        
        long maxTime = getMaxTime(times);
        
        //총 걸리는 심사시간을 기준으로 이분탐색을 통해 최소 시간 찾기.
        long leftT = 0;
        long rightT = maxTime * n;
        long midT;
        while(leftT + 1 < rightT) {
            midT = leftT + (rightT - leftT) / 2;
            //현재 추측 시간에 검사받을 수 있는 사람 수 계산하기.
            long cnt = calCnt(times, midT);

            if(cnt < n) {
                leftT = midT;
            } else {
                rightT = midT;
            }
        }
        answer = rightT;
        return answer;
    }
    
    int getMaxTime(int[] times) {
        int maxTime = 0;
        for(int i = 0; i < times.length; ++i) {
            maxTime = Math.max(maxTime, times[i]);
        }
        return maxTime;
    }
    
    long calCnt(int[] times, long midT) {
        long cnt = 0;
        for(int i = 0; i < times.length; ++i) {
            cnt += midT / times[i];
        }
        return cnt;
    }
}
