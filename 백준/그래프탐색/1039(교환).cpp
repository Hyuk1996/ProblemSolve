#include <iostream>
#include <queue>
#include <unordered_map>>
#include <algorithm>
#include <string>
using namespace std;
string N;
int K;

void getCombination(string& num, queue<string>& q) {
	for (int i = 0; i < num.size(); ++i) {
		for (int j = i + 1; j < num.size(); ++j) {
			string tmp = num;
			swap(tmp[i], tmp[j]);
			if (tmp[0] == '0') {
				continue;
			}
			q.push(tmp);
		}
	}
}
int bfs() {
	queue<string> q;
	q.push(N);
	int curSwitchCount = 0;

	while (curSwitchCount < K) {
		int qSize = q.size();
		unordered_map<string, int> hash;
		for (int i = 0; i < qSize; ++i) {
			string num = q.front();
			q.pop();

			if (hash.find(num) != hash.end()) {
				continue;
			}

			hash[num] = 1;
			getCombination(num, q);
		}
		curSwitchCount++;
	}


	int answer = -1;
	while (!q.empty()) {
		string tmp = q.front();
		q.pop();

		answer = max(answer, stoi(tmp));
	}
	return answer;
}
void input() {
	cin >> N >> K;
}
int main() {
	input();
	int answer = bfs();
	cout << answer;
	return 0;
}
