#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
const int dr[4] = {0, 0, -1, 1};
const int dc[4] = {-1, 1, 0, 0};

void movePopulation(vector<vector<int>>& ground, vector<vector<int>>& visit, int teamSize) {
    vector<int> populations(teamSize, 0);
    vector<int> teamCount(teamSize, 0);
    for(int i=0; i<ground.size(); ++i) {
        for(int j=0; j<ground.size(); ++j) {
            populations[visit[i][j]] += ground[i][j];
            ++teamCount[visit[i][j]];
        }
    }

    for(int i=1; i<populations.size(); ++i) {
        populations[i] = populations[i] / teamCount[i];
    }

    for(int i=0; i<ground.size(); ++i) {
        for(int j=0; j<ground.size(); ++j) {
            ground[i][j] = populations[visit[i][j]];
        }
    }
}
void dfs(vector<vector<int>>& ground, int r, int c, vector<vector<int>>& visit, int& teamNo, bool& isFinish, int L, int R) {
    visit[r][c] = teamNo;

    for(int i=0; i<4; ++i) {
        int nextR = r + dr[i];
        int nextC = c + dc[i];

        if(nextR < 0 || nextR >= ground.size() || nextC < 0 || nextC >= ground.size()) {
            continue;
        }
        int diff = abs(ground[r][c] - ground[nextR][nextC]);
        if(diff < L || diff > R) {
            continue;
        }
        if(visit[nextR][nextC] != 0) {
            continue;
        }
        isFinish = true;
        dfs(ground, nextR, nextC, visit, teamNo, isFinish, L, R);
    }
}
bool boarderCheck(vector<vector<int>>& ground, vector<vector<int>>& visit, int& teamNo, int L, int R) {
    bool isPossible = false;
    for(int i=0; i<ground.size(); ++i) {
        for(int j=0; j<ground.size(); ++j) {
            if(visit[i][j] == 0) {
                dfs(ground, i, j, visit, teamNo, isPossible, L, R);
                ++teamNo;
            }
        }
    }
    return isPossible;
}
int solve(const int N, const int L, const int R, vector<vector<int>>& ground) {
    int dayCount = 0;
    while(true) {
        vector<vector<int>> visit(N, vector<int>(N, false));
        int teamNo = 1; //연합국 식별 번호
        if(!boarderCheck(ground, visit, teamNo, L, R)) {
            break;
        }

        movePopulation(ground, visit, teamNo);
        ++dayCount;
    }
    return dayCount;
}
void input(int& N, int& L, int& R, vector<vector<int>>& ground) {
    cin >> N >> L >> R;
    ground.assign(N, vector<int>(N, 0));
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            cin >> ground[i][j];
        }
    }
}
int main() {
    int N, L, R;
    vector<vector<int>> ground;
    input(N, L, R, ground);

    int answer = solve(N, L, R, ground);
    cout << answer;
    return 0;
}
