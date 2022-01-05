#include <iostream>
#include <vector>
using namespace std;
const int MAX = 10001;

class Stack {
private:
	int arr[MAX];
	int topIdx = -1;

public:
	void push(int x) {
		arr[++topIdx] = x;
	}

	int pop() {
		if (topIdx == -1)
			return -1;
		int tmp = arr[topIdx];
		topIdx--;
		return tmp;
	}

	int size() {
		return topIdx + 1;
	}

	int empty() {
		if (topIdx == -1) {
			return 1;
		}
		else {
			return 0;
		}
	}

	int top() {
		if (topIdx == -1) {
			return -1;
		}
		return arr[topIdx];
	}
};

int main() {
	Stack s;
	vector<int> answers;

	int N;
	cin >> N;
	while (N--) {
		string cmd;
		cin >> cmd;

		if (cmd == "push") {
			int x;
			cin >> x;
			s.push(x);
		}
		else if (cmd == "pop") {
			int tmp = s.pop();
			answers.push_back(tmp);
		}
		else if (cmd == "size") {
			int tmp = s.size();
			answers.push_back(tmp);
		}
		else if (cmd == "empty") {
			int tmp = s.empty();
			answers.push_back(tmp);
		}
		else if (cmd == "top") {
			int tmp = s.top();
			answers.push_back(tmp);
		}
	}

	for (int i = 0; i < answers.size(); ++i) {
		cout << answers[i] << '\n';
	}
}
