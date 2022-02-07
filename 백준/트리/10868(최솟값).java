import java.util.*;
import java.io.*;

public class Main {

    private static int N, M;
    private static int[] arr;

    private static final int MAX = 1000000001;

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

        int[] minIDT = makeMinIDT();

        //쿼리 수행
        StringBuilder sb = new StringBuilder();
        int a, b, min;
        for(int i = 0; i < M; ++i) {

            st = new StringTokenizer(br.readLine());
            a = Integer.parseInt(st.nextToken());
            b = Integer.parseInt(st.nextToken());

            min = getMin(minIDT, a, b);
            sb.append(min + "\n");
        }

        //정답 출력
        System.out.println(sb.toString());
        br.close();
    }

    private static int[] makeMinIDT() {

        //IDT leaf node 개수 설정
        int leafSize = 1;
        while(leafSize < N) {
            leafSize *= 2;
        }

        int[] minIDT = new int[leafSize * 2];
        Arrays.fill(minIDT, MAX);

        //leaf node 채우기
        int startIdx = leafSize;
        for(int i = 1; i <= N; ++i) {
            minIDT[i + startIdx - 1] = arr[i];
        }

        //내부 노드 채우기
        for(int i = startIdx - 1; i >= 1; --i) {
            minIDT[i] = Math.min(minIDT[i * 2], minIDT[i * 2 + 1]);
        }

        return minIDT;
    }

    private static int getMin(int[] minIDT, int left, int right) {
        left += (minIDT.length / 2) - 1;
        right += (minIDT.length / 2) - 1;
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

}

