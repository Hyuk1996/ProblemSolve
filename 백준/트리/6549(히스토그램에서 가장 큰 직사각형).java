import java.util.*;
import java.io.*;

public class Main {

    private static int n, IDTSize;
    private static int[] h = new int[100000];
    private static int[] IDT = new int[300000]; //구간 최소값 저장 IndexTree
    private static int[] IDTIdx = new int[300000]; //구간 최소값의 Idx 저장 IndexTree

    private static int MAX_H = 1000000001;

    public static void main(String[] args) throws IOException {

        //입력
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = null;
        List<Long> answers = new ArrayList<>();

        while(true) {
            String input = br.readLine();
            if(input.equals("0")) {
                break;
            }

            st = new StringTokenizer(input);
            n = Integer.parseInt(st.nextToken());
            for(int i = 0; i < n; ++i) {
                h[i] = Integer.parseInt(st.nextToken());
            }

            makeIDT();
            Long answer = getMaxSize(0, n - 1);
            answers.add(answer);
        }

        //정답 출력
        for(Long ans : answers) {
            System.out.println(ans);
        }
    }

    private static void makeIDT() {
        //index tree 크기 정하기
        int size = 1;
        while(size < n) {
            size *= 2;
        }

        IDTSize = size * 2;

        //index tree 크기만큼 초기화
        for(int i = 1; i < IDTSize; ++i) {
            IDT[i] = MAX_H;
            IDTIdx[i] = 0;
        }

        //leaf node h로 채우기
        int startIdx = size;
        for(int i = 0; i < n; ++i) {
            IDT[i + startIdx] = h[i];
            IDTIdx[i + startIdx] = i;
        }

        //구간 대표값 min으로 IDT 만들기
        for(int i = startIdx - 1; i >= 1; --i) {
            if(IDT[i * 2] <= IDT[i * 2 + 1]) {
                IDT[i] = IDT[i * 2];
                IDTIdx[i] = IDTIdx[i * 2];
            } else {
                IDT[i] = IDT[i * 2 + 1];
                IDTIdx[i] = IDTIdx[i * 2 + 1];
            }
        }
    }

    private static long getMaxSize(int left, int right) {
        int minIdx = getMinIdx(left, right);

        long size = (long)(right - left + 1) * (long)h[minIdx];
        if(left < minIdx) {
            long tmp = getMaxSize(left, minIdx - 1);
            size = Math.max(size, tmp);
        }
        if(minIdx < right) {
            long tmp = getMaxSize(minIdx + 1, right);
            size = Math.max(size, tmp);
        }
        return size;
    }

    private static int getMinIdx(int left, int right) {
        left += (IDTSize / 2);
        right += (IDTSize / 2);

        int minH = MAX_H;
        int minIdx = -1;
        while(left <= right) {
            if(left % 2 == 1) {
                if(minH > IDT[left]) {
                    minH = IDT[left];
                    minIdx = IDTIdx[left];
                }
            }
            if(right % 2 == 0) {
                if(minH > IDT[right]) {
                    minH = IDT[right];
                    minIdx = IDTIdx[right];
                }
            }

            left = (left + 1) / 2;
            right = (right - 1) / 2;
        }
        return minIdx;
    }
}

