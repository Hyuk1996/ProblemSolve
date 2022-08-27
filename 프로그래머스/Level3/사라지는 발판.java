class Solution {
    
    int[] dr = {-1, 0, 1, 0};
    int[] dc = {0, -1, 0, 1};
    
    public int solution(int[][] board, int[] aloc, int[] bloc) {   
        return game(board, aloc, bloc, 0).count;
    }
    
    Result game(int[][] board, int[] myloc, int[] enemyloc, int count) {
        if (isPlayerLose(board, myloc)) {
            return new Result(false, count);
        }
        
        boolean isWin = false;
        int minCount = Integer.MAX_VALUE;
        int maxCount = Integer.MIN_VALUE;
        
        for (int i = 0; i < 4; ++i) {
            int nextR = myloc[0] + dr[i];
            int nextC = myloc[1] + dc[i];
            if (isValidLoc(board, nextR, nextC)) {
                board[myloc[0]][myloc[1]] = 0;
                Result enemyResult = game(board, enemyloc, new int[]{nextR, nextC}, count + 1);
                board[myloc[0]][myloc[1]] = 1;
                        
                isWin |= !enemyResult.isWin;
                if (!enemyResult.isWin) {
                    minCount = Math.min(minCount, enemyResult.count);
                } else {
                    maxCount = Math.max(maxCount, enemyResult.count);
                }
            }
        }
        
        return new Result(isWin, isWin ? minCount : maxCount);
    }
    
    boolean isPlayerLose(int[][] board, int[] loc) {
        //현재 발판 없음
        if (board[loc[0]][loc[1]] == 0) {
            return true;
        }
        
        //더 이상 이동할 수 없음
        for (int i = 0; i < 4; ++i) {
            int nextR = loc[0] + dr[i];
            int nextC = loc[1] + dc[i];
            if (isValidLoc(board, nextR, nextC)) {
                return false;
            }
        }
        return true;
    }
    
    boolean isValidLoc(int[][] board, int r, int c) {
        return 0 <= r && r < board.length && 0 <= c && c < board[0].length && board[r][c] == 1;
    }
    
    static class Result {
        boolean isWin;
        int count;
        
        Result(boolean isWin, int count) {
            this.isWin = isWin;
            this.count = count;
        }
    } 
}
