#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;
const int dr[8] = { -1, -1, -1, 0, 0, 1, 1, 1};
const int dc[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
const int MAX = 1000000;

bool bfs(vector<string>& town, vector<vector<int>>& townHeight, int maxH, int minH, int startR, int startC, int houseCount) {
	if (townHeight[startR][startC] < minH || townHeight[startR][startC] > maxH) {
		return false;
	}

	vector<vector<bool>> visit(town.size(), vector<bool>(town.size(), false));
	queue<pair<int, int>> q;

	q.push(make_pair(startR, startC));
	visit[startR][startC] = true;
	while (!q.empty()) {
		int r = q.front().first;
		int c = q.front().second;
		q.pop();

		for (int i = 0; i < 8; ++i) {
			int nextR = r + dr[i];
			int nextC = c + dc[i];

			if (nextR < 0 || nextR >= town.size() || nextC < 0 || nextC >= town.size()) {
				continue;
			}
			if (visit[nextR][nextC]) {
				continue;
			}
			if (townHeight[nextR][nextC] < minH || townHeight[nextR][nextC] > maxH) {
				continue;
			}

			visit[nextR][nextC] = true;
			q.push(make_pair(nextR, nextC));
			if (town[nextR][nextC] == 'K') {
				--houseCount;
			}
		}
	}

	if (houseCount == 0) {
		return true;
	}
	else {
		return false;
	}
}
bool canGo(vector<string>& town, vector<vector<int>>& townHeight, int maxH, int minH, int& answer, int startR, int startC, int houseCount) {
	bool possible = bfs(town, townHeight, maxH, minH, startR, startC, houseCount);

	if (possible) {
		answer = min(answer, maxH - minH);
		return true;
	}
	else {
		return false;
	}
}
int solve(int N, vector<string>& town, vector<vector<int>>& townHeight) {
	// 필요한 정보 구하기
	int startR, startC;
	int houseCount = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (town[i][j] == 'P') {
				startR = i;
				startC = j;
			}
			else if (town[i][j] == 'K') {
				houseCount++;
			}
		}
	}


	// 중복제거 & 오름차순 정렬
	map<int, int> heights;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			heights[townHeight[i][j]] = 1;
		}
	}

	vector<int> heightList;
	for (auto it = heights.begin(); it != heights.end(); it++) {
		heightList.push_back(it->first);
	}

	// 투 포인터 이용해 가능한 피로도에 대해서 배달 가능여부 확인
	int minIdx = 0;
	int maxIdx = 0;
	int answer = MAX;
	while (maxIdx < heightList.size()) {
		while (minIdx <= maxIdx) {
			if (!canGo(town, townHeight, heightList[maxIdx], heightList[minIdx], answer, startR, startC, houseCount)) {
				break;
			}
			minIdx++;
		}
		maxIdx++;
	}

	return answer;
}
void input(int& N, vector<string>& town, vector<vector<int>>& townHeight) {
	cin >> N;
	town.assign(N, "");
	townHeight.assign(N, vector<int>(N, 0));
	for (int i = 0; i < N; ++i) {
		cin >> town[i];
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> townHeight[i][j];
		}
	}
}
int main() {
	int N;
	vector<string> town;
	vector<vector<int>> townHeight;
	input(N, town, townHeight);

	int answer = solve(N, town, townHeight);
	cout << answer;
	return 0;
}
