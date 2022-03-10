import java.util.*;

class Solution {
    
    int size;
    
    final int[] dr = {-1, 1, 0, 0};
    final int[] dc = {0, 0, -1, 1};
    
    public int solution(int[][] game_board, int[][] table) {

        size = game_board.length;
        
        List<List<Pos>> emptyBlocks = findEmptyBlocks(game_board);
        List<List<Pos>> blocks = findBlocks(table);
        
        //emptyBlocks 미리 좌표 조절. (비교 편의 위해)
        setEmptyBlocksPos(emptyBlocks);
        
        //비교시작
        int answer = 0;
        for(List<Pos> block : blocks) {
            for(int i = 0; i < emptyBlocks.size(); ++i) {
                if(check(block, emptyBlocks.get(i))) {
                    answer += block.size();
                    emptyBlocks.remove(i);
                    break;
                }
            }
        }
        
        return answer;
    }
    
    List<List<Pos>> findEmptyBlocks(int[][] game_board) {
        List<List<Pos>> emptyBlocks = new ArrayList<>();
        
        for(int i = 0; i < size; ++i) {
            for(int j = 0; j < size; ++j) {
                if(game_board[i][j] == 0) {
                    List<Pos> emptyBlock = new ArrayList<>();
                    gameBoardDfs(game_board, emptyBlock, i, j);
                    emptyBlocks.add(emptyBlock);
                }
            }
        }
        return emptyBlocks;
    }
    
    void gameBoardDfs(int[][] game_board, List<Pos> block, int r, int c) {
        game_board[r][c] = 1;
        block.add(new Pos(r, c));
        
        for(int i = 0; i < 4; ++i) {
            int nextR = r + dr[i];
            int nextC = c + dc[i];
            
            if(nextR < 0 || nextR >= size || nextC < 0 || nextC >= size) {
                continue;
            }
            if(game_board[nextR][nextC] == 1) {
                continue;
            }
            gameBoardDfs(game_board, block, nextR, nextC);
        }
    }
    
    List<List<Pos>> findBlocks(int[][] table) {
        List<List<Pos>> blocks = new ArrayList<>();
        
        for(int i = 0; i < size; ++i) {
            for(int j = 0; j < size; ++j) {
                if(table[i][j] == 1) {
                    List<Pos> block = new ArrayList<>();
                    tableDfs(table, block, i, j);
                    blocks.add(block);
                }
            }
        }
        return blocks;
    }
    
    void tableDfs(int[][] table, List<Pos> block, int r, int c) {
        table[r][c] = 0;
        block.add(new Pos(r, c));
        for(int i = 0; i < 4; ++i) {
            int nextR = r + dr[i];
            int nextC = c + dc[i];
            
            if(nextR < 0 || nextR >= size || nextC < 0 || nextC >= size) {
                continue;
            }
            if(table[nextR][nextC] == 0) {
                continue;
            }
            tableDfs(table, block, nextR, nextC);
        }
    }
    
    void setEmptyBlocksPos(List<List<Pos>> emptyBlocks) {
        for(List<Pos> emptyBlock : emptyBlocks) {
            int minR = 50;
            int minC = 50;
            for(Pos p : emptyBlock) {
                minR = Math.min(minR, p.r);
                minC = Math.min(minC, p.c);
            }
            
            for(Pos p : emptyBlock) {
                p.r -= minR;
                p.c -= minC;
            }
        }    
    }
    
    boolean check(List<Pos> block, List<Pos> emptyBlock) {
        if(block.size() != emptyBlock.size()) {
            return false;
        }
        
        //block 좌표 조정
        int minR = 50;
        int minC = 50;
        for(Pos p : block) {
            minR = Math.min(minR, p.r);
            minC = Math.min(minC, p.c);
        }
        
        int maxR = -1;
        int maxC = -1;
        for(Pos p : block) {
            p.r -= minR;
            p.c -= minC;
            
            maxR = Math.max(maxR, p.r);
            maxC = Math.max(maxC, p.c);
        }
        
        //block의 회전을 구현하기 위해, block을 사각형에 넣기 
        int[][] squareBlock = new int[maxR + 1][maxC + 1];
        for(Pos p : block) {
            squareBlock[p.r][p.c] = 1;
        }
        
        //블록을 회전하면서 게임 보드에 널 수 있는 체크
        for(int i = 0; i < 4; ++i) {
            if(compare(squareBlock, emptyBlock)) {
                return true;
            }
            squareBlock = rotate(squareBlock);
        }
        
        return false;
    }
    
    int[][] rotate(int[][] block) {
        int rSize = block.length;
        int cSize = block[0].length;
        
        int[][] rotateBlock = new int[cSize][rSize];
        for(int c = 0; c < cSize; ++c) {
            for(int r = 0; r < rSize; ++r) {
                rotateBlock[c][rSize - 1 - r] = block[r][c];
            }
        }
        return rotateBlock;
    }
    
    boolean compare(int[][] block, List<Pos> emptyBlock) {
        for(Pos p : emptyBlock) {
            if(p.r < 0 || p.r >= block.length || p.c < 0 || p.c >= block[0].length) {
                return false;
            }
            if(block[p.r][p.c] == 0) {
                return false;
            }
        }
        return true;
    }
    
    class Pos {
        int r, c;
        Pos(int r, int c) {
            this.r = r;
            this.c = c;
        }
    }
}
