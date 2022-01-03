#include <iostream>
#include <vector>
#include <string>
using namespace std;
const int dr[4] = { 0, 0, -1, 1 };
const int dc[4] = { -1, 1, 0, 0 };

bool dfs(vector<string>& board, int r, int c, int curMove, int& answer, vector<vector<bool>>& visit, vector<vector<int>>& cache) {
	visit[r][c] = true;
	cache[r][c] = curMove;
	int x = board[r][c] - '0';

	for (int i = 0; i < 4; ++i) {
		int nextR = r + dr[i] * x;
		int nextC = c + dc[i] * x;

		if (nextR < 0 || nextR >= board.size() || nextC < 0 || nextC >= board[r].size()) {
			answer = max(answer, curMove);
			continue;
		}

		if (board[nextR][nextC] == 'H') {
			answer = max(answer, curMove);
			continue;
		}

		if (cache[nextR][nextC] > 0 && cache[nextR][nextC] > curMove) {
			continue;
		}

		// cycle 생성
		if (visit[nextR][nextC]) {
			answer = -1;
			return false;
		}

		if (!dfs(board, nextR, nextC, curMove + 1, answer, visit, cache)) {
			return false;
		}
	}
	visit[r][c] = false;
	return true;
}
int solve(int N, int M, vector<string>& board) {
	vector<vector<bool>> visit(N, vector<bool>(M, false));
	vector<vector<int>> cache(N, vector<int>(M, 0));
	int answer = 0;
	dfs(board, 0, 0, 1, answer, visit, cache);

	return answer;
}
void input(int& N, int& M, vector<string>& board) {
	cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		string info;
		cin >> info;
		board.push_back(info);
	}
}
int main() {
	int N, M;
	vector<string> board;
	input(N, M, board);
	int answer = solve(N, M, board);
	cout << answer;
	return 0;
}
