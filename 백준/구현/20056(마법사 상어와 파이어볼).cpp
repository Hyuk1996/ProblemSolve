#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};
struct fireBall {
    int r, c, m, s, d;
    fireBall(int r, int c, int m, int s, int d) {
        this->r = r;
        this->c = c;
        this->m = m;
        this->s = s;
        this->d = d;
    }
};

void mergeFireBalls(vector<vector<vector<fireBall>>>& map, queue<fireBall>& fireBalls, int r, int c) {
    int mSum = 0;
    int sSum = 0;
    int fireBallCnt = map[r][c].size();
    int oddCnt = 0;
    while(!map[r][c].empty()) {
        mSum += map[r][c].back().m;
        sSum += map[r][c].back().s;
        if(map[r][c].back().d % 2 == 1) {
            oddCnt++;
        }

        map[r][c].pop_back();
    }

    int newM = mSum / 5;
    int newS = sSum / fireBallCnt;
    if(newM == 0) {
        return;
    }

    if(oddCnt == 0 || oddCnt == fireBallCnt) {
        for(int k=0; k<=6; k+=2) {
            fireBalls.push(fireBall(r, c, newM, newS, k));
        }
    } else {
        for(int k=1; k<=7; k+=2) {
            fireBalls.push(fireBall(r, c, newM, newS, k));
        }
    }
}
void checkFireBalls(vector<vector<vector<fireBall>>>& map, queue<fireBall>& fireBalls, int N) {
    for(int i=1; i<=N; ++i) {
        for(int j=1; j<=N; ++j) {
            if(map[i][j].size() == 0) {
                continue;
            } else if(map[i][j].size() == 1){
                fireBalls.push(map[i][j][0]);
                map[i][j].pop_back();
            } else {
                mergeFireBalls(map, fireBalls, i, j);
            }
        }
    }
}
void moveFireBall(vector<vector<vector<fireBall>>>& map, queue<fireBall>& fireBalls, int N) {
    while(!fireBalls.empty()) {
        int r = fireBalls.front().r;
        int c = fireBalls.front().c;
        int m = fireBalls.front().m;
        int s = fireBalls.front().s;
        int d = fireBalls.front().d;
        fireBalls.pop();

        // N칸을 움직이는 것은 움직이지 않는 것과 동일하다.
        int tmpS = s % N;
        while(tmpS--) {
            r = r + dr[d];
            c = c + dc[d];

            if(r == 0) {
                r = N;
            }
            if(r == N+1) {
                r = 1;
            }
            if(c == 0) {
                c = N;
            }
            if(c == N+1) {
                c = 1;
            }
        }

        map[r][c].push_back(fireBall(r, c, m, s, d));
    }
}
int simulation(int N, int M, int K, queue<fireBall>& fireBalls) {
    vector<vector<vector<fireBall>>> map(N+1, vector<vector<fireBall>>(N+1, vector<fireBall>()));
    int curMove = 1;
    while(true) {

        moveFireBall(map, fireBalls, N);

        checkFireBalls(map, fireBalls, N);

        if(curMove == K) {
            break;
        } else {
            curMove++;
        }
    }

    int answer = 0;
    while(!fireBalls.empty()) {
        answer += fireBalls.front().m;
        fireBalls.pop();
    }
    return answer;
}
void input(int& N, int& M, int& K, queue<fireBall>& fireBalls) {
    cin >> N >> M >> K;
    int r, c, m, s, d;
    for(int i=0; i<M; ++i) {
        cin >> r >> c >> m >> s >> d;
        fireBalls.push(fireBall(r, c, m, s, d));
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, K;
    queue<fireBall> fireBalls;
    input(N, M, K, fireBalls);

    int answer = simulation(N, M, K, fireBalls);

    cout << answer;
    return 0;
}
