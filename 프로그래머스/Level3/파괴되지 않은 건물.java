class Solution {
    public int solution(int[][] board, int[][] skill) {
        
        int[][] change = new int[board.length + 1][board[0].length + 1];
        
        for (int[] s : skill) {
            int type = s[0];
            int r1 = s[1];
            int c1 = s[2];
            int r2 = s[3];
            int c2 = s[4];
            int degree = s[5];
            
            degree = type == 1 ? degree * (-1) : degree;
            
            change[r1][c1] += degree;
            change[r1][c2 + 1] -= degree;
            change[r2 + 1][c1] -= degree;
            change[r2 + 1][c2 + 1] += degree;
        }
        
        for (int c = 0; c < change[0].length; ++c) {
            for (int r = 1; r < change.length; ++r) {
                change[r][c] += change[r - 1][c];
            }
        }
        
        for (int r = 0; r < change.length; ++r) {
            for (int c = 1; c < change[0].length; ++c) {
                change[r][c] += change[r][c - 1];
            }
        }
        
        int answer = 0;
        for (int r = 0; r < board.length; ++r) {
            for (int c = 0; c < board[0].length; ++c) {
                board[r][c] += change[r][c];
                if (board[r][c] > 0) {
                    ++answer;
                }
            }
        }
        return answer;
    }
}
