class Solution {
    public int[] solution(int n, long left, long right) {

        long diff = right - left + 1L;
        int[] answer = new int[(int)diff];

        int idx = 0;
        for(long i = left; i <= right; ++i) {
            answer[idx++] = (int)Math.max(i / n + 1, i % n + 1);
        }
        return answer;
    }
}
