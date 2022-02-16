class Solution {
    public int solution(int n) {
        int answer = 0;
        
        for(int i = 1; i <= n; ++i) {
            if(recursiveSum(i, i, n) == n) {
                answer++;
            }
        }
        return answer;
    }
    
    int recursiveSum(int curNum, int curSum, int n) {
        if(curSum >= n) {
            return curSum;
        }
        
        curNum++;
        curSum += curNum;
        return recursiveSum(curNum, curSum, n);
    }
}
