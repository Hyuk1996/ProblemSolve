import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Queue;
import java.util.TreeMap;

class Solution {

    public static final String IMPOSSIBLE = "IMPOSSIBLE";

    private final int[] dx = {0, 0, -1, 1};
    private final int[] dy = {-1, 1, 0, 0};

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
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                tmp[i][j] = board[i].charAt(j);
            }
        }
        return tmp;
    }

    private Map<Character, List<Position>> storePositionToMap() {
        Map<Character, List<Position>> map = new TreeMap<>();
        for (int i = 0; i < this.m; ++i) {
            for (int j = 0; j < this.n; ++j) {
                if (this.grid[i][j] != '*' && this.grid[i][j] != '.') {
                    char c = this.grid[i][j];
                    if (map.containsKey(c)) {
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
        for (int i = 0; i < cnt; ++i) {

            for (Entry<Character, List<Position>> entry : this.map.entrySet()) {
                int startX = entry.getValue().get(0).x;
                int startY = entry.getValue().get(0).y;

                int endX = entry.getValue().get(1).x;
                int endY = entry.getValue().get(1).y;

                if (canRemoveUsingBruteForce(startX, startY, endX, endY)) {
                    sb.append(entry.getKey());
                    this.map.remove(entry.getKey());
                    this.grid[startY][startX] = '.';
                    this.grid[endY][endX] = '.';
                    break;
                }
            }

            if (sb.length() != (i + 1)) {
                return IMPOSSIBLE;
            }
        }
        return sb.toString();
    }

    private boolean canRemoveUsingBruteForce(int startX, int startY, int endX, int endY) {
        if (startX <= endX) {
            if (checkRow(startX, startY, endY, this.grid[endY][endX]) &&
                checkColumn(startX, endY, endX, this.grid[endY][endX])) {
                return true;
            }
            if (checkColumn(startX, startY, endX, this.grid[endY][endX]) &&
                checkRow(endX, startY, endY, this.grid[endY][endX])) {
                return true;
            }
        } else {
            if (checkRow(startX, startY, endY, this.grid[endY][endX]) &&
                checkColumn(endX, endY, startX, this.grid[endY][endX])) {
                return true;
            }
            if (checkColumn(endX, startY, startX, this.grid[endY][endX]) &&
                checkRow(endX, startY, endY, this.grid[endY][endX])) {
                return true;
            }
        }
        return false;
    }

    private boolean checkRow(int curX, int curY, int destY, char c) {
        for (int i = curY; i <= destY; ++i) {
            if (this.grid[i][curX] != '.' && this.grid[i][curX] != c) {
                return false;
            }
        }
        return true;
    }

    private boolean checkColumn(int curX, int curY, int destX, char c) {
        for (int i = curX; i <= destX; ++i) {
            if (this.grid[curY][i] != '.' && this.grid[curY][i] != c) {
                return false;
            }
        }
        return true;
    }

    private boolean canRemoveUsingBFS(int startX, int startY, int endX, int endY) {
        Queue<State> q = new LinkedList<>();
        q.add(new State(startX, startY, -1, 0));
        while (!q.isEmpty()) {
            State state = q.poll();
            int curX = state.x;
            int curY = state.y;
            int curDir = state.dir;
            int curDist = state.dist;

            if (curX == endX && curY == endY) {
                return true;
            }

            for (int i = 0; i < 4; ++i) {
                int nextX = curX + this.dx[i];
                int nextY = curY + this.dy[i];
                int nextDir = i;
                int nextDist = curDist;

                if (nextX < 0 || nextX >= n || nextY < 0 || nextY >= m) {
                    continue;
                }

                if (!(this.grid[nextY][nextX] == '.'
                    || this.grid[nextY][nextX] == this.grid[startY][startX])) {
                    continue;
                }

                if (curDir != -1 && curDir != nextDir) {
                    nextDist++;
                }

                if (nextDist == 2) {
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
