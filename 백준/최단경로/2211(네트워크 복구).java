import java.util.*;
import java.io.*;

class Node {
    int v;
    int w;

    Node(int v, int w) {
        this.v = v;
        this.w = w;
    }
}

class Pair implements Comparable<Pair>{
    int v;
    int dist;

    Pair(int v, int dist) {
        this.v = v;
        this.dist = dist;
    }

    @Override
    public int compareTo(Pair target) {
        if(this.dist > target.dist) {
            return 1;
        } else if(this.dist < target.dist) {
            return -1;
        } else {
            return 0;
        }
    }
}

public class Main {

    private static int N, M;
    private static ArrayList<ArrayList<Node>> graph;

    private static final int INF = 987654321;

    public static void main(String[] args) throws IOException {
        input();

        StringBuilder sb = new StringBuilder();
        solve(sb);

        System.out.println(sb.toString());
    }

    private static void input() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = null;

        st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());

        //그래프 만들기
        graph = new ArrayList<>();
        for(int i = 0; i <= N; ++i) {
            graph.add(new ArrayList<>());
        }

        int A, B, C;
        for(int i = 0; i < M; ++i) {
            st = new StringTokenizer(br.readLine());
            A = Integer.parseInt(st.nextToken());
            B = Integer.parseInt(st.nextToken());
            C = Integer.parseInt(st.nextToken());

            graph.get(A).add(new Node(B, C));
            graph.get(B).add(new Node(A, C));
        }
    }

    private static void solve(StringBuilder sb) {
        //다익스트라
        int[] distances = new int[N + 1];
        Arrays.fill(distances, INF);
        int[] parent = new int[N + 1];
        PriorityQueue<Pair> pq = new PriorityQueue<>();

        distances[1] = 0;
        pq.add(new Pair(1, 0));
        while(!pq.isEmpty()) {
            int curV = pq.peek().v;
            int dist = pq.peek().dist;
            pq.remove();

            if(dist > distances[curV]) {
                continue;
            }
            for(int i = 0; i < graph.get(curV).size(); ++i) {
                int nextV = graph.get(curV).get(i).v;
                int weight = graph.get(curV).get(i).w;

                if(weight + distances[curV] < distances[nextV]) {
                    distances[nextV] = weight + distances[curV];
                    parent[nextV] = curV;
                    pq.add(new Pair(nextV, distances[nextV]));
                }
            }
        }

        sb.append(N - 1 + "\n");
        for(int i = 2; i <= N; ++i) {
            sb.append(i + " " + parent[i] + "\n");
        }
    }
}

