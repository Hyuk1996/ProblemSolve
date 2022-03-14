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

//일일히 조건 체크 풀이
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
                    if(canRemoveColumn(x, y)) {
                        isColumn[y][x] = false;
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
                    if(canRemoveBeam(x, y)) {
                        isBeam[y][x] = false;
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
    
    boolean canRemoveColumn(int x, int y) {
        if(isBeam[y + 1][x] || ((x - 1) >= 0 && isBeam[y + 1][x - 1])) { // 기둥위 보가 존재
            if(isBeam[y + 1][x]) {
                if(!isColumn[y][x + 1]) {
                    if(!((x - 1 >= 0 && isBeam[y + 1][x - 1]) && isBeam[y + 1][x + 1])) {
                        return false;
                    }
                }
            }
            if((x - 1) >= 0 && isBeam[y + 1][x - 1]) {
                if(!isColumn[y][x - 1]) {
                    if(!((x - 2 >= 0 && isBeam[y + 1][x - 2]) && isBeam[y + 1][x])) {
                        return false;
                    }
                }
            }
            return true;
        } else { // 기둥위 보 존재 x
            if(isColumn[y + 1][x]) {
                return false;
            } else {
                return true;
            }
        }
    }
    
    boolean canRemoveBeam(int x, int y) {
        if(isColumn[y][x] || isColumn[y][x + 1]) { //보 위 기둥 존재
            if(isColumn[y][x]) {
                if(!isColumn[y - 1][x]) {
                    if(!(x - 1 >= 0 && isBeam[y][x - 1])) {
                        return false;
                    }
                }
            }
            if(isColumn[y][x + 1]) {
                if(!isColumn[y - 1][x + 1]) {
                    if(!isBeam[y][x + 1]) {
                        return false;
                    }
                }
            }
        } 
    
        //양쪽 보 확인
        if(x - 1 >= 0 && isBeam[y][x - 1]) {
            if(!(isColumn[y - 1][x] || isColumn[y - 1][x - 1])) {
                return false;
            }
        }
        if(isBeam[y][x + 1]) {
            if(!(isColumn[y - 1][x + 1] || isColumn[y - 1][x + 2])) {
                return false;
            }
        }
        return true;
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
