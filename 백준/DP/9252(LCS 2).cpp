#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

string getLcs(vector<vector<int>>& dp, string& str1, string& str2) {
	stack<char> reverseLcs;
	int r = str2.size() - 1;
	int c = str1.size() - 1;
	int curLen;
	while (r > 0 && c > 0) {
		curLen = dp[r][c];
		if (curLen > dp[r - 1][c] && curLen > dp[r][c - 1]) {
			reverseLcs.push(str2[r]);
			r--;
			c--;
		}
		else {
			if (curLen == dp[r - 1][c]) {
				r--;
			}
			else {
				c--;
			}
		}
	}

	string lcs = "";
	while (!reverseLcs.empty()) {
		lcs += reverseLcs.top();
		reverseLcs.pop();
	}
	return lcs;
}
void setDp(vector<vector<int>>& dp, string& str1, string& str2) {
	for (int i = 1; i < str2.size(); ++i) {
		for (int j = 1; j < str1.size(); ++j) {
			if (str2[i] == str1[j]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	string str1, str2;
	cin >> str1 >> str2;
	str1 = " " + str1;
	str2 = " " + str2;

	vector<vector<int>> dp(str2.size(), vector<int>(str1.size(), 0));
	setDp(dp, str1, str2);

	int LcsLen = dp[str2.size() - 1][str1.size() - 1];
	cout << LcsLen << '\n';
	if (LcsLen != 0) {
		string Lcs = getLcs(dp, str1, str2);
		cout << Lcs;
	}
	return 0;
}
