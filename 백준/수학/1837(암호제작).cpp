#include <iostream>
#include <vector>
using namespace std;

int mod(string& P, int prime) {
	int result = 0;
	for (int i = 0; i < P.size(); ++i) {
		result = (result * 10 + (P[i] - '0')) % prime;
	}
	return result;
}
int main() {
	string P;
	int K;
	cin >> P >> K;

	//K 이하의 소수 구하기
	vector<int> visit(K + 1, false); //false: prime
	int prime = -1;
	for (int i = 2; i < K; ++i) {
		if (visit[i]) {
			continue;
		}
		if (mod(P, i) == 0) {
			prime = i;
			break;
		}
		
		for (int j = 2 * i; j < K; j += i) {
			visit[j] = true;
		}
	}

	if (prime == -1) {
		cout << "GOOD";
	}
	else {
		cout << "BAD " << prime;
	}
	return 0;
}
