#include <iostream>
#include <vector>
using namespace std;

int solve(vector<vector<int>>& dp, vector<vector<int>>& map, int n, int m) {
	int maxRectangle = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (map[i][j] == 0) {
				dp[i][j] = 0;
			}
			else {
				dp[i][j] = map[i][j] + min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i][j - 1]));
				maxRectangle = max(maxRectangle, dp[i][j]);
			}
		}
	}
	return maxRectangle;
}
void input(int& n, int& m, vector<vector<int>>& map) {
	cin >> n >> m;
	map.assign(n + 1, vector<int>(m + 1, 0));
	for (int i = 1; i <= n; ++i) {
		string str;
		cin >> str;
		for (int j = 0; j < str.size(); ++j) {
			map[i][j + 1] = str[j] - '0';
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	vector<vector<int>> map;
	input(n, m, map);

	vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
	int answer = solve(dp, map, n, m);
	answer *= answer;
	cout << answer;
	return 0;
}
