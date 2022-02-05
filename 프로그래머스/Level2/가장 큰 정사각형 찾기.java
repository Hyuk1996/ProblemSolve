class Solution
{
    public int solution(int [][]board)
    {    
        int squareLength = getSquareLength(board);
        
        int answer = squareLength * squareLength;   
        
        return answer;
    }
    
    //DP를 이용해 좌표상 만들 수 있는 가장 큰 정사각형의 변 길이 구하기 
    private int getSquareLength(int[][] board) {
        
        int rSize = board.length;
        int cSize = board[0].length;
        int[][] dp = new int[rSize][cSize];
        
        int squareLength = -1;
        for(int i = 0; i < rSize; ++i) {
            for(int j = 0; j < cSize; ++j) {
                if(i == 0 || j == 0) {
                    dp[i][j] = board[i][j];
                } else {
                    if(board[i][j] == 1) {
                        dp[i][j] = 1 + Math.min(dp[i - 1][j], Math.min(dp[i][j - 1], dp[i - 1][j - 1]));
                    }
                }
                
                squareLength = Math.max(squareLength, dp[i][j]);
            }
        }
        
        return squareLength;
    }
}
