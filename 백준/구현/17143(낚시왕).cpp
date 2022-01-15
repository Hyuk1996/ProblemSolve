#include <iostream>
#include <vector>
using namespace std;
const int EMPTY = -1;
struct shark {
    int r;
    int c;
    int s;
    int d;
    int z;
    shark(int r, int c, int s, int d, int z) {
        this->r = r;
        this->c = c;
        this->s = s;
        this->d = d;
        this->z = z;
    }
};

int solve(int R, int C, int M, vector<shark>& sharks, vector<vector<int>>& map) {
    vector<bool> isDied(M, false);
    int answer = 0;

    int curC = 1;
    int sharkIdx;
    while(curC <= C) {
        //상어잡기
        for(int i=1; i<=R; ++i) {
            if(map[i][curC] != -1) {
                sharkIdx = map[i][curC];
                map[i][curC] = -1;
                isDied[sharkIdx] = true;
                answer += sharks[sharkIdx].z;
                break;
            }
        }

        //상어이동
        for(int i=0; i<M; ++i) {
            map[sharks[i].r][sharks[i].c] = EMPTY;
        }

        for(int i=0; i<M; ++i) {
            if(isDied[i]) {
                continue;
            }

            int sharkR = sharks[i].r;
            int sharkC = sharks[i].c;
            int dir = sharks[i].d;
            int speed = sharks[i].s;
            if(dir == 1 || dir == 2) {
                speed = speed % ((R - 1) * 2);
                while(speed > 0) {
                    if(dir == 1) {
                        if(sharkR - 1 <= speed) {
                            speed -= (sharkR - 1);
                            sharkR = 1;
                            dir = 2;
                        }
                        else {
                            sharkR = sharkR - speed;
                            speed = 0;
                        }
                    }
                    if(dir == 2) {
                        if(R - sharkR <= speed) {
                            speed -= (R - sharkR);
                            sharkR = R;
                            dir = 1;
                        }
                        else {
                            sharkR = sharkR + speed;
                            speed = 0;
                        }
                    }
                }
            }
            else {
                speed = speed % ((C - 1) * 2);
                while(speed > 0) {
                    if(dir == 3) {
                        if(C - sharkC <= speed) {
                            speed -= (C - sharkC);
                            sharkC = C;
                            dir = 4;
                        }
                        else {
                            sharkC = sharkC + speed;
                            speed = 0;
                        }
                    }
                    else {
                        if(sharkC - 1 <= speed) {
                            speed -= (sharkC - 1);
                            sharkC = 1;
                            dir = 3;
                        }
                        else {
                            sharkC = sharkC - speed;
                            speed = 0;
                        }
                    }
                }
            }

            if(map[sharkR][sharkC] == EMPTY) {
                map[sharkR][sharkC] = i;
                sharks[i].r = sharkR;
                sharks[i].c = sharkC;
                sharks[i].d = dir;
            } else {
                int preIdx = map[sharkR][sharkC];
                if(sharks[preIdx].z > sharks[i].z) {
                    isDied[i] = true;
                }
                else {
                    isDied[preIdx] = true;
                    map[sharkR][sharkC] = i;
                    sharks[i].r = sharkR;
                    sharks[i].c = sharkC;
                    sharks[i].d = dir;
                }
            }
        }
        curC++;
    }
    return answer;
}
void input(int& R, int& C, int& M, vector<shark>& sharks, vector<vector<int>>& map) {
    cin >> R >> C >> M;
    map.assign(R+1, vector<int>(C+1, EMPTY));
    int r, c, s, d, z;
    for(int i=0; i<M; ++i) {
        cin >> r >> c >> s >> d >> z;
        sharks.push_back(shark(r, c, s, d, z));
        map[r][c] = i;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int R, C, M;
    vector<shark> sharks;
    vector<vector<int>> map;
    input(R, C, M, sharks, map);

    int answer = solve(R, C, M, sharks, map);

    cout << answer;
    return 0;
}
