import java.util.*;

class Solution {
    
    private static final char[] SERIAL = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    
    public String solution(int n, int t, int m, int p) {
           
        //말할 수 있는 최대 숫자까지 진법변환 해주기
        StringBuilder sb = new StringBuilder();
        int startNum = 0;
        while(sb.length() < (m * t)) {
            sb.append(convert(startNum++, n));
        }
        String sequence = sb.toString();
        
        
        //튜브가 말할 숫자 구하기
        sb = new StringBuilder();
        for(int i = p - 1; i < (m * t); i += m) {
            sb.append(sequence.charAt(i));
        }
        
        return sb.toString();
    }
    
    String convert(int num, int n) {
        Stack<Character> s = new Stack<>();
        int remain;
        do {
            remain = num % n;
            
            s.push(SERIAL[remain]);
            
            num /= n;
        } while(num != 0);
        
        StringBuilder sb = new StringBuilder();
        while(!s.empty()) {
            sb.append(s.pop());   
        }
        return sb.toString();
    }
}

// 진수를 자바의 api 이용해서 구한 풀이
import java.util.*;

class Solution {
    public String solution(int n, int t, int m, int p) {

        StringBuilder sb = new StringBuilder();
        int startNum = 0;
        int turn = 0;
        p--;
        while(t > 0) {
            //n진수로 변환
            String transNum = Integer.toString(startNum, n).toUpperCase();

            for(int i = 0; i <transNum.length(); ++i) {
                if(turn == p) {
                    sb.append(transNum.charAt(i));
                    t--;

                    if(t == 0) {
                        break;
                    }
                }
                turn = (turn + 1) % m;
            }

            startNum++;
        }

        String answer = sb.toString();
        return answer;
    }

}
