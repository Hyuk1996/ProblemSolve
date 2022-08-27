import java.util.*;

class Solution {
    public String[] solution(int[][] line) {

        List<Pos> list = new ArrayList<>();

        //1. 좌표 구하기
        for (int i = 0; i < line.length; ++i) {
            long A = line[i][0];
            long B = line[i][1];
            long E = line[i][2];

            for (int j = i + 1; j < line.length; ++j) {
                long C = line[j][0];
                long D = line[j][1];
                long F = line[j][2];

                long xMolecule = B * F - E * D;
                long yMolecule = E * C - A * F;
                long denominator = A * D - B * C;

                if (denominator == 0 || xMolecule % denominator != 0 || yMolecule % denominator != 0) {
                    continue;
                }
              
                long x = xMolecule / denominator;
                long y = yMolecule / denominator;
                Pos pos = new Pos(x, y);

                list.add(pos);
            }
        }

        //출력 격자 범위 정하기
        long minY = Long.MAX_VALUE;
        long minX = Long.MAX_VALUE;
        for (Pos p : list) {
            if (minY > p.y) {
                minY = p.y;
            }
            if (minX > p.x) {
                minX = p.x;
            }
        }

        long maxY = Long.MIN_VALUE;
        long maxX = Long.MIN_VALUE;
        for (Pos p : list) {
            p.y -= minY;
            p.x -= minX;

            if(p.y > maxY) {
                maxY = p.y;
            }
            if(p.x > maxX) {
                maxX = p.x;
            }
        }
        
        //격자 채우기
        char[][] grid = new char[(int)maxY + 1][(int)maxX + 1];

        for (int y = 0; y < maxY + 1; ++y) {
            for (int x = 0; x < maxX + 1; ++x) {
                grid[y][x] = '.';
            }
        }
        for (Pos p : list) {
            grid[(int)p.y][(int)p.x] = '*';
        }

        String[] answer = new String[grid.length];
        for (int i = 0; i < answer.length; ++i) {
            answer[i] = String.valueOf(grid[answer.length - 1 - i]);
        }
        return answer;
    }

    static class Pos {
        long x, y;

        Pos(long x, long y) {
            this.x = x;
            this.y = y;
        }
    }
}
