import java.util.*;
import java.io.*;

public class Main {

    private static int N;
    private static int[] arr;

    public static void main(String[] args) throws IOException {

        input();

        long answer = solve();

        System.out.println(answer);
    }

    private static void input() throws IOException {

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        N = Integer.parseInt(br.readLine());
        arr = new int[N];

        st = new StringTokenizer(br.readLine());
        for(int i = 0; i < N; ++i) {
            arr[i] = Integer.parseInt(st.nextToken());
        }
    }

    private static long solve() {
        //중복 제거 & 오름차순 정렬
        List<Integer> order = compress();

        //order size 참고해 Index Tree 만들기.
        IndexTree indexTree = new IndexTree(order.size());

        //index Tree 이용해 swap 횟수 구하기
       long totalSwapCnt = 0;
        for(int i = N - 1; i >= 0; --i) {
            int idx = binarySearch(order, arr[i]);

            if(idx > 0) {
                totalSwapCnt += indexTree.rangeSum(idx - 1);
            }
            indexTree.update(idx);
        }

        return totalSwapCnt;
    }

    private static List<Integer> compress() {
        Set<Integer> set = new TreeSet<>();
        for(int i = 0; i < N; ++i) {
            set.add(arr[i]);
        }

        List<Integer> order = new ArrayList<>(set);
        return order;
    }

    private static int binarySearch(List<Integer> order, int key) {
        int lo = 0;
        int hi = order.size();
        while(lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;
            if(order.get(mid) <= key) {
                lo = mid;
            } else {
                hi = mid;
            }
        }
        return lo;
    }
    
}

class IndexTree {
    private int[] tree;

    public IndexTree(int leafSize) {
        int h = 1;
        while(true) {
            if(h >= leafSize) {
                break;
            }
            h *= 2;
        }

        tree = new int[h * 2 + 1];
    }

    public int rangeSum(int right) {

        int left = tree.length / 2;
        right += tree.length / 2;
        int sum = 0;
        while(left <= right) {
            if(left % 2 == 1) {
                sum += tree[left];
            }
            if(right % 2 == 0) {
                sum += tree[right];
            }

            left = (left + 1) / 2;
            right = (right - 1) / 2;
        }
        return sum;
    }

    public void update(int idx) {
        idx += tree.length / 2;

        tree[idx]++;
        while(idx > 1) {
            idx /= 2;
            tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
        }
    }
}
