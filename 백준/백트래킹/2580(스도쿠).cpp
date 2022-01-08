#include <iostream>
#include <vector>
using namespace std;
const int SIZE = 9;

bool check(vector<vector<int>>& sudoku, int r, int c, int num) {
	//가로줄 확인
	for (int i = 0; i < SIZE; ++i) {
		if (sudoku[r][i] == num) {
			return false;
		}
	}
	//세로줄 확인
	for (int i = 0; i < SIZE; ++i) {
		if (sudoku[i][c] == num) {
			return false;
		}
	}

	// 3x3 정사각형 확인
	r = (r / 3) * 3;
	c = (c / 3) * 3;
	for (int i = r; i < r + 3; ++i) {
		for (int j = c; j < c + 3; ++j) {
			if (sudoku[i][j] == num) {
				return false;
			}
		}
	}

	return true;
}
bool backTracking(vector<vector<int>>& sudoku, int idx, vector<pair<int, int>>& empty) {
	if (idx == empty.size()) {
		return true;
	}

	int r = empty[idx].first;
	int c = empty[idx].second;
	for (int i = 1; i <= 9; ++i) {
		if (check(sudoku, r, c, i)) {
			sudoku[r][c] = i;
			if (backTracking(sudoku, idx + 1, empty)) {
				return true;
			}
			sudoku[r][c] = 0;
		}
	}
	return false;
}
void input(vector<vector<int>>& sudoku, vector<pair<int, int>>& empty) {
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			cin >> sudoku[i][j];
			if (sudoku[i][j] == 0) {
				empty.push_back(make_pair(i, j));
			}
		}
	}
}
int main() {
	vector<vector<int>> sudoku(9, vector<int>(9, 0));
	vector<pair<int, int>> empty;
	input(sudoku, empty);

	backTracking(sudoku, 0, empty);

	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			cout << sudoku[i][j] << ' ';
		}
		cout << '\n';
	}
	return 0;
}
