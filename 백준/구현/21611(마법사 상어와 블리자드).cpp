#include <iostream>
#include <vector>
#include <queue>
#include <deque>
using namespace std;
const int dr[5] = {0, -1, 1, 0, 0};
const int dc[5] = {0, 0, 0, -1, 1};
struct magic {
    int d, s;
    magic(int d, int s) {
        this->d = d;
        this->s = s;
    }
};

void showMap(vector<vector<int>>& map) {
    for(int i = 1; i < map.size(); ++i) {
        for(int j = 1; j < map.size(); ++j) {
            cout << map[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << "\n\n";
}
int changeDir(int dir) {
    if(dir == 3) {
        return 2;
    } else if(dir == 2) {
        return 4;
    } else if(dir == 4) {
        return 1;
    } else {
        return 3;
    }
}
void putBallsToMap(int N, vector<vector<int>>& map, deque<int>& balls) {
    int r = (N + 1) / 2;
    int c = (N + 1) / 2;
    int dist = 1;
    int dir = 3;
    while(true) {
        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < dist; ++j) {
                r = r + dr[dir];
                c = c + dc[dir];

                if(!balls.empty()) {
                    map[r][c] = balls.front();
                    balls.pop_front();
                } else {
                    break;
                }
            }
            if(balls.empty()) {
                break;
            }
            dir = changeDir(dir);
        }

        if(balls.empty()) {
            break;
        }
        dist++;
        if(dist == N) {
            for(int i = 0; i < N - 1; ++i) {
                r = r + dr[dir];
                c = c + dc[dir];

                if(!balls.empty()) {
                    map[r][c] = balls.front();
                    balls.pop_front();
                } else {
                    break;
                }
            }
            break;
        }
    }
}
void changeBall(deque<int>& balls) {
    deque<int> tmp(balls);
    balls.clear();

    while(!tmp.empty()) {
        int idx = tmp.front();
        int cnt = 1;
        tmp.pop_front();

        while(true) {
            if(tmp.empty() || tmp.front() != idx) {
                balls.push_back(cnt);
                balls.push_back(idx);
                break;
            }

            tmp.pop_front();
            cnt++;
        }
    }
}
void ExplosionAndMove(deque<int>& balls, int& oneCnt, int& twoCnt, int& threeCnt) {
    while(true) {
        int ballsCnt = balls.size();
        deque<int> tmp(balls);
        balls.clear();

        int cnt = 0;
        while(!tmp.empty()) {

            if(!balls.empty() && balls.back() != tmp.front()) {
                if(cnt >= 4) {
                    if(balls.back() == 1) {
                        oneCnt += cnt;
                    } else if(balls.back() == 2) {
                        twoCnt += cnt;
                    } else {
                        threeCnt += cnt;
                    }

                    while(cnt--) {
                        balls.pop_back();
                    }
                } else {
                    cnt = 0;
                }
            }

            balls.push_back(tmp.front());
            tmp.pop_front();
            cnt++;
        }

        if(cnt >= 4) {
            if(balls.back() == 1) {
                oneCnt += cnt;
            } else if(balls.back() == 2) {
                twoCnt += cnt;
            } else {
                threeCnt += cnt;
            }

            while(cnt--) {
                balls.pop_back();
            }
        }

        if(ballsCnt == balls.size()) {
            break;
        }
    }
}
void saveBalls(int N, vector<vector<int>>& map, deque<int>& balls) {
    int r = (N + 1) / 2;
    int c = (N + 1) / 2;
    int dist = 1;
    int dir = 3;
    while(true) {
        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < dist; ++j) {
                r = r + dr[dir];
                c = c + dc[dir];

                if(map[r][c] > 0) {
                    balls.push_back(map[r][c]);
                    map[r][c] = 0;
                }
            }
            dir = changeDir(dir);
        }

        dist++;
        if(dist == N) {
            for(int i = 0; i < N - 1; ++i) {
                r = r + dr[dir];
                c = c + dc[dir];

                if(map[r][c] > 0) {
                    balls.push_back(map[r][c]);
                    map[r][c] = 0;
                }
            }
            break;
        }
    }
}
void blizzard(int N, vector<vector<int>>& map, int d, int s) {
    int r = (N + 1) / 2;
    int c = (N + 1) / 2;

    while(s--) {
        r += dr[d];
        c += dc[d];

        map[r][c] = 0;
    }
}
int simulation(int N, int M, vector<vector<int>>& map, vector<magic>& magics) {
    int oneCnt = 0;
    int twoCnt = 0;
    int threeCnt = 0;
    deque<int> balls;

    for(int i = 0; i < M; ++i) {
        int d = magics[i].d;
        int s = magics[i].s;

        blizzard(N, map, d, s);

        saveBalls(N, map, balls);

        ExplosionAndMove(balls, oneCnt, twoCnt, threeCnt);

        changeBall(balls);

        putBallsToMap(N, map, balls);

        balls.clear();
    }

    int answer = oneCnt + (2 * twoCnt) + (3 * threeCnt);
    return answer;
}
void input(int& N, int& M, vector<vector<int>>& map, vector<magic>& magics) {
    cin >> N >> M;
    map.assign(N + 1, vector<int>(N + 1, 0));
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            cin >> map[i][j];
        }
    }
    magics.assign(M, {0, 0});
    for(int i = 0; i < M; ++i) {
        cin >> magics[i].d >> magics[i].s;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    vector<vector<int>> map;
    vector<magic> magics;
    input(N, M, map, magics);

    int answer = simulation(N, M, map, magics);

    cout << answer;
    return 0;
}
