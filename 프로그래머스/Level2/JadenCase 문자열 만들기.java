class Solution {
    public String solution(String s) {
       
        boolean isFirstChar = true;
        StringBuilder sb = new StringBuilder();
        
        for(int i = 0; i < s.length(); ++i) {
            if(s.charAt(i) == ' ') {
                sb.append(' ');
                isFirstChar = true;
                continue;
            }
            
            if(isFirstChar) {
                sb.append(Character.toUpperCase(s.charAt(i)));
                isFirstChar = false;
            } else {
                sb.append(Character.toLowerCase(s.charAt(i)));
            }
        }
        
        String answer = sb.toString();
        return answer;
    }
}
