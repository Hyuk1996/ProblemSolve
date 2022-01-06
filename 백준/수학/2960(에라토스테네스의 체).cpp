#include <iostream>
#include <vector>
using namespace std;

int main() {
	int N, K;
	cin >> N >> K;

	int answer = 0;
	vector<bool> visit(N + 1, false); //false: prime
	for (int i = 2; i <= N; ++i) {
		if (visit[i]) {
			continue;
		}

		for (int j = i; j <= N; j += i) {
			if (visit[j]) {
				continue;
			}

			visit[j] = true;
			K--;
			if (K == 0) {
				answer = j;
				break;
			}
		}

		if (answer != 0) {
			break;
		}
	}

	cout << answer;
	return 0;
}
