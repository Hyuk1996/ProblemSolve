#include <iostream>
#include <vector>
using namespace std;

int rangeSum(vector<int>& indexTree, int left, int right) {
	int startIdx = indexTree.size() / 2;
	left += startIdx - 1;
	right += startIdx - 1;
	int sum = 0;
	while (left <= right) {
		if (left % 2 == 1) {
			sum += indexTree[left];
		}
		if (right % 2 == 0) {
			sum += indexTree[right];
		}

		left = (left + 1) / 2;
		right = (right - 1) / 2;
	}
	return sum;
}
void makeIndexTree(vector<int>& arr, int N, vector<int>& indexTree) {
	int startIdx = 1;
	while (startIdx < N) {
		startIdx *= 2;
	}
	indexTree.assign(startIdx * 2, 0);

	for (int i = 1; i <= N; ++i) {
		indexTree[i + startIdx - 1] = arr[i];
	}
	for (int i = startIdx - 1; i > 0; --i) {
		indexTree[i] = indexTree[i * 2] + indexTree[i * 2 + 1];
	}
}
void setDp(vector<int>& arr, int N, vector<int>& dp) {
	dp[0] = arr[0];
	for (int i = 1; i <= N; ++i) {
		dp[i] = dp[i - 1] + arr[i];
	}
}
void input(int& N, int& M, vector<int>& arr) {
	cin >> N >> M;
	arr.assign(N+1, 0);
	for (int i = 1; i <= N; ++i) {
		cin >> arr[i];
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int N, M;
	vector<int> arr;
	input(N, M, arr);

	vector<int> indexTree;
	makeIndexTree(arr, N, indexTree);

	//indexTree 이용 풀이.
	vector<int> answers(M, 0);
	int a, b;
	for (int i = 0; i < M; ++i) {
		cin >> a >> b;
		answers[i] = rangeSum(indexTree, a, b);
	}

	/* DP이용 풀이
	vector<int> dp(N+1, 0);
	setDp(arr, N, dp);

	vector<int> answers(M, 0);
	int a, b;
	for (int i = 0; i < M; ++i) {
		cin >> a >> b;
		answers[i] = dp[b] - dp[a - 1];
	}*/

	
	for (int i = 0; i < M; ++i) {
		cout << answers[i] << '\n';
	}
	return 0;
}
