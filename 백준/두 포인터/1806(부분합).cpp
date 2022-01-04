#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve(int N, int S, vector<int>& arr) {
	int answer = N + 1;
	int left = 0;
	int right = 0;
	int curSum = arr[0];
	while (true) {
		while (curSum >= S) {
			answer = min(answer, right - left + 1);
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
	if (answer == N + 1) {
		answer = 0;
	}
	return answer;
}
void input(int& N, int& S, vector<int>& arr) {
	cin >> N >> S;
	arr.assign(N, 0);
	for (int i = 0; i < N; ++i) {
		cin >> arr[i];
	}
}
int main() {
	int N, S;
	vector<int> arr;
	input(N, S, arr);

	int answer = solve(N, S, arr);
	cout << answer;
	return 0;
}
