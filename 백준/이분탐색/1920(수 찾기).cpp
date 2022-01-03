#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve(int N, int M, vector<int>& A, vector<int>& searchNum, vector<int>& answers) {
	sort(A.begin(), A.end());

	for (int i = 0; i < M; ++i) {
		int num = searchNum[i];
		
		int lo = 0;
		int hi = N - 1;
		while (lo + 1< hi) {
			int mid = (lo + hi) / 2;
			if (A[mid] > num) {
				hi = mid;
			} 
			else {
				lo = mid;
			}
		}

		if (A[lo] == num || A[hi] == num) {
			answers[i] = 1;
		}
	}
}
void input(int& N, int& M, vector<int>& A, vector<int>& searchNum) {
	cin >> N;
	A.assign(N, 0);
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
	}
	cin >> M;
	searchNum.assign(M, 0);
	for (int i = 0; i < M; ++i) {
		cin >> searchNum[i];
	}
}
int main() {
	int N, M;
	vector<int> A;
	vector<int> searchNum;
	input(N, M, A, searchNum);

	vector<int> answers(M, 0);
	solve(N, M, A, searchNum, answers);

	for (int i = 0; i < answers.size(); ++i) {
		cout << answers[i] << '\n';
	}
	return 0;
}
