import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;

class Solution {

	private static final String RULE_1_FAIL_EXP_MSG = "Rule 1 적용 불가능";
	private static final String SPACE = " ";
	private static final String SPACE_EXP_MSG = "공백이 있으면 안됨.";
	private static final String INVALID = "invalid";

	private Map<Character, List<Integer>> positions = new HashMap<>();

	public String solution(String sentence) {
		try {
			extractLowerCaseInfo(sentence);

			StringBuilder sb = new StringBuilder();
			StringBuilder answer = new StringBuilder();

			for (int i = 0; i < sentence.length(); ++i) {
				char c = sentence.charAt(i);
				if (Character.isUpperCase(c)) {
					sb.append(c);
					continue;
				}

				List<Integer> position = this.positions.get(c);

				if (position.size() == 2 && position.get(1) - position.get(0) >= 2) { //Rul2
					if (sb.length() > 0) {
						answer.append(sb).append(SPACE);
					}
					sb.setLength(0);

					String word = sentence.substring(position.get(0) + 1, position.get(1));
					if (!isValid(word)) {
						word = decodeUsingRule1(word, position.get(0) + 1, position.get(1) - 1);
					}

					answer.append(word).append(SPACE);
					i = position.get(1);
				} else { //Rule1
					if (sb.length() > 1) {
						answer.append(sb.substring(0, sb.length() - 1)).append(SPACE);
					}
					if (sb.length() == 0) {
						throw new IllegalArgumentException(RULE_1_FAIL_EXP_MSG);
					}
					sb.setLength(0);

					if (position.get(0) < i || position.get(position.size() - 1) + 1 >= sentence.length()) {
						throw new IllegalArgumentException(RULE_1_FAIL_EXP_MSG);
					}

					String word = sentence.substring(position.get(0) - 1, position.get(position.size() - 1) + 2);
					word = decodeUsingRule1(word, position.get(0) - 1, position.get(position.size() - 1) + 1);

					answer.append(word).append(SPACE);
					i = position.get(position.size() - 1) + 1;
				}
			}
			if (sb.length() > 0) {
				answer.append(sb).append(SPACE);
			}
			return answer.substring(0, answer.length() - 1);
		} catch (IllegalArgumentException e) {
			return INVALID;
		}
	}

	private void extractLowerCaseInfo(String sentence) {
		for (int i = 0; i < sentence.length(); ++i) {
			char c = sentence.charAt(i);
			if (Character.isWhitespace(c)) {
				throw new IllegalArgumentException(SPACE_EXP_MSG);
			}
			if (Character.isLowerCase(c)) {
				if (this.positions.containsKey(c)) {
					this.positions.get(c).add(i);
					continue;
				}
				List<Integer> position = new ArrayList<>();
				position.add(i);
				this.positions.put(c, position);
			}
		}
	}

	private boolean isValid(String word) {
		for (int i = 0; i < word.length(); ++i) {
			if (Character.isLowerCase(word.charAt(i))) {
				return false;
			}
		}
		return true;
	}

	private String decodeUsingRule1(String word, int start, int end) {
		if (word.length() % 2 == 0) {
			throw new IllegalArgumentException(RULE_1_FAIL_EXP_MSG);
		}

		List<Integer> position = this.positions.get(word.charAt(1));
		if (Objects.isNull(position)) {
			throw new IllegalArgumentException(RULE_1_FAIL_EXP_MSG);
		}

		if (position.get(0) != (start + 1) || position.get(position.size() - 1) != (end - 1)) {
			throw new IllegalArgumentException(RULE_1_FAIL_EXP_MSG);
		}

		char c = word.charAt(1);
		for (int i = 0; i < word.length(); ++i) {
			if (i % 2 == 1 && word.charAt(i) != c) {
				throw new IllegalArgumentException(RULE_1_FAIL_EXP_MSG);
			}
			if (i % 2 == 0 && Character.isLowerCase(word.charAt(i))) {
				throw new IllegalArgumentException(RULE_1_FAIL_EXP_MSG);
			}
		}
		return word.replace(String.valueOf(c), "");
	}
}
