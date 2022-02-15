class Solution {
    public int solution(int n, int k) {
        int answer = 0;
        
        //n을 k진수로 변환
        String transN = Integer.toString(n, k);
        
        String[] tokens = transN.split("0");
        for(String token : tokens) {
            if(token.isEmpty()) {
                continue;
            }
            if(isPrime(Long.parseLong(token))) {
                answer++;
            }
        }
        
        return answer;
    }
    
    boolean isPrime(long num) {
        if(num == 1) {
            return false;
        }
        
        for(long i = 2; i <= Math.sqrt(num); ++i) {
            if(num % i == 0) {
                return false;
            }
        }
        return true;
    }
}
