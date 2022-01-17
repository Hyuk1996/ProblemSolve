#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int dr[4] = {0, 0, -1, 1};
const int dc[4] = {-1, 1, 0, 0};
const int EMPTY = -1;

void getMinTime(vector<vector<int>>& lab, int& answer, vector<pair<int, int>>& activeVirus, int emptyCnt) {
    vector<vector<int>> time(lab.size(), vector<int>(lab.size(), EMPTY));
    int maxTime = 0;
    queue<pair<int, int>> q;

    for(int i=0; i<activeVirus.size(); ++i) {
        q.push(make_pair(activeVirus[i].first, activeVirus[i].second));
        time[activeVirus[i].first][activeVirus[i].second] = 0;
    }
    while(!q.empty()) {
        int curR = q.front().first;
        int curC = q.front().second;
        q.pop();

        for(int i=0; i<4; ++i) {
            int nextR = curR + dr[i];
            int nextC = curC + dc[i];

            if(nextR < 0 || nextR >= lab.size() || nextC < 0 || nextC >= lab.size()) {
                continue;
            }
            if(time[nextR][nextC] != EMPTY || lab[nextR][nextC] == 1) {
                continue;
            }

            time[nextR][nextC] = time[curR][curC] + 1;
            q.push(make_pair(nextR, nextC));
            if(lab[nextR][nextC] == 0) {
                emptyCnt--;
                maxTime = time[nextR][nextC];
            }
        }
    }

    if(emptyCnt == 0) {
        if(answer == -1) {
            answer = maxTime;
        }
        else {
            answer = min(answer, maxTime);
        }
    }
}
void getCombi(vector<pair<int, int>>& virus, int idx, vector<pair<int, int>>& activeVirus, int M, int& answer, vector<vector<int>>& lab, int emptyCnt) {
    if(activeVirus.size() == M) {
        //virus 퍼지기
        getMinTime(lab, answer, activeVirus, emptyCnt);
        return;
    }
    for(int i=idx; i < virus.size(); ++i) {
        activeVirus.push_back(virus[i]);
        getCombi(virus, i + 1, activeVirus, M, answer, lab, emptyCnt);
        activeVirus.pop_back();
    }
}
int solve(int N, int M, vector<vector<int>>& lab) {
    //바이러스 정보 얻기
    vector<pair<int, int>> virus;
    int emptyCnt = 0;
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            if(lab[i][j] == 2) {
                virus.push_back(make_pair(i, j));
            }
            else if(lab[i][j] == 0) {
                emptyCnt++;
            }
        }
    }

    //활성화할 바이러스 조합 구하기
    vector<pair<int, int>> activeVirus;
    int answer = -1;
    getCombi(virus, 0, activeVirus, M, answer, lab, emptyCnt);

    return answer;
}
void input(int& N, int& M, vector<vector<int>>& lab) {
    cin >> N >> M;
    lab.assign(N, vector<int>(N, 0));
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            cin >> lab[i][j];
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    vector<vector<int>> lab;
    input(N, M, lab);

    int answer = solve(N, M, lab);

    cout << answer;
    return 0;
}
