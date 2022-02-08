import java.util.*;
import java.io.*;

class Node {
    int v, w;

    public Node(int v, int w) {
        this.v = v;
        this.w = w;
    }
}

class Pair implements Comparable<Pair> {
    int v, dist;

    public Pair(int v, int dist) {
        this.v = v;
        this.dist = dist;
    }

    @Override
    public int compareTo(Pair target) {
        if(dist > target.dist) {
            return 1;
        } else if(dist < target.dist) {
            return -1;
        } else {
            return 0;
        }
    }
}

public class Main {

    private static int n, m, r;
    private static int[] items;
    private static ArrayList<ArrayList<Node>> graph;

    private static final int INF = 987654321;

    public static void main(String[] args) throws IOException {

        input();

        int answer = solve();

        output(answer);
    }

    private static void input() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = null;

        st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());
        r = Integer.parseInt(st.nextToken());

        items = new int[n + 1];
        st = new StringTokenizer(br.readLine());
        for(int i = 1; i <= n; ++i) {
            items[i] = Integer.parseInt(st.nextToken());
        }

        //그래프 만들기
        graph = new ArrayList<>();
        for(int i = 0; i <= n; ++i) {
            graph.add(new ArrayList<>());
        }

        int a, b, l;
        for(int i = 0; i < r; ++i) {
            st = new StringTokenizer(br.readLine());
            a = Integer.parseInt(st.nextToken());
            b = Integer.parseInt(st.nextToken());
            l = Integer.parseInt(st.nextToken());

            graph.get(a).add(new Node(b, l));
            graph.get(b).add(new Node(a, l));
        }
    }

    private static int solve() {

        int maxItemsCnt = 0;
        
        for(int i = 1; i <= n; ++i) {
            maxItemsCnt = Math.max(maxItemsCnt, getItem(i));
        }

        return maxItemsCnt;
    }

    //startV에서 시작할 때 얻을 수 있는 item 개수 return
    private static int getItem(int startV) {
        int[] dists = new int[n + 1];
        Arrays.fill(dists, INF);
        PriorityQueue<Pair> minHeap = new PriorityQueue<>();

        dists[startV] = 0;
        minHeap.add(new Pair(startV, 0));
        while(!minHeap.isEmpty()) {
            Pair Pair = minHeap.poll();
            int curV = Pair.v;
            int curDist = Pair.dist;

            if(curDist > dists[curV]) {
                continue;
            }
            for(int i = 0; i < graph.get(curV).size(); ++i) {
                int nextV = graph.get(curV).get(i).v;
                int weight = graph.get(curV).get(i).w;

                if(weight + curDist < dists[nextV]) {
                    dists[nextV] = weight + curDist;
                    minHeap.add(new Pair(nextV, dists[nextV]));
                }
            }
        }

        int totalItems = 0;
        for(int i = 1; i <= n; ++i) {
            if(dists[i] <= m) {
                totalItems += items[i];
            }
        }
        return totalItems;
    }

    private static void output(int answer) {
        System.out.println(answer);
    }
}

