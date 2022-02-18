class Solution {
    public int solution(int[] arr) {
        int answer = divideConquer(arr, 0, arr.length - 1);
        return answer;
    }
    
    int divideConquer(int[] arr, int left, int right) {
        if(left == right) {
            return arr[left];
        }
        
        int mid = (left + right) / 2;
        int LCM1 = divideConquer(arr, left, mid);
        int LCM2 = divideConquer(arr, mid + 1, right);
        
        int LCM = getLCM(LCM1, LCM2);
        return LCM;
    }
    
    int getLCM(int a, int b) {
        if(a < b) {
            int tmp = a;
            a = b;
            b = tmp;
        }
        int GCD = getGCD(a, b);
        a /= GCD;
        return a * b;
    }
    
    int getGCD(int a, int b) {
        int r;
        while(true) {
            r = a % b;
            if(r == 0) {
                return b;
            }
            a = b;
            b = r;
        }
    }
    
}
