#include <iostream>
#include <vector>
using namespace std;

void getPrime(int N, vector<int>& primes) {
	vector<bool> visit(N + 1, false);

	for (int i = 2; i <= N; ++i) {
		if (visit[i]) { // 소수 아닌 경우
			continue;
		}

		for (int j = i * 2; j <= N; j += i) {
			visit[j] = true;
		}
	}

	for (int i = 2; i <= N; ++i) {
		if (visit[i] == false) {
			primes.push_back(i);
		}
	}
}
int main() {
	int N;
	cin >> N;

	vector<int> primes;
	getPrime(N, primes);
	
	int answer = 0;
	if (!primes.empty()) {
		int left = 0;
		int right = 0;
		int sum = primes[right];
		while (true) {
			while (sum >= N) {
				if (sum == N) {
					++answer;
				}
				if (left == right) {
					break;
				}
				sum -= primes[left++];
			}

			if (right == (primes.size() - 1)) {
				break;
			}
			sum += primes[++right];
		}
	}

	cout << answer;
	return 0;
}
