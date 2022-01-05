#include <iostream>
#include <vector>
using namespace std;
const int MAX = 1000000;

bool check(vector<int>& indexTree, int end, int goal) {
	int startIdx = indexTree.size() / 2;

	int left = startIdx;
	int right = startIdx + end;
	int sum = 0;
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

	if (sum < goal) {
		return false;
	}
	else {
		return true;
	}
}
int getCandy(vector<int>& indexTree, int order) {
	int lo = 0;
	int hi = MAX - 1;

	if (check(indexTree, lo, order)) {
		hi = 0;
	}
	while (lo + 1 < hi) {
		int mid = lo + (hi - lo) / 2;
		if (check(indexTree, mid, order) == false) {
			lo = mid;
		}
		else {
			hi = mid;
		}
	}
	return 1 + hi;
}
void updateIndexTree(vector<int>& indexTree, int p, int changeVal) {
	int startIdx = indexTree.size() / 2;
	p += (startIdx - 1);
	indexTree[p] += changeVal;
	while (p > 1) {
		p /= 2;
		indexTree[p] = indexTree[p * 2] + indexTree[p * 2 + 1];
	}
}
void makeIndexTree(vector<int>& indexTree, vector<int>& candy) {
	int start = 1;
	while (start < MAX) {
		start *= 2;
	}

	indexTree.assign(start * 2, 0);
}
int main() {
	vector<int> answers;
	vector<int> candy(MAX + 1, 0);
	vector<int> indexTree;
	makeIndexTree(indexTree, candy);

	int N;
	cin >> N;
	while (N--) {
		int A, B, C;
		cin >> A;
		if (A == 1) {
			cin >> B;
			int candyVal = getCandy(indexTree, B);
			candy[candyVal]--;
			updateIndexTree(indexTree, candyVal, -1);
			answers.push_back(candyVal);
		}
		else {
			cin >> B >> C;
			candy[B] += C;
			updateIndexTree(indexTree, B, C);
		}
	}

	for (int i = 0; i < answers.size(); ++i) {
		cout << answers[i] << '\n';
	}
	return 0;
}
