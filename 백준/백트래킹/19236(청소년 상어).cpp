#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int EMPTY = 0;
const int SHARK = 17;
const int dr[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
const int dc[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
struct fish {
    int r, c, d;
    fish(int r, int c, int d) {
        this->r = r;
        this->c = c;
        this->d = d;
    }
};

int changeDir(int d) {
    if(d == 8) {
        return 1;
    } else {
        return d + 1;
    }
}
int findFish(vector<vector<int>>& map, fish& babyShark, int dist) {

    int nextR = babyShark.r + (dr[babyShark.d] * dist);
    int nextC = babyShark.c + (dc[babyShark.d] * dist);

    if((nextR < 0 || nextR >= 4 || nextC < 0 || nextC >= 4) || map[nextR][nextC] == EMPTY) {
        return 0;
    }
    return map[nextR][nextC];
}
void moveFishes(vector<vector<int>>& map, vector<fish>& fishes, vector<bool>& isDied) {
    for(int i=1; i<=16; ++i) {
        if(isDied[i]) {
            continue;
        }

        int r = fishes[i].r;
        int c = fishes[i].c;
        int d = fishes[i].d;

        for(int j=1; j<=8; ++j) {
            int nextR = r + dr[d];
            int nextC = c + dc[d];

            if((nextR < 0 || nextR >= 4 || nextC < 0 || nextC >= 4) || map[nextR][nextC] == SHARK) {
                d = changeDir(d);
                continue;
            }

            fishes[i].r = nextR;
            fishes[i].c = nextC;
            fishes[i].d = d;
            if(map[nextR][nextC] != EMPTY) {
                fishes[map[nextR][nextC]].r = r;
                fishes[map[nextR][nextC]].c = c;
            }
            swap(map[r][c], map[nextR][nextC]);
            break;
        }
    }
}
void startEat(vector<vector<int>> map, vector<fish> fishes, fish& babyShark, vector<bool>& isDied, int sum, int& maxSum) {
    moveFishes(map, fishes, isDied);

    for(int i=1; i<=3; ++i) {
        int fishIdx = findFish(map, babyShark, i);

        if(fishIdx > 0) {
            int r = babyShark.r;
            int c = babyShark.c;
            int d = babyShark.d;

            babyShark.r = fishes[fishIdx].r;
            babyShark.c = fishes[fishIdx].c;
            babyShark.d = fishes[fishIdx].d;

            map[r][c] = EMPTY;
            map[fishes[fishIdx].r][fishes[fishIdx].c] = SHARK;
            isDied[fishIdx] = true;

            startEat(map, fishes, babyShark, isDied, sum + fishIdx, maxSum);

            babyShark.r = r;
            babyShark.c = c;
            babyShark.d = d;

            map[r][c] = SHARK;
            map[fishes[fishIdx].r][fishes[fishIdx].c] = fishIdx;
            isDied[fishIdx] = false;
        } else {
            if(i == 3) {
                maxSum = max(maxSum, sum);
                return;
            }
        }
    }
}
int solve(vector<vector<int>>& map, vector<fish>& fishes) {
    int maxSum = 0;
    vector<bool> isDied(17, false);

    //(0, 0) 물고기 먹기
    fish babyShark(0, 0, fishes[map[0][0]].d);
    maxSum += map[0][0];
    isDied[map[0][0]] = true;
    map[0][0] = SHARK;

    startEat(map, fishes, babyShark, isDied, maxSum, maxSum);

    return maxSum;
}
void input(vector<vector<int>>& map, vector<fish>& fishes) {
    int a, b;
    map.assign(4, vector<int>(4, 0));
    for(int i=0; i<4; ++i) {
        for(int j=0; j<4; ++j) {
            cin >> a >> b;
            map[i][j] = a;
            fishes[a].r = i;
            fishes[a].c = j;
            fishes[a].d = b;
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<vector<int>> map;
    vector<fish> fishes(17, {0, 0, 0});
    input(map, fishes);

    int answer = solve(map, fishes);

    cout << answer;
    return 0;
}
