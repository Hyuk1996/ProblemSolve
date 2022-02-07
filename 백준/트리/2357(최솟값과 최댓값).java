import java.util.*;
import java.io.*;

public class Main {

    private static int N;
    private static int M;
    private static int[] arr;

    private static int MAX = 1000000001;

    public static void main(String[] args) throws IOException {

        //입력
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = null;

        st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());

        arr = new int[N + 1];
        for(int i = 1; i <= N; ++i) {
            arr[i] = Integer.parseInt(br.readLine());
        }

        //IDT 만들기
        int IDTSize = getIDTSize();
        int[] minIDT = makeMinIDT(IDTSize);
        int[] maxIDT = makeMaxIDT(IDTSize);

        //쿼리 수행
        int a, b;
        int min, max;
        int[] minAnswers = new int[M];
        int[] maxAnswers = new int[M];
        for(int i = 0; i < M; ++i) {
            st = new StringTokenizer(br.readLine());
            a = Integer.parseInt(st.nextToken());
            b = Integer.parseInt(st.nextToken());

            minAnswers[i] = getMin(minIDT, IDTSize, a, b);
            maxAnswers[i] = getMax(maxIDT, IDTSize, a, b);
        }

        //정답 출력
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        for(int i = 0; i < M; ++i) {
            bw.write(String.valueOf(minAnswers[i]));
            bw.write(" ");
            bw.write(String.valueOf(maxAnswers[i]));
            bw.write("\n");
        }

        bw.flush();
        bw.close();
        br.close();
    }

    private static int getIDTSize() {
        int leafSize = 1;
        while(leafSize < N) {
            leafSize *= 2;
        }

        return leafSize * 2;
    }

    private static int[] makeMinIDT(int IDTSize) {
        int[] minIDT = new int[IDTSize];
        Arrays.fill(minIDT, MAX);

        //leaf node 채우기
        int startIdx = IDTSize / 2;
        for(int i = 1; i <= N; ++i) {
            minIDT[i + startIdx - 1] = arr[i];
        }

        //내부 노드 채우기 (대표값 = 최솟값)
        for(int i = startIdx - 1; i >= 1; --i) {
            minIDT[i] = Math.min(minIDT[i * 2], minIDT[i * 2 + 1]);
        }

        return minIDT;
    }

    private static int[] makeMaxIDT(int IDTSize) {
        int[] maxIDT = new int[IDTSize];

        //leaf node 채우기
        int startIdx = IDTSize / 2;
        for(int i = 1; i <= N; ++i) {
            maxIDT[i + startIdx - 1] = arr[i];
        }

        //내부 노드 채우기 (대표값 = 최댓값)
        for(int i = startIdx - 1; i >= 1; --i) {
            maxIDT[i] = Math.max(maxIDT[i * 2], maxIDT[i * 2 + 1]);
        }

        return maxIDT;
    }

    private static int getMin(int[] minIDT, int IDTSize, int left, int right) {
        left += (IDTSize / 2) - 1;
        right += (IDTSize / 2) - 1;
        int min = MAX;
        while(left <= right) {
            if(left % 2 == 1) {
                min = Math.min(min, minIDT[left]);
            }
            if(right % 2 == 0) {
                min = Math.min(min, minIDT[right]);
            }

            left = (left + 1) / 2;
            right = (right - 1) / 2;
        }
        return min;
    }

    private static int getMax(int[] maxIDT, int IDTSize, int left, int right) {
        left += (IDTSize / 2) - 1;
        right += (IDTSize / 2) - 1;
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

}

