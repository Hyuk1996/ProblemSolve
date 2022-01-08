#include <iostream>
#include <vector>
using namespace std;

bool isPossible(vector<int>& col, int r) {
	for (int i = 0; i < r; ++i) {
		if (col[i] == col[r] || abs(col[r] - col[i]) == r - i) { // 같은 열 or 대각선에 존재하는 경우
			return false;
		}
	}
	return true;
}
void dfs(vector<int>& col, int r, int N, int& answer) {
	if (r == N) {
		++answer;
		return;
	}
	for (int i = 0; i < N; ++i) {
		col[r] = i;
		if (isPossible(col, r)) {
			dfs(col, r + 1, N, answer);
		}
	}
}
int main() {
	int N;
	cin >> N;

	int answer = 0;
	vector<int> col(N, 0); // col[i] = j : 체스판이 i 번째 row, j 번째 column에 존재
	dfs(col, 0, N, answer);

	cout << answer;
	return 0;
}
