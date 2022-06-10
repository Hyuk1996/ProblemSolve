import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Queue;
import java.util.TreeMap;

class Solution {

    public static final String IMPOSSIBLE = "IMPOSSIBLE";

    private Map<Character, List<Position>> map;
    private char[][] grid;
    private int m;
    private int n;

    public String solution(int m, int n, String[] board) {
        this.m = m;
        this.n = n;
        this.grid = boardToGrid(board);
        this.map = storePositionToMap();

        return removeTile();
    }

    private char[][] boardToGrid(String[] board) {
        char[][] tmp = new char[this.m][this.n];
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                tmp[i][j] = board[i].charAt(j);
            }
        }
        return tmp;
    }

    private Map<Character, List<Position>> storePositionToMap() {
        Map<Character, List<Position>> map = new TreeMap<>();
        for(int i = 0; i < this.m; ++i) {
            for(int j = 0; j < this.n; ++j) {
                if(this.grid[i][j] != '*' && this.grid[i][j] != '.') {
                    char c = this.grid[i][j];
                    if(map.containsKey(c)) {
                        map.get(c).add(new Position(j, i));
                    } else {
                        List<Position> list = new ArrayList<>();
                        list.add(new Position(j, i));
                        map.put(c, list);
                    }
                }
            }
        }
        return map;
    }

    private String removeTile() {
        StringBuilder sb = new StringBuilder();
        int cnt = this.map.size();
        for(int i = 0; i < cnt; ++i) {

            for (Entry<Character, List<Position>> entry : this.map.entrySet()) {
                int startX = entry.getValue().get(0).x;
                int startY = entry.getValue().get(0).y;

                int endX = entry.getValue().get(1).x;
                int endY = entry.getValue().get(1).y;

                if(canRemove(startX, startY, endX, endY)) {
                    sb.append(entry.getKey());
                    this.map.remove(entry.getKey());
                    this.grid[startY][startX] = '.';
                    this.grid[endY][endX] = '.';
                    break;
                }
            }

            if(sb.length() != (i + 1)) {
                return IMPOSSIBLE;
            }
        }
        return sb.toString();
    }

    private boolean canRemove(int startX, int startY, int endX, int endY) {
        int[] dx = {0, 0, -1, 1};
        int[] dy = {-1, 1, 0, 0};

        Queue<State> q = new LinkedList<>();
        q.add(new State(startX, startY, -1, 0));
        while(!q.isEmpty()) {
            State state = q.poll();
            int curX = state.x;
            int curY = state.y;
            int curDir = state.dir;
            int curDist = state.dist;

            if(curX == endX && curY == endY) {
                return true;
            }
            
            for(int i = 0; i < 4; ++i) {
                int nextX = curX + dx[i];
                int nextY = curY + dy[i];
                int nextDir = i;
                int nextDist = curDist;

                if(nextX < 0 || nextX >= n || nextY < 0 || nextY >= m) {
                    continue;
                }

                if(!(this.grid[nextY][nextX] == '.' || this.grid[nextY][nextX] == this.grid[startY][startX])) {
                    continue;
                } 
                
                if(curDir != -1 && curDir != nextDir) {
                    nextDist++;
                }

                if(nextDist == 2) {
                    continue;
                }

                q.add(new State(nextX, nextY, nextDir, nextDist));
            }
        }
        return false;
    }

    static class Position {
        int x, y;

        Position(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    static class State {
        int x, y;
        int dir;
        int dist;

        State(int x, int y, int dir, int dist) {
            this.x = x;
            this.y = y;
            this.dir = dir;
            this.dist = dist;
        }
    }
}
