#include <iostream>
#include <vector>
using namespace std;

long long dp(int N, vector<int>& arr, int result) {
	vector<vector<long long>> cache(N - 1, vector<long long>(21, 0));

	// cache[i][j] : i번째 수까지 연산값이 j인 경우의 수
	cache[0][arr[0]] = 1;
	for (int i = 1; i < N - 1; ++i) {
		for (int j = 0; j <= 20; ++j) {
			if (cache[i - 1][j] == 0) {
				continue;
			}

			if (j + arr[i] <= 20) {
				cache[i][j + arr[i]] += cache[i - 1][j];
			}
			if (j - arr[i] >= 0) {
				cache[i][j - arr[i]] += cache[i - 1][j];
			}
		}
	}
	return cache[N - 2][result];
}
void input(int& N, vector<int>& arr, int& result) {
	cin >> N;
	arr.assign(N - 1, 0);
	for (int i = 0; i < N - 1; ++i) {
		cin >> arr[i];
	}
	cin >> result;
}
int main() {
	int N, result;
	vector<int> arr;
	input(N, arr, result);

	long long answer = dp(N, arr, result);
	cout << answer;
	return 0;
}
