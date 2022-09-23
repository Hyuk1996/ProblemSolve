package com.company.baekjoon;

import java.io.*;
import java.util.*;

public class Main {

	private static int N;
	private static int K;

	private static int[][] cache = new int[401][401];

	private static List<int[]> answers = new ArrayList<>();

	public static void main(String[] args) throws IOException {
		input();

		int candidate = N + K - 1;
		int choose = K - 1;

		System.out.println(getCombiCnt(candidate, choose));
	}

	private static void input() throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer tokens = new StringTokenizer(br.readLine());
		N = Integer.parseInt(tokens.nextToken());
		K = Integer.parseInt(tokens.nextToken());
	}

	private static int getCombiCnt(final int n, final int r) {

		if (r == 0 || n == r) {
			return 1;
		}
		if (r == 1) {
			return n;
		}

		if (cache[n - 1][r - 1] == 0) {
			cache[n - 1][r - 1] = getCombiCnt(n- 1, r - 1);
		}

		if (cache[n - 1][r] == 0) {
			cache[n - 1][r] = getCombiCnt(n - 1, r);
		}

		return (cache[n - 1][r - 1] + cache[n - 1][r]) % 1_000_000_000;
	}
}
