import static java.lang.Math.*;

class Solution {
	public int solution(int[] money) {
		
		int length = money.length;
		int[] dp1 = new int[length];
		int[] dp2 = new int[length];
		
		for(int i = 0; i < length - 1; ++i) {
			dp1[i + 1] = money[i];
		}
		
		for(int i = 1; i < length; ++i) {
			dp2[i] = money[i];
		}
		
		for(int i = 2; i < length; ++i) {
			dp1[i] = max(dp1[i - 2] + dp1[i], dp1[i - 1]);
			dp2[i] = max(dp2[i - 2] + dp2[i], dp2[i - 1]);
		}

		return max(dp1[length - 1], dp2[length - 1]);
	}
}
