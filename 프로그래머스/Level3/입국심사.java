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

//재귀 풀이
class Solution {

    private int n;
    private int[] times;

    public long solution(int n, int[] times) {

        long min = 0;
        long max = (long)(1e9) * n;

        this.n = n;
        this.times = times;

        return binarySearch(min, max);
    }

    private long binarySearch(long lo, long hi) {
        if(lo + 1 == hi) {
            return hi;
        }
        
        long mid = lo + (hi - lo) / 2;
        if(possible(mid)) {
            return binarySearch(lo, mid);
        } else {
            return binarySearch(mid, hi);
        }
    }

    private boolean possible(long hour) {
        long cnt = 0;
        for(int time : times) {
            cnt += hour / time;
        }
        return cnt >= n;
    }
}

//우선수위 큐 & 최적해 이용한 풀이
import java.util.Comparator;
import java.util.PriorityQueue;

class Solution {

    public long solution(int n, int[] times) {

        //심사관이 동시에 심사를 진행할 때, 분당 처리할 수 있는 손님 수 구하기
        double vel = 0;
        for (int t : times) {
            vel += 1D / t;
        }

        //최적의 심사시간 구하기
        double optimalTime = n / vel;

        System.out.println(optimalTime);

        //우선순위 큐 이용 실제 가능시간 구하기
        PriorityQueue<long[]> pq = new PriorityQueue<>(
            Comparator.comparingLong(arr -> arr[0] + arr[1]));

        for(int t : times) {
            long cnt = (long)optimalTime / t;
            pq.add(new long[]{t, cnt * t});
            n -= cnt;
        }

        long answer = (long)optimalTime;
        for(int i = 0; i < n; ++i) {
            long[] a = pq.poll();
            a[1] += a[0];
            pq.offer(a);
            answer = a[1];
        }
        return answer;
    }
}
