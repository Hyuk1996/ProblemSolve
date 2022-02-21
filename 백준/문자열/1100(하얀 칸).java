package com.company;

import java.io.*;
import java.util.*;

public class Main {

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		int r = 0;
		String chess;
		int answer = 0;
		while(r < 8) {
			chess = br.readLine();
			for(int i = 0; i < chess.length(); ++i) {
				if((i + r) % 2 == 0 && chess.charAt(i) == 'F') {
					answer++;
				}
			}
			r++;
		}
		System.out.println(answer);
	}

}

