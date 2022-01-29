#include <iostream>
#include <vector>
using namespace std;
const int dr[9] = {-2, 0, -1, -1, -1, 0, 1, 1, 1};
const int dc[9] = {-2, -1, -1, 0, 1, 1, 1, 0, -1};
struct moveInfo {
    int d, s;
    moveInfo (int d, int s) {
        this->d = d;
        this->s = s;
    }
};

void makeClouds(vector<vector<int>>& map, int N, vector<pair<int, int>>& clouds, vector<vector<bool>>& isVisited) {
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            if(isVisited[i][j]) {
                continue;
            }

            if(map[i][j] >= 2) {
                map[i][j] -= 2;
                clouds.push_back({i, j});
            }
        }
    }
}
int check(vector<vector<int>>& map, int N, int r, int c) {
    int cnt = 0;

    for(int i = 2; i <= 8; i += 2) {
        int nextR = r + dr[i];
        int nextC = c + dc[i];

        if(nextR < 1 || nextR > N || nextC < 1 || nextC > N) {
            continue;
        }

        if(map[nextR][nextC] > 0) {
            cnt++;
        }
    }
    return cnt;
}
void copyWatersAndRemoveClouds(vector<vector<int>>& map, int N, vector<pair<int, int>>& clouds, vector<vector<bool>>& isVisited) {
    vector<vector<int>> cnts(N + 1, vector<int>(N + 1, 0));

    for(int i = 0; i < clouds.size(); ++i) {
        int r = clouds[i].first;
        int c = clouds[i].second;

        map[r][c] += check(map, N, r, c);
    }

    clouds.clear();
}
void increaseWater(vector<vector<int>>& map, vector<pair<int, int>>& clouds, vector<vector<bool>>& isVisited) {

    for(int i = 0; i < clouds.size(); ++i) {
        int r = clouds[i].first;
        int c = clouds[i].second;

        map[r][c]++;
        isVisited[r][c] = true;
    }
}
void moveClouds(vector<pair<int, int>>& clouds, int d, int s, int N) {

    s = s % N;

    for(int i = 0; i < clouds.size(); ++i) {
        int r = clouds[i].first;
        int c = clouds[i].second;

        r = r + dr[d] * s;
        c = c + dc[d] * s;

        if(r < 1) {
            r += N;
        } else if(r > N) {
            r -= N;
        }

        if(c < 1) {
            c += N;
        } else if(c > N) {
            c -= N;
        }

        clouds[i].first = r;
        clouds[i].second = c;
    }
}
int simulation(int N, int M, vector<vector<int>>& map, vector<moveInfo>& moveInfos) {
    vector<pair<int, int>> clouds;
    clouds.push_back({N, 1});
    clouds.push_back({N, 2});
    clouds.push_back({N - 1, 1});
    clouds.push_back({N - 1, 2});

    for(int i = 0; i < moveInfos.size(); ++i) {
        int d = moveInfos[i].d;
        int s = moveInfos[i].s;

        moveClouds(clouds, d, s, N);

        vector<vector<bool>> isVisited(N + 1, vector<bool>(N + 1, false));
        increaseWater(map, clouds, isVisited);

        copyWatersAndRemoveClouds(map, N, clouds, isVisited);

        makeClouds(map, N, clouds, isVisited);
    }

    int waterSum = 0;
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            waterSum += map[i][j];
        }
    }
    return waterSum;
}
void input(int& N, int& M, vector<vector<int>>& map, vector<moveInfo>& moveInfos) {
    cin >> N >> M;
    map.assign(N+1, vector<int>(N+1, 0));
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            cin >> map[i][j];
        }
    }
    moveInfos.assign(M, {0, 0});
    for(int i = 0; i < M; ++i) {
        cin >> moveInfos[i].d >> moveInfos[i].s;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    vector<vector<int>> map;
    vector<moveInfo> moveInfos;
    input(N, M, map, moveInfos);

    int answer = simulation(N, M, map, moveInfos);

    cout << answer;
    return 0;
}
