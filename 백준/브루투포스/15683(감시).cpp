#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {-1, 1, 0, 0};
const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int WALL = 6;
const int CHECK = 7;
struct cctv {
    int x;
    int y;
    int type;
    int maxRotation;
    int dir;

    cctv(int x, int y, int type, int maxRotation, int dir) {
        this->x = x;
        this->y = y;
        this->type = type;
        this->maxRotation = maxRotation;
        this->dir = dir;
    }
};

void makeOffice(vector<vector<int>>& office, int N, int  M);
void showOffice(const vector<vector<int>>& office);
void getCctv(const vector<vector<int>>& office, vector<cctv>& cctvs);
void getCctvCombination(vector<cctv>& cctv, int idx, vector<vector<int>>& office, int& blindSpot);
void startCctv(vector<vector<int>>& office, vector<cctv>& cctvs, int& blindSpot);
void dfs(vector<vector<int>>& office, int x, int y, int dir);
int getBlindSpot(vector<vector<int>>& office);
int main() {
    // 입력
    int N, M;
    cin >> N >> M;
    vector<vector<int>> office(N, vector<int>(M));
    makeOffice(office, N, M);

    vector<cctv> cctvs;
    getCctv(office, cctvs);

    int blindSpot = 100;
    getCctvCombination(cctvs, 0, office, blindSpot);
    cout << blindSpot;
    return 0;
}
void showOffice(const vector<vector<int>>& office) {
    for(int i=0; i<office.size(); ++i) {
        for(int j=0; j<office[i].size(); ++j) {
            cout << office[i][j] << ' ';
        }
        cout << '\n';
    }
}

void makeOffice(vector<vector<int>>& office, int N, int M) {
    for(int i=0; i<N; ++i) {
        for(int j=0; j<M; ++j) {
            int info;
            cin >> info;
            office[i][j] = info;
        }
    }
}
void getCctv(const vector<vector<int>>& office, vector<cctv>& cctvs) {
    for(int i=0; i<office.size(); ++i) {
        for(int j=0; j<office[i].size(); ++j) {
            if(0 < office[i][j] && office[i][j] < 6) {
                int maxRotation;
                if(office[i][j] == 1) {
                    maxRotation = 4;
                } else if(office[i][j] == 2) {
                    maxRotation = 2;
                } else if(office[i][j] == 3) {
                    maxRotation = 4;
                } else if(office[i][j] == 4) {
                    maxRotation = 4;
                } else {
                    maxRotation = 1;
                }
                cctvs.push_back(cctv(j, i, office[i][j], maxRotation, 0));
            }
        }
    }
}
void getCctvCombination(vector<cctv>& cctvs, int idx, vector<vector<int>>& office, int& blindSpot) {
    if(idx == cctvs.size()) {
        startCctv(office, cctvs, blindSpot);
        return;
    }

    for(int i=0; i<cctvs[idx].maxRotation; ++i) {
        cctvs[idx].dir = i;
        getCctvCombination(cctvs, idx + 1, office, blindSpot);
    }
}
void startCctv(vector<vector<int>>& office, vector<cctv>& cctvs, int& blindSpot) {
    vector<vector<int>> officeCopy(office.size(), vector<int>(office[0].size()));
    copy(office.begin(), office.end(), officeCopy.begin());

    for(int i=0; i<cctvs.size(); ++i) {
        int startX = cctvs[i].x;
        int startY = cctvs[i].y;
        int type = cctvs[i].type;
        int dir = cctvs[i].dir;

        if(type == 1) {
            dfs(officeCopy, startX, startY, dir);
        } else if(type == 2) {
            if(dir == 0) {
                for(int i=2; i<4; ++i) {
                    dfs(officeCopy, startX, startY, i);
                }
            } else {
                for(int i=0; i<2; ++i) {
                    dfs(officeCopy, startX, startY, i);
                }
            }
        } else if(type == 3) {
            if(dir == 0) {
                dfs(officeCopy, startX, startY, RIGHT);
                dfs(officeCopy, startX, startY, UP);
            } else if (dir == 1) {
                dfs(officeCopy, startX, startY, UP);
                dfs(officeCopy, startX, startY, LEFT);
            } else if (dir == 2) {
                dfs(officeCopy, startX, startY, LEFT);
                dfs(officeCopy, startX, startY, DOWN);
            } else {
                dfs(officeCopy, startX, startY, DOWN);
                dfs(officeCopy, startX, startY, RIGHT);
            }
        } else if(type == 4) {
            for(int i=0; i<4; ++i) {
                if(i == dir) {
                    continue;
                }
                dfs(officeCopy, startX, startY, i);
            }
        } else {
            for(int j=0; j<4; ++j) {
                dfs(officeCopy, startX, startY, j);
            }
        }
    }

    blindSpot = min(blindSpot, getBlindSpot(officeCopy));
}
void dfs(vector<vector<int>>& office, int x, int y, int dir) {
    office[y][x] = CHECK;

    int nextX = x + dx[dir];
    int nextY = y + dy[dir];
    if((0 <= nextX && nextX < office[y].size()) && (0 <= nextY && nextY < office.size())) {
        if(office[nextY][nextX] != WALL)
            dfs(office, nextX, nextY, dir);
    }
}
int getBlindSpot(vector<vector<int>>& office) {
    int blindSpot = 0;
    for(int i=0; i<office.size(); ++i) {
        for(int j=0; j<office[i].size(); ++j){
            if(office[i][j] == 0) {
                ++blindSpot;
            }
        }
    }
    return blindSpot;
}
