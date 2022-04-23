import java.util.*;

class Solution {
    public String[] solution(String[] s) {
        
        String[] answer = new String[s.length];
        int idx = 0;
        
        for(String x : s) {
            answer[idx++] = updateX(x);
        }
        
        return answer;
    }
    
    String updateX(String x) {
        StringBuilder sb = new StringBuilder();
        StringBuilder tmp = new StringBuilder();
        for(int i = 0; i < x.length(); ++i) {
            sb.append(x.charAt(i));
            
            if(sb.length() >= 3) {
                if(sb.substring(sb.length() - 3, sb.length()).equals("110")) {
                    sb.delete(sb.length() - 3, sb.length());
                    tmp.append("110");
                }
            }
        }
        
        int index = -1;
        for(int i = sb.length() - 1; i >= 0; --i) {
            if(sb.charAt(i) == '0') {
                index = i + 1;
                break;
            }
        }
        
        
        if(index != -1) {
            sb.insert(index, tmp.toString());
        } else {
            sb.insert(0, tmp.toString());
        }
        return sb.toString();
    }
    
}
