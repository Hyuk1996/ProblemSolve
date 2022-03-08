import java.util.*;

class Solution {
    
    int[][] map;
    final int EMPTY = 0;
    final int OUT = 1;
    final int IN = 2;
    
    final int[] dx = {-1, 1, 0, 0};
    final int[] dy = {0, 0, -1, 1};
    
    public int solution(int[][] rectangle, int characterX, int characterY, int itemX, int itemY) {
        
        //rectangle 정보 이용해 map 색칠하기. 테두리 -> OUT, 내부 -> IN
        makeMap(rectangle);
        
        //BFS 이용해 가장 짧은 거리 구하기
        int answer = bfs(characterX * 2, characterY * 2, itemX * 2, itemY * 2);
        
        return answer;
    }
    
    void makeMap(int[][] rectangle) {
        
        //후에 테두리를 순회하는 과정을 위해 map을 2배 늘리기
        map = new int[101][101];
        for(int i = 0; i < rectangle.length; ++i) {
            int x1 = rectangle[i][0] * 2;
            int y1 = rectangle[i][1] * 2;
            int x2 = rectangle[i][2] * 2;
            int y2 = rectangle[i][3] * 2;
            
            //테두리 칠하기
            //가로
            for(int x = x1; x <= x2; ++x) {
                if(map[y1][x] == EMPTY) {
                    map[y1][x] = OUT;
                }
                if(map[y2][x] == EMPTY) {
                    map[y2][x] = OUT;
                }
            }
            
            //세로
            for(int y = y1; y <= y2; ++y) {
                if(map[y][x1] == EMPTY) {
                    map[y][x1] = OUT;
                }
                if(map[y][x2] == EMPTY) {
                    map[y][x2] = OUT;
                }
            }
            
            //내부 색칠
            for(int x = x1 + 1; x < x2; ++x) {
                for(int y = y1 + 1; y < y2; ++y) {
                    map[y][x] = IN;
                }
            }
        }
    }
    
    int bfs(int startX, int startY, int endX, int endY) {
        Queue<Pos> q = new LinkedList<>();
        int[][] dist = new int[101][101];
        for(int i = 0; i < 101; ++i) {
            Arrays.fill(dist[i], Integer.MAX_VALUE);
        }
        
        
        q.add(new Pos(startX, startY));
        dist[startY][startX] = 0;
        while(!q.isEmpty()) {
            int x = q.peek().x;
            int y = q.peek().y;
            q.remove();
            
            for(int i = 0; i < 4; ++i) {
                int nextX = x + dx[i];
                int nextY = y + dy[i];
                
                if(nextX < 1 || nextX > 100 || nextY < 1 || nextY > 100) {
                    continue;
                }
                if(map[nextY][nextX] != OUT || dist[nextY][nextX] <= dist[y][x]) {
                    continue;
                }
                
                dist[nextY][nextX] = dist[y][x] + 1;
                if(nextX == endX && nextY == endY) {
                    return (int)(dist[endY][endX] / 2);
                }
                
                q.add(new Pos(nextX, nextY));
            }
        }
        return -1;
    }
    
    class Pos {
        int x, y;
        Pos (int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
}
