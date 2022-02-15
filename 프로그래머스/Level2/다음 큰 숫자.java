class Solution {
    public int solution(int n) {
        
        int nOneCnt = getOneCnt(n);
        int answer = n + 1;
        
        while(true) {
            if(nOneCnt == getOneCnt(answer)) {
                break;
            }
            answer++;
        }
        
        return answer;
    }
    
    int getOneCnt(int n) {
        int oneCnt = 0;
        do {
            if(n % 2 == 1) {
                oneCnt++;
            }
            n /= 2;
        } while(n != 0);
        return oneCnt;
    }
}
