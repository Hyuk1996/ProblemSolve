#include <iostream>
using namespace std;

long long factorial(int N) {
	if (N == 0) {
		return 1;
	}
	return N * factorial(N - 1);
}
int main() {
	int N, K;
	cin >> N >> K;

	cout << factorial(N) / (factorial(N - K) * factorial(K));
	return 0;
}
