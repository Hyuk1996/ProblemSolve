#include <iostream>
#include <queue>
using namespace std;

int main() {
	int N;
	cin >> N;

	priority_queue<int, vector<int>, greater<int> > minHeap;
	priority_queue<int, vector<int>, less<int> > maxHeap;
	vector<int> answers(N, 0);
	for (int i = 0; i < N; ++i) {
		int num;
		cin >> num;
		if (maxHeap.size() > minHeap.size()) {
			minHeap.push(num);
		}
		else {
			maxHeap.push(num);
		}

		if (!maxHeap.empty() && !minHeap.empty()) {
			if (maxHeap.top() > minHeap.top()) {
				int maxNum = maxHeap.top();
				int minNum = minHeap.top();
				maxHeap.pop();
				minHeap.pop();
				maxHeap.push(minNum);
				minHeap.push(maxNum);
			}
		}

		answers[i] = maxHeap.top();
	}


	for (int i = 0; i < N; ++i) {
		cout << answers[i] << '\n';
	}
	return 0;
}
