import java.util.*;
import java.io.*;

public class Main {

    private static int n, m;
    private static int[] years;
    private static int[] rains;

    public static void main(String[] args) throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        input(br);

        StringBuilder sb = new StringBuilder();
        solve(br, sb);

        System.out.print(sb);
        br.close();
    }

    private static void input(BufferedReader br) throws IOException {

        n = Integer.parseInt(br.readLine());
        years = new int[n];
        rains = new int[n];

        StringTokenizer st = null;
        for(int i = 0; i < n; ++i) {
            st = new StringTokenizer(br.readLine());

            years[i] = Integer.parseInt(st.nextToken());
            rains[i] = Integer.parseInt(st.nextToken());
        }
    }

    private static void solve(BufferedReader br, StringBuilder sb) throws IOException {
        int[] maxIDT = makeMaxIDT();

        m = Integer.parseInt(br.readLine());

        StringTokenizer st = null;
        int Y, X;
        int idxY, idxX, nextY;
        boolean existY, existX;
        int maxRain;
        for(int i = 0; i < m; ++i) {
            st = new StringTokenizer(br.readLine());
            Y = Integer.parseInt(st.nextToken());
            X = Integer.parseInt(st.nextToken());

            idxY = binarySearch(Y);
            idxX = binarySearch(X);

            existY = (idxY < n && years[idxY] == Y);
            existX = (idxX < n && years[idxX] == X);

            nextY = binarySearch(Y + 1);
            if(nextY == n) {
                maxRain = 0;
            } else {
                maxRain = getRangeMax(maxIDT, nextY, idxX - 1);
            }

            getAnswer(sb, existY, existX, idxY, idxX, maxRain);
        }
    }

    private static int[] makeMaxIDT() {
        //IDT 크기 설정
        int startIdx = 1;
        while(startIdx < n) {
            startIdx *= 2;
        }

        int[] maxIDT = new int[startIdx * 2];

        //leaf node 채우기
        for(int i = 0; i < n; ++i) {
            maxIDT[i + startIdx] = rains[i];
        }

        //내부 노드 채우기
        for(int i = startIdx - 1; i >= 1; --i) {
            maxIDT[i] = Math.max(maxIDT[i * 2], maxIDT[i * 2 + 1]);
        }

        return maxIDT;
    }

    private static int binarySearch(int key) {
        int lo = -1;
        int hi = n - 1;
        while(lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;
            if(years[mid] < key) {
                lo = mid;
            } else {
                hi = mid;
            }
        }

        if(years[hi] < key) {
            return n;
        }
        return hi;
    }

    private static int getRangeMax(int[] maxIDT, int left, int right) {
        left += (maxIDT.length / 2);
        right += (maxIDT.length / 2);
        int max = 0;
        while(left <= right) {
            if(left % 2 == 1) {
                max = Math.max(max, maxIDT[left]);
            }
            if(right % 2 == 0) {
                max = Math.max(max, maxIDT[right]);
            }

            left = (left + 1) / 2;
            right = (right - 1) / 2;
        }
        return max;
    }

    private static void getAnswer(StringBuilder sb, boolean existY, boolean existX, int idxY, int idxX, int maxRain) {

        if(existY && existX) {
            if(rains[idxX] > rains[idxY]) {
                sb.append("false\n");
            } else {
                if(maxRain >= rains[idxX]) {
                    sb.append("false\n");
                } else {
                    if((years[idxX] - years[idxY]) == (idxX - idxY)) {
                        sb.append("true\n");
                    } else {
                        sb.append("maybe\n");
                    }
                }
            }
        } else if(existY) {
            if(maxRain >= rains[idxY]) {
                sb.append("false\n");
            } else {
                sb.append("maybe\n");
            }
        } else if(existX) {
            if(maxRain >= rains[idxX]) {
                sb.append("false\n");
            } else {
                sb.append("maybe\n");
            }
        } else {
            sb.append("maybe\n");
        }
    }
    
}

