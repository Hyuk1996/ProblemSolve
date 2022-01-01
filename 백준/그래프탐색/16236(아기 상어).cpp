#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int dr[4] = {0, 0, -1, 1};
const int dc[4] = {-1, 1, 0, 0};
struct shark {
    int r;
    int c;
    int size;
    int curEatFish;
    shark(int r, int c, int size, int curEatFish) {
        this->r = r;
        this->c = c;
        this->size = size;
        this->curEatFish = curEatFish;
    }
};


bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    if(a.first == b.first) {
        return a.second < b.second;
    }
    return a.first < b.first;
}
void moveBabyShark(vector<vector<int>>& map, shark& babyShark, int fishR, int fishC) {
    babyShark.r = fishR;
    babyShark.c = fishC;
    ++babyShark.curEatFish;
    map[fishR][fishC] = 0;
    if(babyShark.curEatFish == babyShark.size) {
        babyShark.curEatFish = 0;
        ++babyShark.size;
    }
}
bool searchFish(vector<vector<int>>& map, shark& babyShark, int& fishR, int& fishC, int& dist) {
    vector<vector<bool>> visit(map.size(), vector<bool>(map.size(), false));
    queue<pair<int, int>> q;
    vector<pair<int, int>> eatableFish;

    int curDist = 0;
    q.push(make_pair(babyShark.r, babyShark.c));
    visit[babyShark.r][babyShark.c] = true;
    while(!q.empty()) {
        int qSize = q.size();
        ++curDist;

        for(int i=0; i<qSize; ++i) {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();

            for(int j=0; j<4; ++j) {
                int nextR = r + dr[j];
                int nextC = c + dc[j];

                if(nextR < 0 || nextR >= map.size() || nextC < 0 || nextC >= map.size()) {
                    continue;
                }

                if(visit[nextR][nextC] || map[nextR][nextC] > babyShark.size) {
                    continue;
                }

                if(map[nextR][nextC] == 0 || map[nextR][nextC] == babyShark.size) {
                    q.push(make_pair(nextR, nextC));
                    visit[nextR][nextC] = true;
                } else {
                    eatableFish.push_back(make_pair(nextR, nextC));
                    visit[nextR][nextC] =true;
                }
            }
        }
        if(!eatableFish.empty()) {
            break;
        }
    }

    if(eatableFish.empty()) {
        dist = -1;
        return false;
    } else {
        sort(eatableFish.begin(), eatableFish.end(), cmp);
        fishR = eatableFish[0].first;
        fishC = eatableFish[0].second;
        dist = curDist;
        return true;
    }
}
void getSharkInfo(vector<vector<int>>& map, shark& shark) {
    for(int i=0; i<map.size(); ++i) {
        for(int j=0; j<map.size(); ++j) {
            if(map[i][j] == 9) {
                shark.r = i;
                shark.c = j;
                map[i][j] = 0;
                return;
            }
        }
    }
}
int solve(const int N, vector<vector<int>>& map) {
    shark babyShark(0, 0, 2, 0);
    getSharkInfo(map, babyShark);

    int curTime = 0;
    int fishR = -1;
    int fishC = -1;
    while(true) {
        int dist;
        if(!searchFish(map, babyShark, fishR, fishC, dist)) {
            break;
        }

        moveBabyShark(map, babyShark, fishR, fishC);
        curTime += dist;
    }

    return curTime;
}
void input(int& N, vector<vector<int>>& map) {
    cin >> N;
    map.assign(N, vector<int>(N, 0));
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            cin >> map[i][j];
        }
    }
}
int main() {
    int N;
    vector<vector<int>> map;
    input(N, map);

    int answer = solve(N, map);
    cout << answer;
    return 0;
}
