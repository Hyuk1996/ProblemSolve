#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int solve(vector<vector<int>>& dp, string& str, string& str2) {
	int answer = 0;
	for (int i = 0; i < str.size(); ++i) {
		for (int j = 0; j < str2.size(); ++j) {
			if (str[i] != str2[j]) {
				dp[i][j] = 0;
			}
			else {
				if (i - 1 < 0 || j - 1 < 0) {
					dp[i][j] = 1;
				}
				else {
					dp[i][j] = dp[i - 1][j - 1] + 1;
					answer = max(answer, dp[i][j]);
				}
			}
		}
	}
	return answer;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	string str, str2;
	cin >> str >> str2;

	vector<vector<int>> dp(str.size(), vector<int>(str2.size(), 0));
	int answer = solve(dp, str, str2);

	cout << answer;
	return 0;
}
