import java.util.*;

class Solution {

    private int[] dr = {-1, 0, 1, 0};
    private int[] dc = {0, -1, 0, 1};

    public int solution(int[][] game_board, int[][] table) {

        List<List<int[]>> blocks = findBlocks(table);
        List<List<int[]>> emptyBlocks = findEmptyBlocks(game_board);
        
        //블록 하나씩 게임보드에 채우기
        int answer = 0;
        for (List<int[]> block : blocks) {
            for (List<int[]> emptyBlock : emptyBlocks) {
                if (isSameBlock(block, emptyBlock)) {
                    answer += emptyBlock.size();
                    emptyBlocks.remove(emptyBlock);
                    break;
                }
            }
        }

        return answer;
    }

    private List<List<int[]>> findBlocks(int[][] table) {
        
        List<List<int[]>> blocks = new ArrayList<>();
        for (int r = 0; r < table.length; ++r) {
            for (int c = 0; c < table[0].length; ++c) {
                if (table[r][c] == 1) {
                    List<int[]> block = new ArrayList<>();
                    tableDfs(table, r, c, block);
                    blocks.add(arrangeBlockPos(block));
                }
            }
        }
        
        return blocks;
    }
    
    private void tableDfs(int[][] table, int r, int c, List<int[]> block) {
        table[r][c] = 0;
        block.add(new int[]{r, c});

        for (int i = 0; i < 4; ++i) {
            int nextR = r + dr[i];
            int nextC = c + dc[i];

            if (nextR < 0 || nextR >= table.length || nextC < 0 || nextC >= table[0].length) {
                continue;
            }
            if (table[nextR][nextC] == 0) {
                continue;
            }

            tableDfs(table, nextR, nextC, block);
        }
    }
    
    private List<List<int[]>> findEmptyBlocks(int[][] game_board) {
        
        List<List<int[]>> emptyBlocks = new ArrayList<>();
        for (int r = 0; r < game_board.length; ++r) {
            for (int c = 0; c < game_board[0].length; ++c) {
                if (game_board[r][c] == 0) {
                    List<int[]> emptyBlock = new ArrayList<>();
                    gameBoardDfs(game_board, r, c, emptyBlock);
                    emptyBlocks.add(arrangeBlockPos(emptyBlock));
                }
            }
        }
        
        return emptyBlocks;
    }
    
    private void gameBoardDfs(int[][] board, int r, int c, List<int[]> emptyBlock) {
        board[r][c] = 1;
        emptyBlock.add(new int[]{r, c});

        for (int i = 0; i < 4; ++i) {
            int nextR = r + dr[i];
            int nextC = c + dc[i];

            if (nextR < 0 || nextR >= board.length || nextC < 0 || nextC >= board[0].length) {
                continue;
            }
            if (board[nextR][nextC] == 1) {
                continue;
            }

            gameBoardDfs(board, nextR, nextC, emptyBlock);
        }
    }

    private List<int[]> arrangeBlockPos(List<int[]> block) {
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
        
        for (int[] pos : block) {
            pos[0] -= minR;
            pos[1] -= minC;
        }
        
        return block;
    }
    
    private boolean isSameBlock(List<int[]> block, List<int[]> emptyBlock) {
        
        if(block.size() != emptyBlock.size()) {
            return false;
        }
        
        boolean[][] emptyBlockGrid = makeGrid(emptyBlock);
        boolean[][] blockGrid = makeGrid(block);

        for (int i = 0; i < 4; ++i) {
            if (isSameGrid(blockGrid, emptyBlockGrid)) {
                return true;
            }
            
            //rotate
            boolean[][] tmpGrid = new boolean[blockGrid[0].length][blockGrid.length];
            for (int r = 0; r < blockGrid.length; ++r) {
                for (int c = 0; c < blockGrid[0].length; ++c) {
                    tmpGrid[c][blockGrid.length - 1 - r] = blockGrid[r][c];
                }
            }
            blockGrid = tmpGrid;
        }
        return false;
    }

    private boolean[][] makeGrid(List<int[]> poses) {
    
        int maxR = Integer.MIN_VALUE;
        int maxC = Integer.MIN_VALUE;
        for (int[] pos : poses) {
            if (maxR < pos[0]) {
                maxR = pos[0];
            }
            if (maxC < pos[1]) {
                maxC = pos[1];
            }
        }
        
        boolean[][] grid = new boolean[maxR + 1][maxC + 1];
        for (int[] pos : poses) {
            grid[pos[0]][pos[1]] = true;
        }
        return grid;
    }
    
    private boolean isSameGrid(boolean[][] grid1, boolean[][] grid2) {
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
}
