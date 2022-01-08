#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;
const int dr[4] = { 0, 0, -1, 1 };
const int dc[4] = { -1, 1, 0, 0 };


int bfs(int R, int C, vector<string>& map) {
	queue<pair<int, int>> mouse;
	queue<pair<int, int>> water;
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			if (map[i][j] == 'S') {
				mouse.push(make_pair(i, j));
			}
			else if (map[i][j] == '*') {
				water.push(make_pair(i, j));
			}
		}
	}
	
	int curTime = 0;
	bool arrive = false;
	while (true) {
		curTime++;

		int waterSize = water.size();
		for (int i = 0; i < waterSize; ++i) {
			int r = water.front().first;
			int c = water.front().second;
			water.pop();

			for (int j = 0; j < 4; ++j) {
				int nextR = r + dr[j];
				int nextC = c + dc[j];

				if (nextR < 0 || nextR >= R || nextC < 0 || nextC >= C) {
					continue;
				}
				if (map[nextR][nextC] == 'X' || map[nextR][nextC] == 'D' || map[nextR][nextC] == '*') {
					continue;
				}

				map[nextR][nextC] = '*';
				water.push(make_pair(nextR, nextC));
			}
		}

		int mouseSize = mouse.size();
		for (int i = 0; i < mouseSize; ++i) {
			int r = mouse.front().first;
			int c = mouse.front().second;
			mouse.pop();

			for (int j = 0; j < 4; ++j) {
				int nextR = r + dr[j];
				int nextC = c + dc[j];

				if (nextR < 0 || nextR >= R || nextC < 0 || nextC >= C) {
					continue;
				}
				if (map[nextR][nextC] == 'X' || map[nextR][nextC] == '*' || map[nextR][nextC] == 'S') {
					continue;
				}
			
				if (map[nextR][nextC] == 'D') {
					arrive = true;
					break;
				}

				map[nextR][nextC] = 'S';
				mouse.push(make_pair(nextR, nextC));
			}
		}

		if (arrive) {
			break;
		}

		if (mouse.empty()) {
			break;
		}
	}

	if (!arrive) {
		return -1;
	}
	return curTime;
}
void input(int& R, int& C, vector<string>& map) {
	cin >> R >> C;
	map.assign(R, "");
	for (int i = 0; i < R; ++i) {
		cin >> map[i];
	}
}
int main() {
	int R, C;
	vector<string> map;
	input(R, C, map);

	int answer = bfs(R, C, map);

	if (answer == -1) {
		cout << "KAKTUS";
	}
	else {
		cout << answer;
	}
	return 0;
}
