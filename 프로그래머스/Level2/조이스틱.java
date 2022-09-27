/* dfs */
class Solution {
    
    private char[] nameArr;
    private int answer = Integer.MAX_VALUE;
    
    public int solution(String name) {
    
        nameArr = name.toCharArray();
        
        int changeCnt = 0;
        for (char c : nameArr) {
            if (c != 'A') {
                changeCnt++;
            }
        }
        
        dfs(0, 0, 0, changeCnt);
        
        return answer;
    }
    
    private void dfs(int depth, int moveCnt, int cursor, int maxDepth) {
        if (maxDepth == depth) {
            answer = Math.min(moveCnt, answer);
            return;
        }
        
        int rightCnt = 0;
        int rightCursor = cursor;
        while (nameArr[rightCursor] == 'A') {
            rightCursor = (rightCursor + 1) % nameArr.length;
            rightCnt++;
        }
        
        int leftCnt = 0;
        int leftCursor = cursor;
        while (nameArr[leftCursor] == 'A') {
            leftCursor--;
            if (leftCursor == -1) {
                leftCursor = nameArr.length - 1;
            }
            leftCnt++;
        }
        
        rightCnt += Math.min(nameArr[rightCursor] - 'A', 'Z' - nameArr[rightCursor] + 1);
        char rightPrev = nameArr[rightCursor];
        nameArr[rightCursor] = 'A';
        dfs(depth + 1, moveCnt + rightCnt, rightCursor, maxDepth);
        nameArr[rightCursor] = rightPrev;
        
        leftCnt += Math.min(nameArr[leftCursor] - 'A', 'Z' - nameArr[leftCursor] + 1);
        char leftPrev = nameArr[leftCursor];
        nameArr[leftCursor] = 'A';
        dfs(depth + 1, moveCnt + leftCnt, leftCursor, maxDepth);
        nameArr[leftCursor] = leftPrev;
    }
}

/* 가능한 경우의 수 구해 판단 (구현) */
class Solution {
    public int solution(String name) {
        
        int upDownCnt = 0;
        for (char c : name.toCharArray()) {
            upDownCnt += Math.min(c - 'A', 'Z' - c + 1);
        }
        
        int minRightLeftCnt = name.length() - 1;
        for (int i = 0; i < name.length(); ++i) {
            int index = i + 1;
            while (index < name.length() && name.charAt(index) == 'A') {
                index++;
            }
            
            minRightLeftCnt = Math.min(minRightLeftCnt, i * 2 + name.length() - index);
            minRightLeftCnt = Math.min(minRightLeftCnt, (name.length() - index) * 2 + i);
        }
        
        int answer = upDownCnt + minRightLeftCnt;
        return answer;
    }
}
