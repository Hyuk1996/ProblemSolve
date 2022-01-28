class Solution {
    
    private int[] dr = {-1, 0, 1, 0};
    private int[] dc = {0, -1, 0, 1};
    
    public int solution(String dirs) {
        int answer = 0;
        
        boolean[][][] road = new boolean[11][11][4];
        int r = 5;
        int c = 5;
        
        for(int i=0; i<dirs.length(); ++i) {
            int dir = getDir(dirs.charAt(i));
            
            int nextR = r + dr[dir];
            int nextC = c + dc[dir];
            
            if(nextR < 0 || nextR > 10 || nextC < 0 || nextC > 10) {
                continue;
            }
            
            if(!road[r][c][dir]) {
                answer++;
                road[r][c][dir] = true;
                road[nextR][nextC][(dir + 2) % 4] = true;
            }
            r = nextR;
            c = nextC;
        }
        
        return answer;
    }
    
    private int getDir(char d) {
        if(d == 'U') {
            return 0;
        } else if(d == 'L') {
            return 1;
        } else if(d == 'D') {
            return 2;
        } else {
            return 3;
        }
    }
}
