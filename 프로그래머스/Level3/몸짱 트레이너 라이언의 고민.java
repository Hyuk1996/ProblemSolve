import java.util.ArrayList;
import java.util.List;

class Solution {

    private static final int LAST_TIME = 1320;

    public int solution(int n, int m, int[][] timetable) {

        int maxConcurrentCustomers = getMaxConcurrentCustomers(timetable);

        if (maxConcurrentCustomers == 1) {
            return 0;
        }
        
        return getMaxDistance(n, m, maxConcurrentCustomers);
    }

    private int getMaxConcurrentCustomers(int[][] timetable) {
        int[] cnt = new int[LAST_TIME + 1];
        for (int[] time : timetable) {
            int start = time[0];
            int end = time[1];

            for (int i = start; i <= end; ++i) {
                cnt[i]++;
            }
        }

        int maxConcurrentCustomer = 0;
        for (int i = 0; i < cnt.length; ++i) {
            if (maxConcurrentCustomer < cnt[i]) {
                maxConcurrentCustomer = cnt[i];
            }
        }
        return maxConcurrentCustomer;
    }

    private int getMaxDistance(int n, int m, int maxConcurrentCustomers) {
        for (int dist = 2 * n - 2; dist > 0; --dist) {
            for (int i = 0; i < n; ++i) {
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
