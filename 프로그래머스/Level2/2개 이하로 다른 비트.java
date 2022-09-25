class Solution {
    public long[] solution(long[] numbers) {
        long[] answer = new long[numbers.length];
        for (int i = 0; i < numbers.length; ++i) {
            long number = numbers[i];
            
            long tmp = 1L;
            while ((number & tmp) != 0) {
                tmp <<= 1;
            }
            
            /* 가장 처음 나오는 0 -> 1 */
            number |= tmp;
            /* 0 오른쪽 1 -> 0 */
            number &= ~(tmp >> 1);
            
            answer[i] = number;
        }
        
        return answer;
    }
}
