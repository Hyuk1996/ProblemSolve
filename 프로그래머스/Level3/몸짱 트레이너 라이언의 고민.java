import java.util.ArrayList;
import java.util.List;

class Solution {

    private static final int LAST_TIME = 1320;
    private static final int START_TIME = 600;

    public int solution(int n, int m, int[][] timetable) {

        int maxConcurrentCustomers = getMaxConcurrentCustomers(timetable);
        if (maxConcurrentCustomers == 1) {
            return 0;
        }

        return getMaxDistance(n, m, maxConcurrentCustomers);
    }

    private int getMaxConcurrentCustomers(int[][] timetable) {
        int[] cnt = new int[LAST_TIME + 2];
        for (int[] time : timetable) {
            cnt[time[0]]++;
            cnt[time[1] + 1]--;
        }

        int maxConcurrentCustomers = 0;
        int curConcurrentCustomers = 0;
        for (int i = START_TIME; i <= LAST_TIME; ++i) {
            curConcurrentCustomers += cnt[i];
            maxConcurrentCustomers = Math.max(maxConcurrentCustomers, curConcurrentCustomers);
        }
        return maxConcurrentCustomers;
    }

    private int getMaxDistance(int n, int m, int maxConcurrentCustomers) {
        for (int dist = 2 * n - 2; dist > 0; --dist) {
            for (int i = 0; i <= n / 2; ++i) {
                List<Pos> customers = new ArrayList<>();
                for (int y = 0; y < n; ++y) {
                    for (int x = 0; x < n; ++x) {
                        if (y == 0 && x < i) {
                            continue;
                        }

                        boolean check = true;
                        for (Pos pos : customers) {
                            int tmp = Math.abs(pos.y - y) + Math.abs(pos.x - x);
                            if (tmp < dist) {
                                check = false;
                                break;
                            }
                        }

                        if (check) {
                            customers.add(new Pos(x, y));
                            if (customers.size() == maxConcurrentCustomers) {
                                return dist;
                            }
                        }
                    }
                }
            }
        }
        return -1;
    }

    static class Pos {

        int x;
        int y;

        Pos(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
}
