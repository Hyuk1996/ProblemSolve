import java.util.*;

class Solution {
    
    private int N;
    private int M;
    private int lockEmptyCnt = 0;
    
    public boolean solution(int[][] key, int[][] lock) {
        
        N = lock.length;
        M = key.length;
        
        //기존 자물쇠보다, 큰 2차원 배열을 이용해 자물쇠 표현하기
        int[][] bigLock = makeBigLock(lock);
        
        //완전탐색으로 자물쇠 열 수 있는지 확인하기
        boolean answer = true;
        for(int i = 0; i < M - 1 + N; ++i) {
            for(int j = 0; j < M - 1 + N; ++j) {
                for(int k = 0; k < 4; ++k) {                            
                    //자물쇠와 열쇠 비교
                    answer = compare(key, bigLock, i, j);
                   
                    if(answer) {
                        return answer;
                    } else {
                        rotateKey(key);
                    }
                }
            }
        }        
        return answer;
    }
    
    private int[][] makeBigLock(int[][] lock) {
        int size = 2 * M + N - 2;
        int[][] bigLock = new int[size][size];
        
        for(int i = 0; i < size; ++i) {
            for(int j = 0; j < size; ++j) {
                if((M - 1 <= i && i < M - 1 + N) && (M - 1 <= j && j < M - 1 + N)) {
                    bigLock[i][j] = lock[i - (M - 1)][j - (M - 1)];
                    if(bigLock[i][j] == 0) {
                        lockEmptyCnt++;
                    }
                } else {
                    bigLock[i][j] = -1;
                }
            }
        }
        
        return bigLock;
    }
    
    private boolean compare(int[][]key, int[][] bigLock, int diffR, int diffC) {
        int emptyCnt = 0; //현재 키로 매꿀 수 있는 자물쇠 홈의 개수
        boolean canTry = true;
        
        for(int r = 0; r < M; ++r) {
            for(int c = 0; c < M; ++c) {
                //키가 lock의 범위 벗어나는 경우
                if(bigLock[r + diffR][c + diffC] == -1) {
                    continue;
                }
                        
                if(bigLock[r + diffR][c + diffC] == 0 && key[r][c] == 1) {
                    emptyCnt++;
                }
                if(bigLock[r + diffR][c + diffC] == 1 && key[r][c] == 1) {
                    canTry = false;
                    break;
                }
            }
        }
                
        if(canTry) {
            if(emptyCnt == lockEmptyCnt) {
                return true;
            }
        }
        return false;
    }
    
    private void rotateKey(int[][] key) {
        Queue<Integer> q = new LinkedList<>();
        
        for(int i = 0; i < M; ++i) {
            for(int j = M - 1; j >= 0; --j) {
                q.add(key[i][j]);
            }
        }
        
        for(int i = M - 1; i >= 0; --i) {
            for(int j = M - 1; j >= 0; --j) {
                key[j][i] = q.poll();
            }
        }
    }    
}
