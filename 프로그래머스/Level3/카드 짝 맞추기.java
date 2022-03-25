import java.util.*;

class Solution {
    
    final int BOARD_SIZE = 4;
    
    Map<Integer, List<Point>> map;
    List<List<Integer>> permutations;
    int answer = Integer.MAX_VALUE;
    
    final int[] dr = {-1, 1, 0, 0};
    final int[] dc = {0, 0, -1, 1};
    
    public int solution(int[][] board, int r, int c) {
        
        //board에서 카드 정보를 구하기
        map = getInfo(board);
        
        //카드를 뽑을 수 있는 모든 순열 구하기
        permutations = new ArrayList<>();
        List<Integer> cards = new ArrayList(map.keySet());
        boolean[] isSelected = new boolean[cards.size()];
        Integer[] permutation = new Integer[cards.size()];
        
        getPermutations(cards, isSelected, permutation, 0);
        
        
        //각 순서에 대해 게임 진행
        for(List<Integer> cardOrder : permutations) {
            game(cardOrder, board, r, c, 0, 0);
        }
        
        return answer;
    }
    
    Map<Integer, List<Point>> getInfo(int[][] board) {
        Map<Integer, List<Point>> map = new HashMap<>();
        for(int i = 0; i < BOARD_SIZE; ++i) {
            for(int j = 0; j < BOARD_SIZE; ++j) {
                if(board[i][j] == 0) {
                    continue;
                }
                
                int cardNum = board[i][j];
                if(map.containsKey(cardNum)) {
                    map.get(cardNum).add(new Point(i, j));
                } else {
                    List<Point> list = new ArrayList<>();
                    list.add(new Point(i, j));
                    map.put(cardNum, list);
                }
            }
        }
        return map;
    }
    
    void getPermutations(List<Integer> cards, boolean[] isSelected, Integer[] permutation, int depth) {
        if(depth == cards.size()) {
            permutations.add(new ArrayList<>(Arrays.asList(permutation)));
            return;
        }
        
        for(int i = 0; i < cards.size(); ++i) {
            if(!isSelected[i]) {
                isSelected[i] = true;
                permutation[depth] = cards.get(i);
                getPermutations(cards, isSelected, permutation, depth + 1);
                isSelected[i] = false;
            }
        }
    }
    
    void game(List<Integer> cardOrder, int[][] board, int r, int c, int gameTurn, int moveCnt) {
        if(gameTurn == cardOrder.size()) {
            answer = Math.min(answer, moveCnt);
            return;
        }
        
        int cardNum = cardOrder.get(gameTurn);
        int r1 = map.get(cardNum).get(0).r;
        int c1 = map.get(cardNum).get(0).c;
        int r2 = map.get(cardNum).get(1).r;
        int c2 = map.get(cardNum).get(1).c;
        
        //(r1, c1) -> (r2, c2)
        int[][] tmp1 = copyBoard(board);
        int tmpCnt1 = moveCnt;
        
        tmpCnt1 += move(tmp1, r, c, r1, c1);
        tmpCnt1 += move(tmp1, r1, c1, r2, c2);
        tmpCnt1 += 2; //Enter
        
        tmp1[r1][c1] = 0;
        tmp1[r2][c2] = 0;
        game(cardOrder, tmp1, r2, c2, gameTurn + 1, tmpCnt1);
        
        //(r2, c2) -> (r1, c1)
        int[][] tmp2 = copyBoard(board);
        int tmpCnt2 = moveCnt;
        
        tmpCnt2 += move(tmp2, r, c, r2, c2);
        tmpCnt2 += move(tmp2, r2, c2, r1, c1);
        tmpCnt2 += 2; //Enter
        
        tmp2[r1][c1] = 0;
        tmp2[r2][c2] = 0;
        game(cardOrder, tmp2, r1, c1, gameTurn + 1, tmpCnt2);
    }
    
    int[][] copyBoard(int[][] board) {
        int[][] tmp = new int[BOARD_SIZE][BOARD_SIZE];
        for(int i = 0; i < BOARD_SIZE; ++i) {
            for(int j = 0; j < BOARD_SIZE; ++j) {
                tmp[i][j] = board[i][j];
            }
        }
        return tmp;
    }
    
    int move(int[][] board, int startR, int startC, int endR, int endC) {
        Queue<Point> q = new LinkedList<>();
        int[][] dist = init();
        
        dist[startR][startC] = 0;
        q.add(new Point(startR, startC));
        while(!q.isEmpty()) {
            Point p = q.poll();
            
            if(p.r == endR && p.c == endC) {
                return dist[endR][endC];
            }
            
            //방향키
            for(int i = 0; i < 4; ++i) {
                int nextR = p.r + dr[i];
                int nextC = p.c + dc[i];
                
                if(nextR < 0 || nextR >= BOARD_SIZE || nextC < 0 || nextC >= BOARD_SIZE) {
                    continue;
                }
                if(dist[nextR][nextC] < dist[p.r][p.c] + 1) {
                    continue;
                }
                dist[nextR][nextC] = dist[p.r][p.c] + 1;
                q.add(new Point(nextR, nextC));
            }
            
            //Ctrl+방향키
            for(int i = 0; i < 4; ++i) {
                int nextR = p.r + dr[i];
                int nextC = p.c + dc[i];
                
                if(nextR < 0 || nextR >= BOARD_SIZE || nextC < 0 || nextC >= BOARD_SIZE) {
                    continue;
                }
                
                while(true) {
                    if(board[nextR][nextC] != 0) {
                        break;
                    }
                    
                    nextR += dr[i];
                    nextC += dc[i];
                    if(nextR < 0 || nextR >= BOARD_SIZE || nextC < 0 || nextC >= BOARD_SIZE) {
                        nextR -= dr[i];
                        nextC -= dc[i];
                        break;
                    }
                }
                
                if(dist[nextR][nextC] < dist[p.r][p.c] + 1) {
                    continue;
                }
                dist[nextR][nextC] = dist[p.r][p.c] + 1;
                q.add(new Point(nextR, nextC));
            }
        }
        return -1;
    }
    
    int[][] init() {
        int [][] dist = new int[BOARD_SIZE][BOARD_SIZE];
        for(int i = 0; i < BOARD_SIZE; ++i) {
            Arrays.fill(dist[i], Integer.MAX_VALUE);
        }
        return dist;
    }
 
    class Point {
        int r, c;
        Point(int r, int c) {
            this.r = r;
            this.c = c;
        }
    }
}
