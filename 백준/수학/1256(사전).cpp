#include <iostream>
#include <vector>
#include <string>
using namespace std;
const int MAXK = 1000000000;

string findWord(vector<vector<int>>& combi, int N, int M, int K) {
	string answer = "";
	if (K > combi[N + M][N]) {
		answer = to_string(-1);
	}
	else { //K번째 문자열 찾기
		while (N > 0 || M > 0) {
			if (K <= combi[N + M - 1][M]) {
				answer += "a";
				N--;
			}
			else {
				answer += "z";
				K -= combi[N + M - 1][M];
				M--;
			}
		}
	}
	return answer;
}
void getCombi(vector<vector<int>>& combi, int limit) {
	combi[0][0] = 1;
	for (int i = 1; i <= limit; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (j == 0 || j == i) {
				combi[i][j] = 1;
			}
			else {
				combi[i][j] = combi[i - 1][j - 1] + combi[i - 1][j];
				if (combi[i][j] > MAXK) {
					combi[i][j] = MAXK + 1;
				}
			}
		}
	}
}
int main() {
	int N, M;
	long long K;
	cin >> N >> M >> K;

	vector<vector<int>> combi(N + M + 1, vector<int>(N+M+1, 0));
	getCombi(combi, N + M);

	string answer = findWord(combi, N, M, K);
	cout << answer;
	return 0;
}
