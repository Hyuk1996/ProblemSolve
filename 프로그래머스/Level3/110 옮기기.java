class Solution {
    
    private static final String ONE_ONE_ZERO = "110";
    private static final char ZERO = '0';
    
    public String[] solution(String[] s) {
        
        String[] answer = new String[s.length];
        for (int i = 0; i < s.length; ++i) {
            String x = s[i];
            answer[i] = renewX(x);
        }
        return answer;
    }
    
    private String renewX(String x) {
        
        StringBuilder newX = new StringBuilder();
        int cnt = 0;

        //"110" 제거하기
        for (char c : x.toCharArray()) {
            newX.append(c);
                
            if (newX.length() >= 3) {
                if (newX.indexOf(ONE_ONE_ZERO, newX.length() - 3) != -1) {
                    newX.delete(newX.length() - 3, newX.length());
                    cnt++;
                }
            }
        }
        
        //"110" 규칙에 맞게 삽입하기
        int insertIdx = 0;
        for (int j = newX.length() - 1; j >= 0; j--) {
            if (newX.charAt(j) == ZERO) {
                insertIdx = j + 1;
                break;
            }
        }
        
        newX.insert(insertIdx, ONE_ONE_ZERO.repeat(cnt));
        return newX.toString();
    }
}
