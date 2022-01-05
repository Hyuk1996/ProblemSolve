#include <iostream>
#include <vector>
using namespace std;


void showIndexTree(vector<long long>& indexTree) {
	for (int i = 1; i < indexTree.size(); ++i) {
		cout << indexTree[i] << ' ';
	}
}
long long getRangeSum(vector<long long>& indexTree, int start, int end) {
	int startIndex = indexTree.size() / 2;
	int left = start + startIndex - 1;
	int right = end + startIndex - 1;
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
void updateIndexTree(vector<long long>& indexTree, int p, long long num) {
	int startIndex = indexTree.size() / 2;

	int curP = p + startIndex - 1;
	indexTree[curP] = num;
	while (curP > 1) {
		int parent = curP / 2;
		indexTree[parent] = indexTree[parent * 2] + indexTree[parent * 2 + 1];
		curP = parent;
	}
}
void makeIndexTree(vector<long long>& arr, vector<long long>& indexTree, int N) {
	int startIndex = 1;
	while (startIndex < N) {
		startIndex *= 2;
	}

	indexTree.assign(startIndex * 2, 0);
	for (int i = 1; i <= N; ++i) {
		indexTree[i + startIndex - 1] = arr[i];
	}

	for (int i = startIndex-1; i > 0; --i) {
		indexTree[i] = indexTree[i * 2] + indexTree[i * 2 + 1];
	}
}
void input(int& N, int& M, int& K, vector<long long>& arr) {
	cin >> N >> M >> K;
	arr.assign(N + 1, 0);
	for (int i = 1; i <= N; ++i) {
		cin >> arr[i];
	}
}
int main() {
	int N, M, K;
	vector<long long> arr;
	input(N, M, K, arr);

	vector<long long> indexTree;
	makeIndexTree(arr, indexTree, N);

	vector<long long> answers;
	while (M > 0 || K > 0) {
		long long a, b, c;
		cin >> a >> b >> c;
		if (a == 1) {
			M--;
			updateIndexTree(indexTree, b, c);
		}
		else if (a == 2) {
			K--;
			answers.push_back(getRangeSum(indexTree, b, c));
		}
	}

	for (int i = 0; i < answers.size(); ++i) {
		cout << answers[i] << '\n';
	}
	return 0;
}
