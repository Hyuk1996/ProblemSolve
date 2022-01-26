#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;
const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};

void dfs(vector<vector<int>>& A, int r, int c, vector<vector<bool>>& isVisited, int& areaSize) {
    isVisited[r][c] = true;
    areaSize++;

    for(int i=0; i<4; ++i) {
        int nextR = r + dr[i];
        int nextC = c + dc[i];

        if(nextR < 0 || nextR >= A.size() || nextC < 0 || nextC >= A.size()) {
            continue;
        }
        if(A[nextR][nextC] == 0 || isVisited[nextR][nextC]) {
            continue;
        }

        dfs(A, nextR, nextC, isVisited, areaSize);
    }
}
int getMaxArea(vector<vector<int>>& A, int N) {
    int maxArea = 0;
    vector<vector<bool>> isVisited(N, vector<bool>(N, false));
    for(int r=0; r<N; ++r) {
        for(int c=0; c<N; ++c) {
            if(!isVisited[r][c] && A[r][c] > 0) {
                int areaSize = 0;
                dfs(A, r, c, isVisited, areaSize);
                maxArea = max(maxArea, areaSize);
            }
        }
    }
    return maxArea;
}
int getIceSum(vector<vector<int>>& A, int N) {
    int iceSum = 0;
    for(int r=0; r<N; ++r) {
        for(int c=0; c<N; ++c) {
            iceSum += A[r][c];
        }
    }
    return iceSum;
}
bool check(vector<vector<int>>& A, int r, int c, int N) {
    int iceCnt = 0;
    for(int i = 0; i < 4; ++i) {
        int nextR = r + dr[i];
        int nextC = c + dc[i];

        if(nextR < 0 || nextR >= N || nextC < 0 || nextC >=N) {
            continue;
        }

        if(A[nextR][nextC] > 0) {
            iceCnt++;
        }
    }

    if(iceCnt > 2) {
        return false;
    } else {
        return true;
    }
}
void removeIce(vector<vector<int>>& A, int N) {
    vector<vector<bool>> isRemoved(N, vector<bool>(N, false));
    for(int r = 0; r < N; ++r) {
        for(int c = 0; c < N; ++c) {
            if(A[r][c] == 0) {
                continue;
            }

            if(check(A, r, c, N)) {
                isRemoved[r][c] = true;
            }
        }
    }

    for(int r = 0; r < N; ++r) {
        for(int c = 0; c < N; ++c) {
            if(isRemoved[r][c]) {
                A[r][c]--;
            }
        }
    }
}
void rotateA(vector<vector<int>>& A, int N, int l) {
    for(int r = 0; r < N; r += l) {
        for(int c = 0; c < N; c += l) {

            queue<int> tmp;
            for(int tmpR = r; tmpR < r + l; ++tmpR) {
                for(int tmpC = c; tmpC < c + l; ++tmpC) {
                    tmp.push(A[tmpR][tmpC]);
                }
            }

            for(int tmpC = c + l - 1; tmpC >= c; --tmpC) {
                for (int tmpR = r; tmpR < r + l; ++tmpR) {
                    A[tmpR][tmpC] = tmp.front();
                    tmp.pop();
                }
            }
        }
    }
}
pair<int, int> simulation(int N, int Q, vector<vector<int>>& A, vector<int>& L) {

    for(int i = 0; i < Q; ++i) {
        int l = L[i];
        l = pow(2, l);

        rotateA(A, N, l);
        removeIce(A, N);
    }

    int iceSum = getIceSum(A, N);
    int maxArea = getMaxArea(A, N);

    return {iceSum, maxArea};
}
void input(int& N, int& Q, vector<vector<int>>& A, vector<int>& L) {
    cin >> N >> Q;
    N = pow(2, N);
    A.assign(N, vector<int>(N, 0));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> A[i][j];
        }
    }
    L.assign(Q, 0);
    for(int i = 0; i < Q; ++i) {
        cin >> L[i];
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, Q;
    vector<vector<int>> A;
    vector<int> L;
    input(N, Q, A, L);

    pair<int, int> answer = simulation(N, Q, A, L);

    cout << answer.first << '\n';
    cout << answer.second << '\n';
    return 0;
}
