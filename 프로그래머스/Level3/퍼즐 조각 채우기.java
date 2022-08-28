import java.util.*;

class Solution {

    private int[] dr = {-1, 0, 1, 0};
    private int[] dc = {0, -1, 0, 1};

    public int solution(int[][] game_board, int[][] table) {

        List<boolean[][]> blocks = findBlocks(table);
        List<boolean[][]> emptyBlocks = findEmptyBlocks(game_board);
        
        //블록 하나씩 게임보드에 채우기
        int answer = 0;
        for (boolean[][] block : blocks) {
            for (boolean[][] emptyBlock : emptyBlocks) {
                if (isSameBlock(block, emptyBlock)) {
                    answer += getBlockSize(emptyBlock);
                    emptyBlocks.remove(emptyBlock);
                    break;
                }
            }
        }

        return answer;
    }

    private List<boolean[][]> findBlocks(int[][] table) {
        
        List<boolean[][]> blocks = new ArrayList<>();
        for (int r = 0; r < table.length; ++r) {
            for (int c = 0; c < table[0].length; ++c) {
                if (table[r][c] == 1) {
                    List<int[]> block = new ArrayList<>();
                    dfs(table, r, c, block, 0);
                    blocks.add(posToGrid(block));
                }
            }
        }
        
        return blocks;
    }
    
    private List<boolean[][]> findEmptyBlocks(int[][] game_board) {
        
        List<boolean[][]> emptyBlocks = new ArrayList<>();
        for (int r = 0; r < game_board.length; ++r) {
            for (int c = 0; c < game_board[0].length; ++c) {
                if (game_board[r][c] == 0) {
                    List<int[]> emptyBlock = new ArrayList<>();
                    dfs(game_board, r, c, emptyBlock, 1);
                    emptyBlocks.add(posToGrid(emptyBlock));
                }
            }
        }
        
        return emptyBlocks;
    }
    
    private void dfs(int[][] map, int r, int c, List<int[]> block, int mode) {
        //mode 0 : table, 1 : game_board
        map[r][c] = mode;
        block.add(new int[]{r, c});

        for (int i = 0; i < 4; ++i) {
            int nextR = r + dr[i];
            int nextC = c + dc[i];

            if (nextR < 0 || nextR >= map.length || nextC < 0 || nextC >= map[0].length) {
                continue;
            }
            if (map[nextR][nextC] == mode) {
                continue;
            }

            dfs(map, nextR, nextC, block, mode);
        }
    }

    private boolean[][] posToGrid(List<int[]> block) {
        int minR = Integer.MAX_VALUE;
        int minC = Integer.MAX_VALUE;
        for (int[] pos : block) {
            if (minR > pos[0]) {
                minR = pos[0];
            }
            if (minC > pos[1]) {
                minC = pos[1];
            }
        }
        
        int maxR = Integer.MIN_VALUE;
        int maxC = Integer.MIN_VALUE;
        for (int[] pos : block) {
            pos[0] -= minR;
            pos[1] -= minC;
            
            if (maxR < pos[0]) {
                maxR = pos[0];
            }
            if (maxC < pos[1]) {
                maxC = pos[1];
            }
        }
        
        boolean[][] grid = new boolean[maxR + 1][maxC + 1];
        for (int[] pos : block) {
            grid[pos[0]][pos[1]] = true;
        }
        return grid;
    }
    
    private int getBlockSize(boolean[][] block) {
        int blockCnt = 0;
        for (int r = 0; r < block.length; ++r) {
            for (int c = 0; c < block[0].length; ++c) {
                if (block[r][c]) {
                    ++blockCnt;
                }
            }
        }
        return blockCnt;
    }
    
    private boolean isSameBlock(boolean[][] block, boolean[][] emptyBlock) {
        
        for (int i = 0; i < 4; ++i) {
            if (compare(block, emptyBlock)) {
                return true;
            }
            
            block = rotate(block);
        }
        return false;
    }
    
    private boolean compare(boolean[][] grid1, boolean[][] grid2) {
        if (grid1.length != grid2.length || grid1[0].length != grid2[0].length) {
            return false;
        }
        
        for (int r = 0; r < grid1.length; ++r) {
            for (int c = 0; c < grid1[0].length; ++c) {
                if (grid1[r][c] != grid2[r][c]) {
                    return false;
                }
            }
        }
        return true;
    }

    private boolean[][] rotate(boolean[][] block) {
        boolean[][] tmp = new boolean[block[0].length][block.length];
        for (int r = 0; r < block.length; ++r) {
            for (int c = 0; c < block[0].length; ++c) {
                tmp[c][block.length - 1 - r] = block[r][c];
            }
        }
        return tmp;
    }
}
