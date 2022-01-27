class Solution {
    
    private int zeroCnt = 0;
    private int oneCnt = 0;
    
    public int[] solution(int[][] arr) {
        
        recursive(arr, 0, 0, arr.length);
        
        int[] answer = {this.zeroCnt, this.oneCnt};
        return answer;
    }
    
    private void recursive(int[][] arr, int r, int c, int length) {
        
        if(canCompress(arr, r, c, length)) {
            if(arr[r][c] == 0) {
                zeroCnt++;
            } else {
                oneCnt++;
            }
            return;
        }
        
        int nextLength = length / 2;
        for(int i = r; i < (r + length); i += nextLength) {
            for(int j = c; j < (c + length); j += nextLength) {
                recursive(arr, i, j, nextLength);
            }
        }
    }
    
    private boolean canCompress(int[][] arr, int r, int c, int length) {
        int initNum = arr[r][c];
        for(int i = r; i < (r + length); ++i) {
            for(int j = c; j < (c + length); ++j) {
                if(initNum != arr[i][j]) {
                    return false;
                }
            }
        }
        return true;
    } 
}
