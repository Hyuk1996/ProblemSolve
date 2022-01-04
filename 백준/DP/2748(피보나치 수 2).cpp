#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n;
	cin >> n;

	long long a = 0;
	long long b = 1;
	for (int i = 2; i <= n; ++i) {
		long long tmp = a + b;
		a = b;
		b = tmp;
	}
	cout << b;
	return 0;
}
