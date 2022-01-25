#include <iostream>
#include <vector>
using namespace std;
const int dr[4] = {0, 1, 0, -1};
const int dc[4] = {-1, 0, 1, 0};

void spreadSand(int N, vector<vector<int>>& map, int r, int c, int nextR, int nextC, int d, int& outSandSum) {
    int oneP = map[nextR][nextC] / 100;
    int twoP = (map[nextR][nextC] * 2) / 100;
    int sevenP = (map[nextR][nextC] * 7) / 100;
    int tenP = (map[nextR][nextC] * 10) / 100;
    int fiveP = (map[nextR][nextC] * 5) / 100;
    int a = map[nextR][nextC] - ((oneP * 2) + (twoP * 2) + (sevenP * 2) + (tenP * 2) + (fiveP));
    map[nextR][nextC] = 0;

    if(d % 2 == 0) {
        int oneR = r + dr[1];
        int oneC = c + dc[1];
        if(oneR < 1 || oneR > N || oneC < 1 || oneC > N) {
            outSandSum += oneP;
        } else {
            map[oneR][oneC] += oneP;
        }

        oneR = r + dr[3];
        oneC = c + dc[3];
        if(oneR < 1 || oneR > N || oneC < 1 || oneC > N) {
            outSandSum += oneP;
        } else {
            map[oneR][oneC] += oneP;
        }

        int sevenR = nextR + dr[1];
        int sevenC = nextC + dc[1];
        if(sevenR < 1 || sevenR > N || sevenC < 1 || sevenC > N) {
            outSandSum += sevenP;
        } else {
            map[sevenR][sevenC] += sevenP;
        }

        sevenR = nextR + dr[3];
        sevenC = nextC + dc[3];
        if(sevenR < 1 || sevenR > N || sevenC < 1 || sevenC > N){
            outSandSum += sevenP;
        } else {
            map[sevenR][sevenC] += sevenP;
        }

        int twoR = nextR + dr[1] * 2;
        int twoC = nextC + dc[1] * 2;
        if(twoR < 1 || twoR > N || twoC < 1 || twoC > N) {
            outSandSum += twoP;
        } else {
            map[twoR][twoC] += twoP;
        }

        twoR = nextR + dr[3] * 2;
        twoC = nextC + dc[3] * 2;
        if(twoR < 1 || twoR > N || twoC < 1 || twoC > N) {
            outSandSum += twoP;
        } else {
            map[twoR][twoC] += twoP;
        }

        int aR = nextR + dr[d];
        int aC = nextC + dc[d];
        if(aR < 1 || aR > N || aC < 1 || aC > N) {
            outSandSum += a;
        } else {
            map[aR][aC] += a;
        }

        int tenR = aR + dr[1];
        int tenC = aC + dc[1];
        if(tenR < 1 || tenR > N || tenC < 1 || tenC > N) {
            outSandSum += tenP;
        } else {
            map[tenR][tenC] += tenP;
        }

        tenR = aR + dr[3];
        tenC = aC + dc[3];
        if(tenR < 1 || tenR > N || tenC < 1 || tenC > N) {
            outSandSum += tenP;
        } else {
            map[tenR][tenC] += tenP;
        }

        int fiveR = aR + dr[d];
        int fiveC = aC + dc[d];
        if(fiveR < 1 || fiveR > N || fiveC < 1 || fiveC > N) {
            outSandSum += fiveP;
        } else {
            map[fiveR][fiveC] += fiveP;
        }
    } else { // 방향이 위, 아래
        int oneR = r + dr[0];
        int oneC = c + dc[0];
        if(oneR < 1 || oneR > N || oneC < 1 || oneC > N) {
            outSandSum += oneP;
        } else {
            map[oneR][oneC] += oneP;
        }

        oneR = r + dr[2];
        oneC = c + dc[2];
        if(oneR < 1 || oneR > N || oneC < 1 || oneC > N) {
            outSandSum += oneP;
        } else {
            map[oneR][oneC] += oneP;
        }

        int sevenR = nextR + dr[0];
        int sevenC = nextC + dc[0];
        if(sevenR < 1 || sevenR > N || sevenC < 1 || sevenC > N) {
            outSandSum += sevenP;
        } else {
            map[sevenR][sevenC] += sevenP;
        }

        sevenR = nextR + dr[2];
        sevenC = nextC + dc[2];
        if(sevenR < 1 || sevenR > N || sevenC < 1 || sevenC > N){
            outSandSum += sevenP;
        } else {
            map[sevenR][sevenC] += sevenP;
        }

        int twoR = nextR + dr[0] * 2;
        int twoC = nextC + dc[0] * 2;
        if(twoR < 1 || twoR > N || twoC < 1 || twoC > N) {
            outSandSum += twoP;
        } else {
            map[twoR][twoC] += twoP;
        }

        twoR = nextR + dr[2] * 2;
        twoC = nextC + dc[2] * 2;
        if(twoR < 1 || twoR > N || twoC < 1 || twoC > N) {
            outSandSum += twoP;
        } else {
            map[twoR][twoC] += twoP;
        }

        int aR = nextR + dr[d];
        int aC = nextC + dc[d];
        if(aR < 1 || aR > N || aC < 1 || aC > N) {
            outSandSum += a;
        } else {
            map[aR][aC] += a;
        }

        int tenR = aR + dr[0];
        int tenC = aC + dc[0];
        if(tenR < 1 || tenR > N || tenC < 1 || tenC > N) {
            outSandSum += tenP;
        } else {
            map[tenR][tenC] += tenP;
        }

        tenR = aR + dr[2];
        tenC = aC + dc[2];
        if(tenR < 1 || tenR > N || tenC < 1 || tenC > N) {
            outSandSum += tenP;
        } else {
            map[tenR][tenC] += tenP;
        }

        int fiveR = aR + dr[d];
        int fiveC = aC + dc[d];
        if(fiveR < 1 || fiveR > N || fiveC < 1 || fiveC > N) {
            outSandSum += fiveP;
        } else {
            map[fiveR][fiveC] += fiveP;
        }
    }
}
int simulation(int N, vector<vector<int>>& map) {
    int outSandSum = 0;
    int r = N / 2 + 1;
    int c = N / 2 + 1;
    int d = 0;
    int dist = 1;
    int nextR, nextC;

    while(true) {
        for(int i=0; i<2; ++i) {
            for(int j=0; j<dist; ++j) {
                nextR = r + dr[d];
                nextC = c + dc[d];
                spreadSand(N, map, r, c, nextR, nextC, d, outSandSum);

                r = nextR;
                c = nextC;
            }
            d = (d+1) % 4;
        }

        dist++;
        if(dist == N) {
            for(int i=0; i<N-1; ++i) {
                nextR = r + dr[d];
                nextC = c + dc[d];
                spreadSand(N, map, r, c, nextR, nextC, d, outSandSum);

                r = nextR;
                c = nextC;
            }
            break;
        }
    }
    return outSandSum;
}
void input(int& N, vector<vector<int>>& map) {
    cin >> N;
    map.assign(N+1, vector<int>(N+1, 0));
    for(int i=1; i<=N; ++i) {
        for(int j=1; j<=N; ++j) {
            cin >> map[i][j];
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    vector<vector<int>> map;
    input(N, map);

    int answer = simulation(N, map);

    cout << answer;
    return 0;
}
