package com.company;

import java.io.*;
import java.util.*;

public class Main {

	private static boolean[][] graph;
	private static int n;

	public static void main(String[] args) throws IOException {
		input();

		floydWarshall();

		output();
	}

	private static void input() throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		n = Integer.parseInt(br.readLine());
		graph = new boolean[n + 1][n + 1];
		StringTokenizer st;
		for(int i = 0; i < n; ++i) {
			st = new StringTokenizer(br.readLine());

			for(int j = 0; j < n; ++j) {
				graph[i][j] = st.nextToken().equals("1");
			}
		}
	}

	private static void floydWarshall() {
		for(int k = 0; k < n; ++k) {
			for(int i = 0; i < n; ++i) {
				for(int j = 0; j < n; ++j) {
					if(i == k || j == k) {
						continue;
					}

					if(graph[i][k] && graph[k][j]) {
						graph[i][j] = true;
					}
				}
			}
		}
	}

	private static void output() {
		StringBuilder sb = new StringBuilder();
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				if (graph[i][j]) {
					sb.append("1 ");
				} else {
					sb.append("0 ");
				}
			}
			sb.append("\n");
		}
		System.out.println(sb.toString());
	}

}

