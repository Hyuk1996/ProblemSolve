class Solution {
    
    private final int CONST_MOD = (int)(1e9 + 7);
    
    public int solution(int n) {
        int answer = 0;
        
        if(n == 1) {
            return 1;
        } else if(n == 2) {
            return 2;
        } else {
            int[] dp = new int[n + 1];
            dp[1] = 1;
            dp[2] = 2;
            for(int i = 3; i <=n; ++i) {
                dp[i] = (dp[i - 1] + dp[i - 2]) % CONST_MOD;
            }
            return dp[n];
        }

    }
}

//메모리사용 최적화 풀이
class Solution {
    
    final int CONST_MOD = (int)(1e9 + 7);
    
    public int solution(int n) {
        int answer = 0;
        
        int a = 1;
        int b = 2;
        if(n == 1) {
            return a;
        } else if(n == 2) {
            return b;
        } else {
            for(int i = 3; i <=n; ++i) {
                answer = (a + b) % CONST_MOD;
                a = b;
                b = answer;
            }
            return answer;
        }
    }
}

//up-down 풀이
class Solution {
    
    int[] cache;
    final int CONST = (int)(1e9 + 7);
    
    public int solution(int n) {
        
        cache = new int[n + 1];
        return recursive(n);
    }
    
    int recursive(int n) {
        if(n <= 2) {
            return n;
        }
        
        if(cache[n - 1] == 0) {
            cache[n - 1] = recursive(n - 1);
        }
        if(cache[n - 2] == 0) {
            cache[n - 2] = recursive(n - 2);
        }
        
        return cache[n] = (cache[n - 1] + cache[n - 2]) % CONST;
    }
}
