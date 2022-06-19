import java.util.ArrayList;
import java.util.List;

class Solution {

	private static final String INVALID = "invalid";

	private boolean[] isUsed = new boolean[26];

	public String solution(String sentence) {
		StringBuilder temp = new StringBuilder();
		StringBuilder answer = new StringBuilder();
		List<Integer> indices = new ArrayList<>();
		for (int i = 0; i < sentence.length(); ++i) {
			char c = sentence.charAt(i);
			if ('A' <= c && c <= 'Z') {
				temp.append(c);
				continue;
			}

			//특수 문자 중복 불가능
			if (this.isUsed[c - 'a']) {
				return INVALID;
			}

			//특수 문자 위치 정보 구하기.
			indices.clear();
			for (int j = i; j < sentence.length(); ++j) {
				if (sentence.charAt(j) == c) {
					indices.add(j);
				}
			}

			//rule2
			if ((indices.size() == 2) && (indices.get(1) - indices.get(0) >= 2)) {
				if (temp.length() > 0) {
					answer.append(temp).append(" ");
				}
				temp.setLength(0);

				isUsed[c - 'a'] = true;
				String word = sentence.substring(indices.get(0) + 1, indices.get(1));

				if (!isWord(word)) {
					word = decodeRule1(word);
					if (word.equals(INVALID)) {
						return INVALID;
					}
				}
				answer.append(word).append(" ");
				i = indices.get(1);
			} else { //rule1
				//단어간 중복 체크
				if (temp.length() == 0) {
					return INVALID;
				}
				if (indices.get(indices.size() - 1) == sentence.length() - 1) {
					return INVALID;
				}

				if (temp.length() > 1) {
					answer.append(temp.substring(0, temp.length() - 1)).append(" ");
				}
				temp.setLength(0);

				String word = sentence.substring(indices.get(0) - 1, indices.get(indices.size() - 1) + 2);
				word = decodeRule1(word);
				if (word.equals(INVALID)) {
					return INVALID;
				}
				answer.append(word).append(" ");
				i = indices.get(indices.size() - 1) + 1;
			}
		}
		if (temp.length() > 0) {
			answer.append(temp).append(" ");
		}
		return answer.substring(0, answer.length() - 1);
	}

	private String decodeRule1(String word) {
		//word가 Rule1을 만족하려면 길이가 홀수 여야 함.
		if (word.length() % 2 == 0) {
			return INVALID;
		}

		char c = word.charAt(1);

		if (('A' <= c && c <= 'Z') || this.isUsed[c - 'a']) {
			return INVALID;
		}
		
		this.isUsed[c - 'a'] = true;
		for (int i = 0; i < word.length(); ++i) {
			if (i % 2 == 1 && word.charAt(i) != c) {
				return INVALID;
			}
			if (i % 2 == 0) {
				if ('a' <= word.charAt(i) && word.charAt(i) <= 'z') {
					return INVALID;
				}
			}
		}
		return word.replace(String.valueOf(c), "");
	}

	private boolean isWord(String word) {
		for (char c : word.toCharArray()) {
			if ('a' <= c && c <= 'z') {
				return false;
			}
		}
		return true;
	}
}
