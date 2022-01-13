#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int binarySearch(vector<int>& arr, int key) {
	int lo = -1;
	int hi = arr.size() - 1;
	int mid;
	while (lo + 1 < hi) {
		mid = lo + (hi - lo) / 2;
		if (arr[mid] >= key) {
			hi = mid;
		}
		else {
			lo = mid;
		}
	}
	return hi;
}
void solve(int N, vector<int>& arr, int& LisLen, vector<int>& LIS) {
	vector<int> v;
	vector<int> index(N);
	for (int i = 0; i < N; ++i) {
		if (v.empty() || v.back() < arr[i]) {
			v.push_back(arr[i]);
			index[i] = v.size() - 1;
		}
		else {
			int idx = binarySearch(v, arr[i]); // v 에서 arr[i]보다 같거나 처음으로 큰 수 찾기.
			v[idx] = arr[i];
			index[i] = idx;
		}
	}

	// v의 길이가 LIS
	LisLen = v.size();

	int tmp = v.size() - 1;
	stack<int> s;
	for (int i = N-1; i>=0; --i) {
		if (index[i] == tmp) {
			s.push(arr[i]);
			tmp--;
			if (tmp == -1) {
				break;
			}
		}
	}

	while (!s.empty()) {
		LIS.push_back(s.top());
		s.pop();
	}
}
void input(int& N, vector<int>& arr) {
	cin >> N;
	arr.assign(N, 0);
	for (int i = 0; i < N; ++i) {
		cin >> arr[i];
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int N;
	vector<int> arr;
	input(N, arr);

	int LisLen;
	vector<int> LIS;
	solve(N, arr, LisLen, LIS);

	cout << LisLen << '\n';
	for (int i = 0; i < LIS.size(); ++i) {
		cout << LIS[i] << ' ';
	}
	return 0;
}
