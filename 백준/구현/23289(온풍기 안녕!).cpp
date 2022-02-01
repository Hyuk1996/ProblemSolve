#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

const int moveX[5][3] = {{0, 0, 0},
                         {0, -1, 1},
                         {0, -1, 1},
                         {-1, -1, -1},
                         {1, 1, 1}};
const int moveY[5][3] = {{0, 0, 0},
                         {1, 1, 1},
                         {-1, -1, -1},
                         {0, -1, 1},
                         {0, -1, 1}};
const int wallDir[5][3][2] = {{{0, 0}, {0, 0}, {0, 0}},
                              {{1, 0}, {0, 3}, {2, 3}},
                              {{3, 0}, {0, 1}, {2, 1}},
                              {{0, 0}, {3, 2}, {1, 2}},
                              {{2, 0}, {3, 0}, {1, 0}}};
struct heater {
    int x, y, d;
    heater(int x, int y, int d) {
        this->x = x;
        this->y = y;
        this->d = d;
    }
};


bool doInspection(vector<vector<int>>& room, vector<pair<int, int>>& inspection, int K) {
    for(int i = 0; i < inspection.size(); ++i) {
        if(room[inspection[i].first][inspection[i].second] < K) {
            return false;
        }
    }
    return true;
}
void reduceEdge(int R, int C, vector<vector<int>>& room) {
    for(int i = 1; i <= R; ++i) {
        if(room[i][1] > 0) {
            room[i][1]--;
        }
        if(room[i][C] > 0) {
            room[i][C]--;
        }
    }

    for(int i = 2; i <= C - 1; ++i) {
        if(room[1][i] > 0) {
            room[1][i]--;
        }
        if(room[R][i] > 0) {
            room[R][i]--;
        }
    }
}
void updateChangeTemp(int R, int C, int x, int y, vector<vector<int>>& room, vector<vector<int>>& changeTemp, vector<vector<vector<bool>>>& isWall) {
    for(int i = 0; i < 4; ++i) {
        int nextX = x + dx[i];
        int nextY = y + dy[i];

        if(nextX < 1 || nextX > R || nextY < 1 || nextY > C) {
            continue;
        }
        if(isWall[x][y][i] || room[x][y] <= room[nextX][nextY]) {
            continue;
        }

        int diff = room[x][y] - room[nextX][nextY];
        diff /= 4;
        changeTemp[x][y] -= diff;
        changeTemp[nextX][nextY] += diff;
    }
}
void controlTemp(int R, int C, vector<vector<int>>& room, vector<vector<vector<bool>>>& isWall) {
    vector<vector<int>> changeTemp(R + 1, vector<int>(C + 1, 0));
    for(int i = 1; i <= R; ++i) {
        for(int j = 1; j <= C; ++j) {
            updateChangeTemp(R, C, i, j, room, changeTemp, isWall);
        }
    }

    for(int i = 1; i <= R; ++i) {
        for(int j = 1; j <= C; ++j) {
            room[i][j] += changeTemp[i][j];
        }
    }
}
void operateHeater(int R, int C, int x, int y, int d, vector<vector<int>>& room, vector<vector<vector<bool>>>& isWall) {
    x += moveX[d][0];
    y += moveY[d][0];

    vector<vector<bool>> isVisited(R + 1, vector<bool>(C + 1, false));
    queue<pair<int, int>> q;
    int k = 5;

    isVisited[x][y] = true;
    q.push({x, y});
    room[x][y] += k;

    while(!q.empty() && k > 0) {
        int qSize = q.size();
        k--;

        for(int i = 0; i < qSize; ++i) {

            int curX = q.front().first;
            int curY = q.front().second;
            q.pop();

            for(int j = 0; j < 3; ++j) {
                int nextX = curX + moveX[d][j];
                int nextY = curY + moveY[d][j];

                if(nextX < 1 || nextX > R || nextY < 1 || nextY > C) {
                    continue;
                }
                if(isVisited[nextX][nextY]) {
                    continue;
                }


                if(j == 0) {
                    if(isWall[curX][curY][wallDir[d][j][0]]) {
                        continue;
                    }
                } else {
                    if(isWall[curX][curY][wallDir[d][j][0]] || isWall[nextX][nextY][wallDir[d][j][1]]) {
                        continue;
                    }
                }

                isVisited[nextX][nextY] = true;
                q.push({nextX, nextY});
                room[nextX][nextY] += k;
            }
        }
    }
}
void operateHeaters(int R, int C, vector<vector<int>>& room, vector<heater>& heaters, vector<vector<vector<bool>>>& isWall) {
    for(int i = 0; i < heaters.size(); ++i) {
        int curX = heaters[i].x;
        int curY = heaters[i].y;
        int curD = heaters[i].d;

        operateHeater(R, C, curX, curY, curD, room, isWall);
    }
}
void getInfo(int R, int C, vector<vector<int>>& room, vector<heater>& heaters, vector<pair<int, int>>& inspection) {
    for(int i = 1; i <= R; ++i) {
        for(int j = 1; j <= C; ++j) {
            if(room[i][j] > 0 && room[i][j] < 5) {
                heaters.push_back(heater(i, j, room[i][j]));
                room[i][j] = 0;
            } else if(room[i][j] == 5) {
                inspection.push_back({i, j});
                room[i][j] = 0;
            }
        }
    }
}
int solve(int R, int C, int K, vector<vector<int>>& room, vector<vector<vector<bool>>>& isWall) {
    vector<heater> heaters;
    vector<pair<int, int>> inspection;
    getInfo(R, C, room, heaters, inspection);

    bool isFinished;
    int cnt = 0;
    while(true) {

        operateHeaters(R, C, room, heaters, isWall);

        controlTemp(R, C, room, isWall);

        reduceEdge(R, C, room);

        cnt++;

        isFinished = doInspection(room, inspection, K);

        if(isFinished || cnt == 100) {
            break;
        }
    }

    if(isFinished) {
        return cnt;
    } else {
        return 101;
    }
}
void input(int& R, int& C, int& K, vector<vector<int>>& room, int& W, vector<vector<vector<bool>>>& isWall) {
    cin >> R >> C >> K;
    room.assign(R + 1, vector<int>(C + 1, 0));
    for(int i = 1; i <= R; ++i) {
        for(int j = 1; j <= C; ++j) {
            cin >> room[i][j];
        }
    }
    cin >> W;
    isWall.assign(R + 1, vector<vector<bool>>(C + 1, vector<bool>(4, false)));
    int x, y, t;
    for(int i = 0; i < W; ++i) {
        cin >> x >> y >> t;
        if(t == 0) {
            isWall[x][y][0] = true;
            isWall[x - 1][y][2] = true;
        } else {
            isWall[x][y][1] = true;
            isWall[x][y + 1][3] = true;
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int R, C, K, W;
    vector<vector<int>> room;
    vector<vector<vector<bool>>> isWall;
    input(R, C, K, room, W, isWall);

    int answer = solve(R, C, K, room, isWall);

    cout << answer;
    return 0;
}
