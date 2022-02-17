//up-down
class Solution {
    
    private final int MOD = 1234567;
    int[] cache;
    
    
    public int solution(int n) {
        
        cache = new int[n + 1]; 
        return fibonacci(n);
    }
    
    int fibonacci(int n) {
        //base case
        if(n < 2) {
            return n;
        }
        
        if(cache[n - 1] == 0) {
            cache[n - 1] = fibonacci(n - 1);
        }
        if(cache[n - 2] == 0) {
            cache[n - 2] = fibonacci(n - 2);
        }
        return (cache[n - 2] + cache[ n - 1]) % MOD;
    }
}

//bottom-up
class Solution {

    private final int MOD = 1234567;

    public int solution(int n) {

        int[] fibonacci = new int[n + 1];
        fibonacci[0] = 0;
        fibonacci[1] = 1;
        for(int i = 2; i <= n; ++i) {
            fibonacci[i] = (fibonacci[i - 1] + fibonacci[i - 2]) % MOD;
        }

        return fibonacci[n];
    }
}
