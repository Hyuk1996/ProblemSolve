#include <iostream>
#include <vector>
using namespace std;

int solve(int N, int M, vector<int>& arr) {
	int answer = 0;
	int left = 0;
	int right = 0;
	int curSum = arr[0];
	while (true) {
		while (curSum >= M) {
			if (curSum == M) {
				answer++;
			}
			if (left == right) {
				break;
			}
			curSum -= arr[left++];
		}

		if (right == N - 1) {
			break;
		}
		curSum += arr[++right];
	}
	return answer;
}
void input(int& N, int& M, vector<int>& arr) {
	cin >> N >> M;
	arr.assign(N, 0);
	for (int i = 0; i < N; ++i) {
		cin >> arr[i];
	}
}
int main() {
	int N, M;
	vector<int> arr;
	input(N, M, arr);

	int answer = solve(N, M, arr);
	cout << answer;
	return 0;
}
