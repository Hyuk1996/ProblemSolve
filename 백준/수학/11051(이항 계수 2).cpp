#include <iostream>
#include <vector>
using namespace std;
const int MOD = 10007;

void getCombi(vector<vector<int>>& combi, int N) {
	combi[0][0] = 1;
	for (int i = 1; i <= N; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (j == 0 || j == N) {
				combi[i][j] = 1;
			}
			else {
				combi[i][j] = (combi[i - 1][j - 1] + combi[i - 1][j]) % MOD;
			}
		}
	}
}
int main() {
	int N, K;
	cin >> N >> K;

	vector<vector<int>> combi(N + 1, vector<int>(N+1, 0));
	getCombi(combi, N);

	cout << combi[N][K];
	return 0;
}
