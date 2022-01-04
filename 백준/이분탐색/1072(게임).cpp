#include <iostream>
using namespace std;
const int MAX = 1000000000;

bool change(long long X, long long Y, int Z, int add) {
	int tmpZ = ((Y + add)* 100) / (X + add);
	if (tmpZ == Z) {
		return false;
	}
	else {
		return true;
	}
}
int solve(long long X, long long Y) {
	int Z = (Y * 100) / X;

	if (Z == 100 || Z == 99)
		return -1;

	int lo = 0;
	int hi = MAX;
	while (lo + 1 < hi) {
		int mid = lo + (hi - lo) / 2;
		if (change(X, Y, Z, mid) == true) {
			hi = mid;
		}
		else {
			lo = mid;
		}
	}
	return hi;
}
void input(int& X, int& Y) {
	cin >> X >> Y;
}
int main() {
	int X, Y;
	input(X, Y);

	int answer = solve(X, Y);
	cout << answer;
	return 0;
}
