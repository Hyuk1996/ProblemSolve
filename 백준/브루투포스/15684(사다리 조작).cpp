#include <iostream>
#include <vector>
using namespace std;


int dfs(const vector<vector<bool>>& ladder, int column, int row) {
    if(row == ladder.size()) {
        return column;
    }

    if(!ladder[row][column]) {
        if(column - 1 >= 0 && ladder[row][column -1]) { // 왼쪽으로 가는 사다리 존재
            return dfs(ladder, column - 1, row + 1);
        } else { // 사다리 존재 x
            return dfs(ladder, column, row + 1);
        }
    } else { // 오른쪽 사다리 존재하는 경우
        return dfs(ladder, column + 1, row + 1);
    }
}
bool startLadderGame(const vector<vector<bool>>& ladder) {
    for(int column=0; column<ladder[0].size(); ++column) {
        if(column != dfs(ladder, column, 0)) {
            return false;
        }
    }
    return true;
}
void addLadder(vector<vector<bool>>& ladder, int r, int c, int curDepth, int depth, bool& missionComplete) {
    if(curDepth == depth) {
        missionComplete = startLadderGame(ladder);
        return;
    }

    for(int i=r; i<ladder.size(); ++i) {
        if(i > r) {
            c = 0;
        }
        for(int j = c; j<ladder[i].size() - 1; ++j) {
            if(!ladder[i][j]) {
                if(j > 0 && ladder[i][j - 1]) { // 인접한 곳에 사다리 존재하는 경우
                    continue;
                }
                ladder[i][j] = true;
                addLadder(ladder, i, j + 1, curDepth + 1, depth, missionComplete);
                ladder[i][j] = false;
            }

            if(missionComplete) {
                break;
            }
        }

        if(missionComplete) {
            break;
        }
    }
}
int solve(vector<vector<bool>>& ladder, const int N, const int M, const int H) {
    int answer = -1;
    if(startLadderGame(ladder)) {
        answer = 0;
        return answer;
    }

    // 사다리를 최소 1개부터 3개까지 추가해주기.
    bool missionComplete = false;
    for(int i=1; i<=3; ++i) {
        addLadder(ladder, 0, 0, 0, i, missionComplete);
        if(missionComplete) {
            answer = i;
            break;
        }
    }

    return answer;
}
void input(int& N, int& M, int& H, vector<vector<bool>>& ladder) {
    cin >> N >> M >> H;
    ladder.assign(H, vector<bool>(N, false));
    for(int i=0; i<M; ++i) {
        int a, b;
        cin >> a >> b;
        ladder[a-1][b-1] = true;
    }
}
int main() {
    // 입력
    int N, M, H;
    vector<vector<bool>> ladder;
    input(N, M, H, ladder);

    int answer = solve(ladder, N, M, H);

    cout << answer;
    return 0;
}
