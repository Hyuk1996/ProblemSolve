import java.io.*;
import java.util.*;

public class Main {

	private static int N;
	private static int M;
	private static Edge[] edges;

	public static void main(String[] args) throws IOException {
		input();

		long[] dists = bellmanFord();

		printAnswer(isCycle(dists), dists);
	}

	private static void input() throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer tokens = new StringTokenizer(br.readLine());
		N = Integer.parseInt(tokens.nextToken());
		M = Integer.parseInt(tokens.nextToken());

		edges = new Edge[M];
		for (int i = 0; i < M; ++i) {
			tokens = new StringTokenizer(br.readLine());
			edges[i] = new Edge(
				Integer.parseInt(tokens.nextToken()),
				Integer.parseInt(tokens.nextToken()),
				Integer.parseInt(tokens.nextToken())
			);
		}
	}

	private static long[] bellmanFord() {
		long[] dists = new long[N + 1];
		Arrays.fill(dists, Long.MAX_VALUE);
		dists[1] = 0;

		for (int i = 0; i < N - 1; ++i) {
			for (int j = 0; j < M; ++j) {
				int from = edges[j].v;
				int to = edges[j].u;
				int weight = edges[j].w;

				if (dists[from] == Long.MAX_VALUE) {
					continue;
				}

				dists[to] = Math.min(dists[to], dists[from] + weight);
			}
		}

		return dists;
	}

	private static boolean isCycle(long[] dists) {
		//음의 cycle 확인
		for (int i = 0; i < M; ++i) {
			int from = edges[i].v;
			int to = edges[i].u;
			int weight = edges[i].w;

			if (dists[from] == Long.MAX_VALUE) {
				continue;
			}

			if (dists[to] > dists[from] + weight) {
				return true;
			}
		}
		return false;
	}

	private static void printAnswer(boolean isCycle, long[] dists) {
		if (isCycle) {
			System.out.println(-1);
		} else {
			for (int i = 2; i < dists.length; ++i) {
				if (dists[i] == Long.MAX_VALUE) {
					dists[i] = -1;
				}
				System.out.println(dists[i]);
			}
		}
	}

	static class Edge {
		int v, u, w;

		Edge(int v, int u, int w) {
			this.v = v;
			this.u = u;
			this.w = w;
		}
	}
}
