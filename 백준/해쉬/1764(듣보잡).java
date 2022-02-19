package com.company;

import java.io.*;
import java.util.*;

public class Main {

	static int N;
	static int M;
	static Set<String> A = new HashSet<>();
	static List<String> B = new ArrayList<>();

	public static void main(String[] args) throws IOException {

		input();

		List<String> answers = new ArrayList<>();
		solve(answers);

		output(answers);
	}

	static void input() throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		StringTokenizer st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());

		for(int i = 0; i < N; ++i) {
			A.add(br.readLine());
		}
		for(int i = 0; i < M; ++i) {
			B.add(br.readLine());
		}
	}

	static void solve(List<String> answers) {
		for(int i = 0; i < M; ++i) {
			if(A.contains(B.get(i))) {
				answers.add(B.get(i));
			}
		}
		Collections.sort(answers);
	}

	static void output(List<String> answers) throws IOException {
		StringBuilder sb = new StringBuilder();

		sb.append(answers.size());
		sb.append("\n");
		for(String answer : answers) {
			sb.append(answer + "\n");
		}
		System.out.println(sb);
	}

}

