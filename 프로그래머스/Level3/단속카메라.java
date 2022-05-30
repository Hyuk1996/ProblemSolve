import java.util.Arrays;

class Solution {

    private static final int MIN = -30001;

    public int solution(int[][] routes) {

        Arrays.sort(routes, (o1, o2) -> {
            if(o1[1] == o2[1]) {
                return Integer.compare(o1[0], o2[0]);
            }
            return Integer.compare(o1[1], o2[1]);
        });

        int answer = 0;
        int end = MIN;
        for(int[] route : routes) {
            if(route[0] > end) {
                ++answer;
                end = route[1];
            }
        }
        return answer;
    }
}
