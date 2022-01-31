#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int dr[4] = {-1, 0, 1, 0};
const int dc[4] = {0, 1, 0, -1};
const int UP = 0;
const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;

int selectDir(int map, int dice, int dir) {
    if(dice > map) {
        return (dir + 1) % 4;
    } else if(dice < map) {
        if(dir == 0) {
            dir = 3;
        } else {
            dir = dir - 1;
        }
        return dir;
    } else {
        return dir;
    }
}
int getScore(int N, int M, vector<vector<int>>& map, int r, int c, vector<vector<int>>& scores) {
    if(scores[r][c] > 0) {
        return scores[r][c];
    }

    int score = 0;
    vector<vector<bool>> isVisited(N + 1, vector<bool>(M + 1, false));
    queue<pair<int, int>> q;
    vector<pair<int, int>> groups;

    q.push({r, c});
    groups.push_back({r, c});
    isVisited[r][c] = true;
    while(!q.empty()) {
        int curR = q.front().first;
        int curC = q.front().second;
        score++;
        q.pop();

        for(int i = 0; i < 4; ++i) {
            int nextR = curR + dr[i];
            int nextC = curC + dc[i];

            if(nextR < 1 || nextR > N || nextC < 1 || nextC > M) {
                continue;
            }
            if(isVisited[nextR][nextC] || map[nextR][nextC] != map[curR][curC]) {
                continue;
            }

            q.push({nextR, nextC});
            groups.push_back({nextR, nextC});
            isVisited[nextR][nextC] = true;
        }
    }

    for(int i = 0; i < groups.size(); ++i) {
        scores[groups[i].first][groups[i].second] = score * map[r][c];
    }

    return scores[r][c];
}
void moveDice(int N, int M, int& curR, int& curC, int& dir, vector<int>& diceC, vector<int>& diceR) {
    int nextR = curR + dr[dir];
    int nextC = curC + dc[dir];

    if(nextR < 1 || nextR > N || nextC < 1 || nextC > M) {
        dir = (dir + 2) % 4;
        nextR = curR + dr[dir];
        nextC = curC + dc[dir];
    }

    curR = nextR;
    curC = nextC;

    if(dir == RIGHT) {
        int tmp = diceC[2];
        for(int i = 2; i >= 1; --i) {
            diceC[i] = diceC[i - 1];
        }
        diceC[0] = diceR[3];

        diceR[3] = tmp;
        diceR[1] = diceC[1];
    } else if(dir == LEFT) {
        int tmp = diceC[0];
        for(int i = 0; i <= 1; ++i) {
            diceC[i] = diceC[i + 1];
        }
        diceC[2] = diceR[3];

        diceR[3] = tmp;
        diceR[1] = diceC[1];
    } else if(dir == UP) {
        int tmp = diceR[0];
        for(int i = 0; i <= 2; ++i) {
            diceR[i] = diceR[i + 1];
        }
        diceR[3] = tmp;

        diceC[1] = diceR[1];
    } else {
        int tmp = diceR[3];
        for(int i = 3; i >= 1; --i) {
            diceR[i] = diceR[i - 1];
        }
        diceR[0] = tmp;

        diceC[1] = diceR[1];
    }
}
int simulation(int N, int M, int K, vector<vector<int>> map) {
    int totalScore = 0;
    int dir = RIGHT;
    int curR = 1;
    int curC = 1;
    vector<int> diceC = {4, 1, 3};
    vector<int> diceR = {2, 1, 5, 6};
    vector<vector<int>> scores(N + 1, vector<int>(M + 1, 0));

    while(K--) {
        moveDice(N, M, curR, curC, dir, diceC, diceR);

        totalScore += getScore(N, M, map, curR, curC, scores);

        dir = selectDir(map[curR][curC], diceR[3], dir);
    }

    return totalScore;
}
void input(int& N, int& M, int& K, vector<vector<int>>& map) {
    cin >> N >> M >> K;
    map.assign(N + 1, vector<int>(M + 1 , 0));
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= M; ++j) {
            cin >> map[i][j];
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, K;
    vector<vector<int>> map;
    input(N, M, K, map);

    int answer = simulation(N, M, K, map);

    cout << answer;
    return 0;
}
