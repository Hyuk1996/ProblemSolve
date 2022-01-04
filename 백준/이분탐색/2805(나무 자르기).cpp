#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool possible(vector<int>& trees, int height, int M) {
	long long getTree = 0;
	for (int i = 0; i < trees.size(); ++i) {
		if (trees[i] <= height) {
			continue;
		}
		getTree += (trees[i] - height);
	}

	if (getTree >= M) {
		return true;
	}
	else {
		return false;
	}
}
int solve(int N, int M, vector<int>& trees) {
	int hi = trees[0];
	for (int i = 1; i < N; ++i) {
		hi = max(hi, trees[i]);
	}
	int lo = 0;

	while (lo + 1 < hi) {
		int mid = lo + (hi - lo) / 2;
		if (possible(trees, mid, M)) {
			lo = mid;
		}
		else {
			hi = mid;
		}
	}
	return lo;
}
void input(int& N, int& M, vector<int>& trees) {
	cin >> N >> M;
	trees.assign(N, 0);
	for (int i = 0; i < N; ++i) {
		cin >> trees[i];
	}
}
int main() {
	int N, M;
	vector<int> trees;
	input(N, M, trees);

	int answer = solve(N, M, trees);
	cout << answer;
	return 0;
}
