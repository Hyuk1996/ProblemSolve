import java.util.*;

class Solution {
    
    Map<Integer, List<Pos>> map;
    List<Integer> cards;
    List<List<Integer>> permutations = new ArrayList<>();

    final int[] dr = {-1, 1, 0, 0};
    final int[] dc = {0, 0, -1, 1};
    
    int answer = Integer.MAX_VALUE;
    
    public int solution(int[][] board, int r, int c) {
        
        //보드에서 카드 번호와 좌표정보 구해서 map에 저장
        map = getInfo(board);
        
        //카드를 지울 수 있는 모든 순서 구하기(순열)
        cards = new ArrayList<>(map.keySet());
        boolean[] isVisited = new boolean[cards.size()];
        Integer[] permutation = new Integer[cards.size()];
        
        getPermutation(isVisited, permutation, 0);
    
        //가능한 모든 순서에 대해 게임 진행하기
        for(List<Integer> permu : permutations) {
            gameStart(permu, board, r, c, 0, 0);
        }
        
        return answer;
    }
    
    Map<Integer, List<Pos>> getInfo(int[][] board) {
        Map<Integer, List<Pos>> map = new HashMap<>();
        
        for(int i = 0; i < board.length; ++i) {
            for(int j = 0; j < board.length; ++j) {
                if(board[i][j] == 0) {
                    continue;
                }
                if(map.containsKey(board[i][j])) {
                    map.get(board[i][j]).add(new Pos(i, j));
                } else {
                    List<Pos> pos = new ArrayList<>();
                    pos.add(new Pos(i, j));
                    map.put(board[i][j], pos);
                }
            }
        }
        
        return map;
    }
    
    void getPermutation(boolean[] isVisited, Integer[] permutation, int depth) {
        if(depth == cards.size()) {
            permutations.add(new ArrayList<>(Arrays.asList(permutation)));
        }
        
        for(int i = 0; i < cards.size(); ++i) {
            if(!isVisited[i]) {
                isVisited[i] = true;
                permutation[depth] = cards.get(i);
                getPermutation(isVisited, permutation, depth + 1);
                isVisited[i] = false;
            }
        }
    }
    
    void gameStart(List<Integer> permu, int[][] board, int r, int c, int depth, int moveCnt) {
        if(depth == permu.size()) {
            answer = Math.min(answer, moveCnt);
            return;
        }
        
        int r1 = map.get(permu.get(depth)).get(0).r;
        int c1 = map.get(permu.get(depth)).get(0).c;
        
        int r2 = map.get(permu.get(depth)).get(1).r;
        int c2 = map.get(permu.get(depth)).get(1).c;
        
        //하나의 카드를 없애는 방법도 2가지 경우의 수 존재
        //지우는 순서 (r1, c1) -> (r2, c2)
        int[][] tmp1 = copyBoard(board);
        int moveCnt1 = moveCnt;
        
        moveCnt1 += move(tmp1, r, c, r1, c1);
        moveCnt1 += move(tmp1, r1, c1, r2, c2);
        tmp1[r1][c1] = 0;
        tmp1[r2][c2] = 0;
        gameStart(permu, tmp1, r2, c2, depth + 1, moveCnt1);
        
        //지우는 순서 (r2, c2) -> (r1, c1)
        int[][] tmp2 = copyBoard(board);
        int moveCnt2 = moveCnt;
        
        moveCnt2 += move(tmp2, r, c, r2, c2);
        moveCnt2 += move(tmp2, r2, c2, r1, c1);
        tmp2[r2][c2] = 0;
        tmp2[r1][c1] = 0;
        gameStart(permu, tmp2, r1, c1, depth + 1, moveCnt2);
    }
    
    int move(int[][] board, int fromR, int fromC, int toR, int toC) {
        Queue<Pos> q = new LinkedList<>();
        int[][] dist = new int[board.length][board.length];
        init(dist);
        
        dist[fromR][fromC] = 0;
        q.add(new Pos(fromR, fromC));
        while(!q.isEmpty()) {
            Pos pos = q.poll();
            
            if(pos.r == toR && pos.c == toC) {
                return dist[toR][toC] + 1;
            }
            
            //방향키만 이동
            for(int i = 0; i < 4; ++i) {
                int nextR = pos.r + dr[i];
                int nextC = pos.c + dc[i];
                
                if(nextR < 0 || nextR >= 4 || nextC < 0 || nextC >= 4) {
                    continue;
                }
                if(dist[nextR][nextC] < dist[pos.r][pos.c] + 1) {
                    continue;
                }
                dist[nextR][nextC] = dist[pos.r][pos.c] + 1;
                q.add(new Pos(nextR, nextC));
            }
            
            //컨트롤 + 방향키
            for(int i = 0; i < 4; ++i) {
                int nextR = pos.r + dr[i];
                int nextC = pos.c + dc[i];
                
                if(nextR < 0 || nextR >= 4 || nextC < 0 || nextC >= 4) {
                    continue;
                }
                while(true) {
                    if(board[nextR][nextC] != 0) {
                        break;
                    }
                    nextR = nextR + dr[i];
                    nextC = nextC + dc[i];
                    if(nextR < 0 || nextR >= 4 || nextC < 0 || nextC >= 4) {
                        nextR -= dr[i];
                        nextC -= dc[i];
                        break;
                    }
                }
                
                if(dist[nextR][nextC] < dist[pos.r][pos.c] + 1) {
                    continue;
                }
                dist[nextR][nextC] = dist[pos.r][pos.c] + 1;
                q.add(new Pos(nextR, nextC));
            }
        }
        return -1;
    }
    
    void init(int[][] dist) {
        for(int i = 0; i < dist.length; ++i) {
            for(int j = 0; j < dist.length; ++j) {
                dist[i][j] = Integer.MAX_VALUE;
            }
        }
    }
    
    int[][] copyBoard(int[][] board) {
        int[][] tmp = new int[board.length][board.length];
        for(int i = 0; i < board.length; ++i) {
            for(int j = 0; j < board.length; ++j) {
                tmp[i][j] = board[i][j];
            }
        }
        return tmp;
    }
    
    class Pos {
        int r, c;
        Pos(int r, int c) {
            this.r = r;
            this.c = c;
        }
    }
}
