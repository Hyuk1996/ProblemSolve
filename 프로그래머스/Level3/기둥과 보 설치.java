class Solution {
    
    boolean[][] isBeam;
    boolean[][] isColumn;
    
    public int[][] solution(int n, int[][] build_frame) {
        
        init(n);
        
        int buildCnt = 0;
        int x, y, a, b;
        for(int i = 0; i < build_frame.length; ++i) {
            x = build_frame[i][0];
            y = build_frame[i][1];
            a = build_frame[i][2];
            b = build_frame[i][3];
            
            if(a == 0) {
                if(b == 1) {
                    if(checkColumn(x, y)) {
                        isColumn[y][x] = true;
                        buildCnt++;
                    }
                } else {
                    isColumn[y][x] = false;
                    if(!checkAll(n)) {
                        isColumn[y][x] = true;   
                    } else {
                        buildCnt--;
                    }
                }
            } else {
                if(b == 1) {
                    if(checkBeam(x, y)) {
                        isBeam[y][x] = true;
                        buildCnt++;
                    }
                } else {
                    isBeam[y][x] = false;
                    if(!checkAll(n)) {
                        isBeam[y][x] = true;
                    } else {
                        buildCnt--;
                    }
                }
            }
        }
        
        return getAnswer(buildCnt, n);
    }
    
    void init(int n) {
        isBeam = new boolean[n + 1][n + 1];
        isColumn = new boolean[n + 1][n + 1];
    }
    
    boolean checkColumn(int x, int y) {
        if(y == 0) {
            return true;
        } else {
            if(isColumn[y - 1][x]) {
                return true;
            }
            if((isBeam[y][x]) || (x - 1 >= 0 && isBeam[y][x - 1])) {
                return true;
            }
        }
        return false;
    }
    
    boolean checkBeam(int x, int y) {
        if(isColumn[y - 1][x] || isColumn[y - 1][x + 1]) {
            return true;
        }
        if((x - 1 >= 0 && isBeam[y][x - 1]) && isBeam[y][x + 1]) {
            return true;
        }
        return false;
    }
    
    boolean checkAll(int n) {
        for(int i = 0; i <= n; ++i) {
            for(int j = 0; j <= n; ++j) {
                if(isColumn[i][j]) {
                    if(!checkColumn(j, i)) {
                        return false;
                    }
                }
                if(isBeam[i][j]) {
                    if(!checkBeam(j, i)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
    
    int[][] getAnswer(int buildCnt, int n) {
        int[][] answer = new int[buildCnt][3];
        int idx = 0;
        for(int i = 0; i <= n; ++i) {
            for(int j = 0; j <= n; ++j) {
                if(isColumn[j][i]) {
                    answer[idx][0] = i;
                    answer[idx][1] = j;
                    answer[idx][2] = 0;
                    idx++;
                }
                if(isBeam[j][i]) {
                    answer[idx][0] = i;
                    answer[idx][1] = j;
                    answer[idx][2] = 1;
                    idx++;
                }
            }
        }
        return answer;
    }
    
}
