package com.company;

import java.io.*;
import java.util.*;

public class Main {

	private static int N;
	private static int[] arr;

	public static void main(String[] args) throws IOException {

		input();

		StringBuilder sb = new StringBuilder();
		solve(sb);

		System.out.println(sb.toString());
	}

	private static void input() throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		N = Integer.parseInt(br.readLine());
		arr = new int[N];
		for(int i = 0; i < N; ++i) {
			arr[i] = Integer.parseInt(br.readLine());
		}
	}

	private static void solve(StringBuilder sb) {

		Arrays.sort(arr);

		int median = arr[N / 2];
		int range = arr[N - 1] - arr[0];
		int mean = getMean();
		int mode = getMode();

		sb.append(mean + "\n");
		sb.append(median + "\n");
		sb.append(mode + "\n");
		sb.append(range);
	}

	private static int getMean() {
		int sum = 0;
		for(int num : arr) {
			sum += num;
		}
		return (int)Math.round((double)sum / N);
	}

	private static int getMode() {
		Map<Integer, Integer> map = new HashMap<>();
		for(int num : arr) {
			map.put(num, map.getOrDefault(num, 0) + 1);
		}

		List<Integer> modes = new ArrayList<>();
		int maxCnt = 0;
		for(Integer num : map.keySet()) {
			if(maxCnt < map.get(num)) {
				maxCnt = map.get(num);
				modes.clear();
				modes.add(num);
			} else if(maxCnt == map.get(num)) {
				modes.add(num);
			}
		}

		if(modes.size() > 1) {
			Collections.sort(modes);
			int first = modes.get(0);
			for(int i = 1; i < modes.size(); ++i) {
				if(first < modes.get(i)) {
					return modes.get(i);
				}
			}
		}
		return modes.get(0);
	}

}

