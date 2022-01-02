#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int dr[4] = {0, 0, -1, 1};
const int dc[4] = {-1, 1, 0, 0};
struct dust {
    int r;
    int c;
    int dustSize;
    dust(int r, int c, int dustSize) {
        this->r = r;
        this->c = c;
        this->dustSize = dustSize;
    }
};

int getTotalDust(vector<vector<int>>& home, const int R, const int C) {
    int totalDust = 0;
    for(int i=0; i<R; ++i) {
        for(int j=0; j<C; ++j) {
            if(home[i][j] > 0) {
                totalDust += home[i][j];
            }
        }
    }
    return totalDust;
}
void airCleanerOn(vector<vector<int>>& home, const int R, const int C, pair<int, int>& airCleaner) {
    int up = airCleaner.first;
    int down = airCleaner.second;

    // 반시계 방향 순환
    int tmp = 0;
    for(int i=1; i<C; ++i) {
        swap(tmp, home[up][i]);
    }
    for(int i=up-1; i>=0; --i) {
        swap(tmp, home[i][C-1]);
    }
    for(int i=C-2; i>=0; --i) {
        swap(tmp, home[0][i]);
    }
    for(int i=1; i<up; ++i) {
        swap(tmp, home[i][0]);
    }

    // 시계 방향 순환
    tmp = 0;
    for(int i=1; i<C; ++i) {
        swap(tmp, home[down][i]);
    }
    for(int i=down+1; i<R; ++i) {
        swap(tmp, home[i][C-1]);
    }
    for(int i=C-2; i>=0; --i) {
        swap(tmp, home[R-1][i]);
    }
    for(int i=R-2; i>down; --i) {
        swap(tmp, home[i][0]);
    }
}
void dustSpread(vector<vector<int>>& home, const int R, const int C, vector<dust>& dusts) {
    for(int i=0; i<dusts.size(); ++i) {
        int r = dusts[i].r;
        int c = dusts[i].c;
        int dustSize = dusts[i].dustSize;
        int cnt = 0;

        for(int j=0; j<4; ++j) {
            int nextR = r + dr[j];
            int nextC = c + dc[j];

            if(nextR < 0 || nextR >= R || nextC < 0 || nextC >= C) {
                continue;
            }
            if(home[nextR][nextC] == -1) {
                continue;
            }

            ++cnt;
            home[nextR][nextC] += dustSize / 5;
        }
        home[r][c] += dustSize - (dustSize / 5) * cnt;
    }
}
void getDustInfo(vector<vector<int>>& home, const int R, const int C, vector<dust>& dusts) {
    for(int i=0; i<R; ++i) {
        for(int j=0; j<C; ++j) {
            if(home[i][j] > 0) {
                dusts.push_back(dust(i, j, home[i][j]));
                home[i][j] = 0;
            }
        }
    }
}
void getAirCleanerInfo(vector<vector<int>>& home, const int R, pair<int, int>& airCleaner) {
    for(int i=0; i<R; ++i) {
        if(home[i][0] == -1) {
            airCleaner.first = i;
            airCleaner.second = i+1;
            break;
        }
    }
}
int solve(const int R, const int C, const int T, vector<vector<int>>& home) {
    pair<int, int> airCleaner;
    getAirCleanerInfo(home, R, airCleaner);
    int curTime = 0;
    do{
        vector<dust> dusts;
        getDustInfo(home, R, C, dusts);
        dustSpread(home, R, C, dusts);

        airCleanerOn(home, R, C, airCleaner);

        ++curTime;
    }while(curTime < T);

    int answer = getTotalDust(home, R, C);
    return answer;
}
void input(int& R, int& C, int& T, vector<vector<int>>& home) {
    cin >> R >> C >> T;
    home.assign(R, vector<int>(C, 0));
    for(int i=0; i<R; ++i) {
        for(int j=0; j<C; ++j) {
            cin >> home[i][j];
        }
    }
}
int main() {
    int R, C, T;
    vector<vector<int>> home;
    input(R, C, T, home);

    int answer = solve(R, C, T, home);
    cout << answer;

    return 0;
}
