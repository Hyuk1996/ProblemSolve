import java.util.*;

class Solution {

    //오른쪽, 아래, 왼쪽, 위
    private int[] dr = {0, 1, 0, -1};
    private int[] dc = {1, 0, -1, 0};

    private int rowSize;
    private int colSize;
    
    public int[] solution(String[] grid) {

        rowSize = grid.length;
        colSize = grid[0].length();
        
        boolean[][][] map = new boolean[rowSize][colSize][4];
        List<Integer> answer = new ArrayList<>();

        for (int r = 0; r < rowSize; ++r) {
            for (int c = 0; c < colSize; ++c) {
                for (int d = 0; d < 4; ++d) {
                    if (!map[r][c][d]) {
                        int cycleLen = travel(map, grid, r, c, d);
                        answer.add(cycleLen);
                    }
                }
            }
        }

        Collections.sort(answer);
        return answer.stream().mapToInt(i -> i).toArray();
    }

    private int travel(boolean[][][] map, String[] grid, int r, int c, int d) {
        int cnt = 0;
        while(!map[r][c][d]) {
            map[r][c][d] = true;
            
            if (grid[r].charAt(c) == 'R') {
                d = (d + 1) % 4;
            }
            if (grid[r].charAt(c) == 'L') {
                d = (d + 3) % 4;
            }
            
            r = r + dr[d];
            c = c + dc[d];
            
            //격자의 끝을 넘어가는 경우
            if (r == -1) {
                r = rowSize - 1;
            }
            if (r == rowSize) {
                r = 0;
            }
            if (c == -1) {
                c = colSize - 1;
            }
            if (c == colSize) {
                c = 0;
            }
            
            ++cnt;
        }
        return cnt;
    }
}
