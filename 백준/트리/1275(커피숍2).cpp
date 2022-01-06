#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void updateIndexTree(vector<long long>& indexTree, int p, int num) {
	int startIdx = indexTree.size() / 2;
	p += startIdx - 1;
	indexTree[p] = num;
	while (p > 1) {
		p /= 2;
		indexTree[p] = indexTree[p * 2] + indexTree[p * 2 + 1];
	}
}
long long getRangeSum(vector<long long>& indexTree, int left, int right) {
	int startIdx = indexTree.size() / 2;
	left += startIdx - 1;
	right += startIdx - 1;
	long long sum = 0;
	while (left <= right) {
		if (left % 2 == 1) {
			sum += indexTree[left];
		}
		if (right % 2 == 0) {
			sum += indexTree[right];
		}
		left = (left + 1) / 2;
		right = (right - 1) / 2;
	}
	return sum;
}
void makeIndexTree(vector<long long>& indexTree, vector<int>& arr, int N) {
	int startIdx = 1;
	while (startIdx < N) {
		startIdx *= 2;
	}

	indexTree.assign(startIdx * 2, 0);
	for (int i = 1; i <= N; ++i) {
		indexTree[startIdx + i - 1] = arr[i];
	}

	for (int i = startIdx - 1; i > 0; --i) {
		indexTree[i] = indexTree[i * 2] + indexTree[i * 2 + 1];
	}
}
void input(int& N, int& Q, vector<int>& arr) {
	cin >> N >> Q;
	arr.assign(N + 1, 0);
	for (int i = 1; i <= N; ++i) {
		cin >> arr[i];
	}
}
int main() {
	int N, Q;
	vector<int> arr;
	input(N, Q, arr);

	vector<long long> indexTree;
	makeIndexTree(indexTree, arr, N);

	vector<long long> answers(Q, 0);
	for (int i = 0; i < Q; ++i) {
		int x, y, a, b;
		cin >> x >> y >> a >> b;
		if (x > y) {
			swap(x, y);
		}
		answers[i] = getRangeSum(indexTree, x, y);
		updateIndexTree(indexTree, a, b);
	}

	for (int i = 0; i < Q; ++i) {
		cout << answers[i] << '\n';
	}
	return 0;
}
