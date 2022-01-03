#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
const int LIMIT = 1000000000;

int main() {
	bool finish = false;
	while (true) {
		vector<pair<string, int>> cmds;
		while (true) {
			string cmd;
			cin >> cmd;
			if (cmd == "QUIT") {
				finish = true;
				break;
			}
			else if (cmd == "END") {
				break;
			}
			else if (cmd == "NUM") {
				int X;
				cin >> X;
				cmds.push_back(make_pair(cmd, X));
			}
			else {
				cmds.push_back(make_pair(cmd, 0));
			}
		}

		if (finish) {
			break;
		}

		int N;
		cin >> N;
		vector<int> nums(N, 0);
		for (int i = 0; i < N; ++i) {
			cin >> nums[i];
		}


		vector<string> answers;
		for (int i = 0; i < N; ++i) {
			stack<int> s;
			s.push(nums[i]);

			bool error = false;
			for (int j = 0; j < cmds.size(); ++j) {
				string cmd = cmds[j].first;
				int num = cmds[j].second;
				if (cmd == "NUM") {
					s.push(num);
				}
				else if (cmd == "POP") {
					if (s.empty()) {
						error = true;
						break;
					}
					s.pop();
				}
				else if (cmd == "INV") {
					if (s.empty()) {
						error = true;
						break;
					}
					int tmp = s.top();
					s.pop();
					tmp *= -1;
					s.push(tmp);
				}
				else if (cmd == "DUP") {
					if (s.empty()) {
						error = true;
						break;
					}
					int tmp = s.top();
					s.push(tmp);
				}
				else if (cmd == "SWP") {
					if (s.size() < 2) {
						error = true;
						break;
					}
					int first = s.top();
					s.pop();
					int second = s.top();
					s.pop();
					s.push(first);
					s.push(second);
				}
				else if (cmd == "ADD") {
					if (s.size() < 2) {
						error = true;
						break;
					}
					int first = s.top();
					s.pop();
					int second = s.top();
					s.pop();
					int tmp = second + first;
					if (abs(tmp) > LIMIT) {
						error = true;
						break;
					}
					s.push(tmp);
				}
				else if (cmd == "SUB") {
					if (s.size() < 2) {
						error = true;
						break;
					}
					int first = s.top();
					s.pop();
					int second = s.top();
					s.pop();
					int tmp = second - first;
					if (abs(tmp) > LIMIT) {
						error = true;
						break;
					}
					s.push(tmp);
				}
				else if (cmd == "MUL") {
					if (s.size() < 2) {
						error = true;
						break;
					}
					long long first = s.top();
					s.pop();
					long long second = s.top();
					s.pop();
					long long tmp = second * first;
					if (abs(tmp) > LIMIT) {
						error = true;
						break;
					}
					s.push(tmp);
				}
				else if (cmd == "DIV") {
					if (s.size() < 2) {
						error = true;
						break;
					}
					int first = s.top();
					s.pop();
					int second = s.top();
					s.pop();
					if (first == 0) {
						error = true;
						break;
					}
					int tmp = abs(second) / abs(first);
					int sign = 1;
					if ((first < 0 && second >= 0) || (first >= 0 && second < 0)) {
						sign = -1;
					}
					tmp *= sign;
					s.push(tmp);
				}
				else if (cmd == "MOD") {
					if (s.size() < 2) {
						error = true;
						break;
					}
					int first = s.top();
					s.pop();
					int second = s.top();
					s.pop();
					if (first == 0) {
						error = true;
						break;
					}
					int tmp = second % first;
					s.push(tmp);
				}
			}

			if (error || s.size() != 1) {
				answers.push_back("ERROR");
			}
			else {
				answers.push_back(to_string(s.top()));
			}
		}

		for (int i = 0; i < answers.size(); ++i) {
			cout << answers[i] << '\n';
		}
		cout << '\n';
	}
	return 0;
}
