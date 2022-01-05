#include <iostream>
#include <vector>
using namespace std;
const int MAX = 10001;

class Queue {
private:
	int arr[MAX];
	int frontIdx = 0;
	int backIdx = -1;

public:
	void push(int x) {
		arr[++backIdx] = x;
	}

	int pop() {
		if (frontIdx > backIdx) {
			return -1;
		}
		int tmp = arr[frontIdx++];
		return tmp;
	}

	int size() {
		if (frontIdx > backIdx) {
			return 0;
		}
		return backIdx - frontIdx + 1;
	}

	int empty() {
		if (frontIdx > backIdx) {
			return 1;
		}
		else {
			return 0;
		}
	}

	int front() {
		if (frontIdx > backIdx) {
			return -1;
		}
		return arr[frontIdx];
	}

	int back() {
		if (frontIdx > backIdx) {
			return -1;
		}
		return arr[backIdx];
	}
};

int main() {
	Queue q;
	vector<int> answers;

	int N;
	cin >> N;
	while (N--) {
		string cmd;
		cin >> cmd;

		if (cmd == "push") {
			int x;
			cin >> x;
			q.push(x);
		}
		else if (cmd == "pop") {
			answers.push_back(q.pop());
		}
		else if (cmd == "size") {
			answers.push_back(q.size());
		}
		else if (cmd == "empty") {
			answers.push_back(q.empty());
		}
		else if (cmd == "front") {
			answers.push_back(q.front());
		}
		else if (cmd == "back") {
			answers.push_back(q.back());
		}
	}

	for (int i = 0; i < answers.size(); ++i) {
		cout << answers[i] << '\n';
	}
	return 0;
}
