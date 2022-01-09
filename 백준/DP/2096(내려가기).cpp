#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX = 3;

int main() {
	int N;
	vector<int> gameMap(MAX, 0);
	vector<int> maxPrev(MAX, 0);
	vector<int> minPrev(MAX, 0);
	vector<int> maxCur(MAX, 0);
	vector<int> minCur(MAX, 0);
	cin >> N;
	while (N--) {
		for (int i = 0; i < MAX; ++i) {
			cin >> gameMap[i];
		}

		maxCur[0] = gameMap[0] + max(maxPrev[0], maxPrev[1]);
		maxCur[1] = gameMap[1] + max(maxPrev[0], max(maxPrev[1], maxPrev[2]));
		maxCur[2] = gameMap[2] + max(maxPrev[1], maxPrev[2]);

		minCur[0] = gameMap[0] + min(minPrev[0], minPrev[1]);
		minCur[1] = gameMap[1] + min(minPrev[0], min(minPrev[1], minPrev[2]));
		minCur[2] = gameMap[2] + min(minPrev[1], minPrev[2]);

		for (int i = 0; i < MAX; ++i) {
			maxPrev[i] = maxCur[i];
			minPrev[i] = minCur[i];
		}
	}

	int maxAnswer = max(maxCur[0], max(maxCur[1], maxCur[2]));
	int minAnswer = min(minCur[0], min(minCur[1], minCur[2]));
	cout << maxAnswer << ' ' << minAnswer;
	return 0;
}
