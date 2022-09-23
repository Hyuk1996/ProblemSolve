package com.company.baekjoon;

import java.io.*;
import java.util.*;

public class Main {

	private static int N;
	private static int M;
	private static int[] combi;

	private static List<int[]> answers = new ArrayList<>();

	public static void main(String[] args) throws IOException {
		input();

		combi = new int[M];
		duplicateCombination(1, 0);

		print();
	}

	private static void input() throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer tokens = new StringTokenizer(br.readLine());
		N = Integer.parseInt(tokens.nextToken());
		M = Integer.parseInt(tokens.nextToken());
	}

	private static void duplicateCombination(final int start, final int depth) {
		if (depth == M) {
			answers.add(combi.clone());
			return;
		}

		for (int i = start; i <= N; ++i) {
			combi[depth] = i;
			duplicateCombination(i, depth + 1);
		}
	}

	private static void print() {
		StringBuilder sb = new StringBuilder();
		for (int[] answer : answers) {
			for (int num : answer) {
				sb.append(num).append(' ');
			}
			sb.append('\n');
		}
		System.out.print(sb);
	}
}
