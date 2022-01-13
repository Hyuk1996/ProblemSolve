#include <iostream>
#include <vector>
using namespace std;

void setDp(vector<vector<int>>& dp, vector<vector<int>>& table, int N) {
	dp.assign(N + 1, vector<int>(N+1, 0));
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			dp[i][j] = dp[i - 1][j]+ dp[i][j - 1] + table[i][j] - dp[i - 1][j - 1];
		}
	}
}
void input(int& N, int& M, vector<vector<int>>& table) {
	cin >> N >> M;
	table.assign(N + 1, vector<int>(N + 1, 0));
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			cin >> table[i][j];
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int N, M;
	vector<vector<int>> table;
	input(N, M, table);

	vector<vector<int>> dp; // dp[i][j] 는 dp[1][1] 부터 dp[i][j] 까지의 합
	setDp(dp, table, N);

	vector<int> answers(M, 0);
	int x1, y1, x2, y2;
	int sum = 0;
	for (int i = 0; i < M; ++i) {
		cin >> x1 >> y1 >> x2 >> y2;
		answers[i] = dp[x2][y2] - dp[x2][y1 - 1] - dp[x1 - 1][y2] + dp[x1 - 1][y1 - 1];
	}

	for (int i = 0; i < M; ++i) {
		cout << answers[i] << '\n';
	}
	return 0;
}
