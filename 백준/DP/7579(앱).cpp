#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve(int N, int M, vector<int>& memory, vector<int>& cost, vector<vector<int>>& dp) {
	int maxCost = 0;
	for (int i = 1; i <= N; ++i) {
		maxCost += cost[i];
	}
	dp.assign(maxCost + 1, vector<int>(N + 1, 0));
	for (int i = 1; i <= N; ++i) {
		for (int j = 0; j <= maxCost; ++j) {
			if (cost[i] > j) {
				dp[j][i] = dp[j][i - 1];
			}
			else {
				dp[j][i] = max(dp[j - cost[i]][i - 1] + memory[i], dp[j][i - 1]);
			}
		}
	}

	int minCost = maxCost;
	for (int i = 0; i <= maxCost; ++i) {
		if (dp[i][N] >= M) {
			minCost = i;
			break;
		}
	}
	return minCost;
}
void input(int& N, int& M, vector<int>& memory, vector<int>& cost) {
	cin >> N >> M;
	memory.assign(N + 1, 0);
	cost.assign(N + 1, 0);
	for (int i = 1; i <= N; ++i) {
		cin >> memory[i];
	}
	for (int i = 1; i <= N; ++i) {
		cin >> cost[i];
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int N, M;
	vector<int> memory;
	vector<int> cost;
	input(N, M, memory, cost);

	vector<vector<int>> dp;
	int answer = solve(N, M, memory, cost, dp);

	cout << answer;
	return 0;
}
