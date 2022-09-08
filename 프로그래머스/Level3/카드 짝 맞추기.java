import java.util.*;

class Solution {

    private static final int INF = 100;
    private static final int BOARD_SIZE = 4;
    
    private static final int[] dr = {0, 0, -1, 1};
    private static final int[] dc = {-1, 1, 0, 0};

    private Map<Integer, List<Pos>> cardInfo;

    public int solution(int[][] board, int r, int c) {

        initCardInfo(board);

        List<List<Integer>> removeOrders = getRemoveOrders();

        int answer = Integer.MAX_VALUE;
        for (List<Integer> removeOrder : removeOrders) {
            answer = Math.min(answer, gameStart(board, removeOrder, r, c, 0));
        }
        return answer;
    }

    private void initCardInfo(int[][] board) {
        cardInfo = new HashMap();
        for (int r = 0; r < BOARD_SIZE; ++r) {
            for (int c = 0; c < BOARD_SIZE; ++c) {
                if (board[r][c] > 0) {
                    if (cardInfo.containsKey(board[r][c])) {
                        cardInfo.get(board[r][c]).add(new Pos(r, c));
                    } else {
                        List<Pos> info = new ArrayList<>();
                        info.add(new Pos(r, c));

                        cardInfo.put(board[r][c], info);
                    }
                }
            }
        } 
    }
    
    private List<List<Integer>> getRemoveOrders() {
        List<Integer> cardNumbers = new ArrayList<>(cardInfo.keySet());
        List<List<Integer>> removeOrders = new ArrayList<>();
        boolean[] isSelected = new boolean[cardNumbers.size()];
        permutation(removeOrders, cardNumbers, new ArrayList<>(), isSelected);
        
        return removeOrders;
    }
    
    private void permutation(
        List<List<Integer>> removeOrders,
        List<Integer> cardNumbers,
        List<Integer> order,
        boolean[] isSelected
    ) {
        if (order.size() == cardNumbers.size()) {
            removeOrders.add(new ArrayList<>(order));
            return;
        }

        for (int i = 0; i < cardNumbers.size(); ++i) {
            if (!isSelected[i]) {
                isSelected[i] = true;
                order.add(cardNumbers.get(i));

                permutation(removeOrders, cardNumbers, order, isSelected);

                order.remove(order.size() - 1);
                isSelected[i] = false;
            }
        }
    }
    
    private int gameStart(
        int[][] board,
        List<Integer> removeOrder,
        int r,
        int c,
        int depth
    ) {
        if (removeOrder.size() == depth) {
            return 0;
        }

        int removeCardNo = removeOrder.get(depth);
        
        int r1 = cardInfo.get(removeCardNo).get(0).r;
        int c1 = cardInfo.get(removeCardNo).get(0).c;
        int r2 = cardInfo.get(removeCardNo).get(1).r;
        int c2 = cardInfo.get(removeCardNo).get(1).c;

        //(r1, c1) -> (r2, c2)
        int[][] board1 = copyBoard(board);
        int moveCnt1 = 0;
        
        moveCnt1 += move(board1, r, c, r1, c1) + 1;
        moveCnt1 += move(board1, r1, c1, r2, c2) + 1;
        
        //(r2, c2) -> (r1, c1)
        int[][] board2 = copyBoard(board);
        int moveCnt2 = 0;

        moveCnt2 += move(board2, r, c, r2, c2) + 1;
        moveCnt2 += move(board2, r2, c2, r1, c1) + 1;

        //다음으로 이동
        moveCnt1 += gameStart(board1, removeOrder, r2, c2, depth + 1);
        moveCnt2 += gameStart(board2, removeOrder, r1, c1, depth + 1);

        return Math.min(moveCnt1, moveCnt2);
    }

    private int move(int[][] board, int startR, int startC, int endR, int endC) {
        Queue<Pos> q = new LinkedList<>();
        int[][] dist = new int[board.length][board[0].length];
        for (int i = 0; i < dist.length; ++i) {
            Arrays.fill(dist[i], INF);
        }
        
        dist[startR][startC] = 0;
        q.offer(new Pos(startR, startC));
        while (!q.isEmpty()) {
            Pos p = q.poll();
            int curR = p.r;
            int curC = p.c;
            
            if (curR == endR && curC == endC) {
                board[curR][curC] = 0;
                return dist[curR][curC];
            }
            
            for (int i = 0; i < 4; ++i) {
                int nextR = curR + dr[i];
                int nextC = curC + dc[i];
                
                if (nextR < 0 || nextR >= 4 || nextC < 0 || nextC >= 4) {
                    continue;
                }
                
                if (dist[nextR][nextC] > dist[curR][curC] + 1) {
                    dist[nextR][nextC] = dist[curR][curC] + 1;
                    q.offer(new Pos(nextR, nextC));
                }
            }
            
            for (int i = 0; i < 4; ++i) {
                int nextR = curR;
                int nextC = curC;
                
                while (true) {
                    nextR = nextR + dr[i];
                    nextC = nextC + dc[i];
                        
                    if (nextR < 0 || nextR >= 4 || nextC < 0 || nextC >= 4) {
                        nextR = nextR - dr[i];
                        nextC = nextC - dc[i];
                        break;
                    }
                        
                    if (board[nextR][nextC] > 0) {
                        break;
                    }
                }
                
                if (dist[nextR][nextC] > dist[curR][curC] + 1) {
                    dist[nextR][nextC] = dist[curR][curC] + 1;
                    q.offer(new Pos(nextR, nextC));
                }
            }
        }
        
        throw new AssertionError();
    }

    private int[][] copyBoard(int[][] board) {
        int[][] copyBoard = new int[board.length][board[0].length];
        for (int r = 0; r < board.length; ++r) {
            for (int c = 0; c < board[0].length; ++c) {
                copyBoard[r][c] = board[r][c];
            }
        }
        return copyBoard;
    }

    static class Pos {
        int r, c;

        Pos(int r, int c) {
            this.r = r;
            this.c = c;
        }
    }
}
