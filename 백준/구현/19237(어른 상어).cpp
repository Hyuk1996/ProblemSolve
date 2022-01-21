#include <iostream>
#include <vector>
using namespace std;
const int dr[5] = {0, -1, 1, 0 ,0};
const int dc[5] = {0, 0, 0, -1, 1};
struct shark {
    int r, c, d;
    shark(int r, int c, int d) {
        this->r = r;
        this->c = c;
        this->d = d;
    }
};
struct smell {
    int host;
    int k;
    smell(int host, int k) {
        this->host = host;
        this->k = k;
    }
};

void spreadSmells(vector<vector<smell>>& smells, vector<shark>& sharks, vector<bool>& isDied, int k) {
    for(int i=1; i<sharks.size(); ++i) {
        if(isDied[i]) {
            continue;
        }
        smells[sharks[i].r][sharks[i].c].host = i;
        smells[sharks[i].r][sharks[i].c].k = k;
    }
}
void removeSmells(vector<vector<smell>>& smells) {
    for(int i=0; i<smells.size(); ++i) {
        for(int j=0; j<smells.size(); ++j) {
            if(smells[i][j].host == 0) {
                continue;
            }
            smells[i][j].k--;
            if(smells[i][j].k == 0) {
                smells[i][j].host = 0;
                smells[i][j].k = 0;
            }
        }
    }
}
void initMap(vector<vector<int>>& map) {
    for(int i=0; i<map.size(); ++i) {
        for(int j=0; j<map[i].size(); ++j) {
            map[i][j] = 0;
        }
    }
}
int simulation(int N, int M, int k, vector<vector<int>>& map, vector<shark>& sharks, vector<vector<vector<int>>>& moveInfo) {
    vector<vector<smell>> smells(N, vector<smell>(N, {0, 0}));
    vector<bool> isDied(M+1, false);
    int sharkCnt = M;

    spreadSmells(smells, sharks, isDied, k);

    int curTime = 1;
    while(curTime <= 1000) {

        initMap(map);

        //상어 움직이기
        for(int i=1; i<=M; ++i) {
            if(isDied[i]) {
                continue;
            }

            int r = sharks[i].r;
            int c = sharks[i].c;
            int d = sharks[i].d;

            bool isMoved = false;
            for(int j=0; j<4; ++j) {
                int nextR = r + dr[moveInfo[i][d][j]];
                int nextC = c + dc[moveInfo[i][d][j]];
                int nextD = moveInfo[i][d][j];

                if(nextR < 0 || nextR >= N || nextC < 0 || nextC >= N) {
                    continue;
                }
                if(smells[nextR][nextC].host != 0) {
                    continue;
                }


                isMoved = true;
                if(map[nextR][nextC] == 0) {
                    map[nextR][nextC] = i;
                    sharks[i].r = nextR;
                    sharks[i].c = nextC;
                    sharks[i].d = nextD;
                } else {
                    if(map[nextR][nextC] < i) {
                        isDied[i] = true;
                        sharkCnt--;
                    } else {
                        isDied[map[nextR][nextC]] = true;
                        sharkCnt--;
                        sharks[i].r = nextR;
                        sharks[i].c = nextC;
                        sharks[i].d = nextD;
                    }
                }
                break;
            }

            if(isMoved) {
                continue;
            }

            for(int j=0; j<4; ++j) {
                int nextR = r + dr[moveInfo[i][d][j]];
                int nextC = c + dc[moveInfo[i][d][j]];
                int nextD = moveInfo[i][d][j];

                if(nextR < 0 || nextR >= N || nextC < 0 || nextC >= N) {
                    continue;
                }
                if(smells[nextR][nextC].host != i) {
                    continue;
                }

                if(map[nextR][nextC] == 0) {
                    map[nextR][nextC] = i;
                    sharks[i].r = nextR;
                    sharks[i].c = nextC;
                    sharks[i].d = nextD;
                } else {
                    if(map[nextR][nextC] < i) {
                        isDied[i] = true;
                        sharkCnt--;
                    } else {
                        isDied[map[nextR][nextC]] = true;
                        sharkCnt--;
                        sharks[i].r = nextR;
                        sharks[i].c = nextC;
                        sharks[i].d = nextD;
                    }
                }
                break;
            }
        }

        //상어가 1번 상어만 남는는 경우 시물레이션 종료
        if(sharkCnt == 1) {
            break;
        }

        removeSmells(smells);

        spreadSmells(smells, sharks, isDied, k);

        curTime++;
    }

    if(curTime > 1000) {
        return -1;
    } else {
        return curTime;
    }
}
void input(int& N, int& M, int& k, vector<vector<int>>& map, vector<shark>& sharks, vector<vector<vector<int>>>& moveInfo) {
    cin >> N >> M >> k;
    map.assign(N, vector<int>(N, 0));
    sharks.assign(M+1, {0, 0, 0});
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            cin >> map[i][j];
            if(map[i][j] != 0) {
                sharks[map[i][j]].r = i;
                sharks[map[i][j]].c = j;
            }
        }
    }
    for(int i=1; i<=M; ++i) {
        cin >> sharks[i].d;
    }

    moveInfo.assign(M+1, vector<vector<int>>(5, vector<int>(4, 0)));
    for(int i=1; i<=M; ++i) {
        for(int j=1; j<=4; ++j) {
            for(int k=0; k<4; ++k) {
                cin >> moveInfo[i][j][k];
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, k;
    vector<vector<int>> map;
    vector<shark> sharks;
    vector<vector<vector<int>>> moveInfo;
    input(N, M, k, map, sharks, moveInfo);

    int answer = simulation(N, M, k, map, sharks, moveInfo);

    cout << answer;
    return 0;
}
