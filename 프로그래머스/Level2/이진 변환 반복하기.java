class Solution {
    
    private int removeZeroCnt = 0;
    
    public int[] solution(String s) {
        
        int binaryChangeCnt = 0;
        
        while(true) {
            binaryChangeCnt++;
            s = binaryChange(s);
            if(s.equals("1")) {
                break;
            }
        }
        int[] answer = {binaryChangeCnt, removeZeroCnt};
        return answer;
    }
    
    private String binaryChange(String s) {
        int prevLen = s.length();
        s = s.replaceAll("0", "");
        int len = s.length();
        
        removeZeroCnt += (prevLen - len);
        
        return Integer.toBinaryString(len);
    }
}
