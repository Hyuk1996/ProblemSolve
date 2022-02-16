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

// 반복문 버전
class Solution {
    public int solution(int n) {
        int answer = 0;
        
        int num, sum;
        for(int i = 1; i <= n; ++i) {
            num = i;
            sum = i;
            while(true) {
                if(sum >= n) {
                    break;
                }
                num++;
                sum += num;
            }
            
            if(sum == n) {
                answer++;
            }
        }
        return answer;
    }
}

//정수론을 이용한 풀이
class Solution {
    public int solution(int n) {
        int answer = 0;
        for(int i = 1; i <= n; i += 2) {
            if(n % i == 0) {
                ++answer;
            }
        }
        return answer;
    }
}
