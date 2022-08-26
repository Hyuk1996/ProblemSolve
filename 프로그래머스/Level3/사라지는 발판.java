class Solution {
    
    int[] dr = {-1, 0, 1, 0};
    int[] dc = {0, -1, 0, 1};
    
    static class Result {
        boolean win;
        int count;
        
        Result(boolean win, int count) {
            this.win = win;
            this.count = count;
        }
    }
    
    public int solution(int[][] board, int[] aloc, int[] bloc) {
        Result result = game(board, aloc[0], aloc[1], bloc[0], bloc[1], 0);
        return result.count;
    }
    
    Result game(int[][] board, int myR, int myC, int otherR, int otherC, int curCount) {    
        //base case
        if (isGameEnd(board, myR, myC)) {
            return new Result(false, curCount);
        }
        
        boolean win = false;
        int maxCount = Integer.MIN_VALUE;
        int minCount = Integer.MAX_VALUE;
        
        for (int i = 0; i < 4; ++i) {
            int nextR = myR + dr[i];
            int nextC = myC + dc[i];
                
            if (canMove(board, nextR, nextC)) {
                board[myR][myC] = 0;
                Result result = game(board, otherR, otherC, nextR, nextC, curCount + 1);
                board[myR][myC] = 1;
                    
                win |= (!result.win);
                
                if (!result.win) {
                    minCount = Math.min(minCount, result.count);
                } else {
                    maxCount = Math.max(maxCount, result.count);
                }
            }
        }

        return new Result(win, win ? minCount : maxCount);
    }
    
    boolean isGameEnd(int[][] board, int r, int c) {
        if (board[r][c] == 0) {
            return true;
        }
        
        for (int i = 0; i < 4; ++i) {
            int nextR = r + dr[i];
            int nextC = c + dc[i];
            if (canMove(board, nextR, nextC)) {
                return false;
            }
        }
        return true;
    }
    
    boolean canMove(int[][] board, int r, int c) {
        if (r < 0 || r >= board.length || c < 0 || c >= board[0].length || board[r][c] == 0) {
            return false;
        }
        return true;
    }
}
