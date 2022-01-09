#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int upperBound(vector<int>& arr, int key) {
	int lo = 0;
	int hi = arr.size();
	while (lo + 1 < hi) {
		int mid = lo + (hi - lo) / 2;
		if (arr[mid] <= key) {
			lo = mid;
		}
		else {
			hi = mid;
		}
	}

	if (arr[lo] != key) {
		return -1;
	}
	return lo;
}
int lowerBound(vector<int>& arr, int key) {
	int lo = -1;
	int hi = arr.size() - 1;
	while (lo + 1 < hi) {
		int mid = lo + (hi - lo) / 2;
		if (arr[mid] >= key) {
			hi = mid;
		}
		else {
			lo = mid;
		}
	}

	if (arr[hi] != key) {
		return -1;
	}
	return hi;
}
void getAllSum(vector<int>& v, vector<int>& v2, vector<int>& sum) {
	for (int i = 0; i < v.size(); ++i) {
		for (int j = 0; j < v2.size(); ++j) {
			sum.push_back(v[i] + v2[j]);
		}
	}
}
long long solve(int n, vector<vector<int>>& arr) {
	long long answer = 0;
	
	vector<int> sumA;
	getAllSum(arr[0], arr[1], sumA);

	vector<int> sumB;
	getAllSum(arr[2], arr[3], sumB);
	
	sort(sumA.begin(), sumA.end());
	for (int j = 0; j < sumB.size(); ++j) {
		int sum = (sumB[j] * -1);
		long long lo = lowerBound(sumA, sum);
		long long up = upperBound(sumA, sum);

		if (lo != -1 && up != -1) {
			answer += (up - lo + 1);
		}
	}

	return answer;
}
void input(int& n, vector<vector<int>>& arr) {
	cin >> n;
	arr.assign(4, vector<int>(n, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 4; ++j) {
			cin >> arr[j][i];
		}
	}
}
int main() {
	int n;
	vector<vector<int>> arr;
	input(n, arr);

	long long answer = solve(n, arr);
	cout << answer;
	return 0;
}
