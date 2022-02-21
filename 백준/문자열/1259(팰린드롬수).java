package com.company;

import java.io.*;
import java.util.*;

public class Main {

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

		StringBuilder sb = new StringBuilder();
		String num;
		while(true) {
			num = br.readLine();
			if(num.equals("0")) {
				break;
			}

			int left = 0;
			int right = num.length() - 1;
			boolean isPalindrome = true;
			while(left < right) {
				if(num.charAt(left) == num.charAt(right)) {
					left++;
					right--;
				} else {
					isPalindrome = false;
					break;
				}
			}

			if(isPalindrome) {
				sb.append("yes\n");
			} else {
				sb.append("no\n");
			}
		}

		System.out.println(sb.toString());
	}

}

