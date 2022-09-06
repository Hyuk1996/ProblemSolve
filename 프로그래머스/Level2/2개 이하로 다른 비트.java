class Solution {
    public long[] solution(long[] numbers) {

        long[] answer = new long[numbers.length];

        long f;
        for (int i = 0; i < numbers.length; ++i) {

            long tmp = 1L;
            while ((numbers[i] & tmp) == tmp) {
                tmp = tmp << 1;
            }

            f = (numbers[i] | tmp);

            tmp = (tmp >> 1);
            tmp = (~tmp);
            f = (f & tmp);

            answer[i] = f;
        }
        return answer;
    }
}
