#include <iostream>
#include <vector>
using namespace std;

void walk(vector<vector<bool>>& map, int& r, int& c) {
	while (r < map.size() && c < map[0].size()) {
		if (map[r][c]) {
			c++;
		}
		else {
			r++;
		}
	}
}
void updateMap(vector<vector<bool>>& map, vector<vector<int>>& changeCnt) {
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 0; j < map[i].size(); ++j) {
			if (changeCnt[i][j] % 2 == 1) {
				map[i][j] = !map[i][j];
			}
		}
	}
}
void calChangeCnt(vector<vector<bool>>& map, vector<vector<int>>& changeCnt, int H, int W, int N) {
	changeCnt[0][0] = N - 1;
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			if ((j + 1) != W) {
				if (map[i][j]) {
					changeCnt[i][j + 1] += changeCnt[i][j] / 2;
					if (changeCnt[i][j] % 2 == 1) {
						changeCnt[i][j + 1]++;
					}
				}
				else {
					changeCnt[i][j + 1] += changeCnt[i][j] / 2;
				}
			}

			if ((i + 1) != H) {
				if (!map[i][j]) {
					changeCnt[i + 1][j] += changeCnt[i][j] / 2;
					if (changeCnt[i][j] % 2 == 1) {
						changeCnt[i + 1][j]++;
					}
				}
				else {
					changeCnt[i + 1][j] += changeCnt[i][j] / 2;
				}
			}
		}
	}
}
void input(int& H, int& W, int& N, vector<vector<bool>>& map) {
	cin >> H >> W >> N;
	map.assign(H, vector<bool>(W, 0));
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < W; ++j) {
			int dir;
			cin >> dir;
			map[i][j] = dir;
		}
	}
}
int main() {
	int H, W, N;
	vector<vector<bool>> map;
	input(H, W, N, map);


	vector<vector<int>> changeCnt(H, vector<int>(W, 0));
	calChangeCnt(map, changeCnt, H, W, N);
	updateMap(map, changeCnt); //N-1 산책 후의 map 상태로 update

	int r = 0;
	int c = 0;
	walk(map, r, c); //N번째 산책
	
	cout << r + 1 << ' ' << c + 1;
	return 0;
}
