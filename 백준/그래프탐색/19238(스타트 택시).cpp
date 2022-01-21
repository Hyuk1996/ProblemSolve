#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int dr[4] = {0, 0, -1, 1};
const int dc[4] = {-1, 1, 0, 0};
const int INF = 987654321;
const int WALL = -1;
struct custom {
    int startR, startC;
    int destR, destC;
    custom(int startR, int startC, int destR, int destC) {
        this->startR = startR;
        this->startC = startC;
        this->destR = destR;
        this->destC = destC;
    }
};

bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    if(a.first == b.first) {
        return a.second < b.second;
    }
    return a.first < b.first;
}
int findDistToDest(vector<vector<int>>& map, pair<int, int>& startPoint, int destR, int destC) {
    vector<vector<int>> dist(map.size(), vector<int>(map.size(), INF));
    queue<pair<int, int>> q;

    q.push(make_pair(startPoint.first, startPoint.second));
    dist[startPoint.first][startPoint.second] = 0;
    while(!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        for(int i=0; i<4; ++i) {
            int nextR = r + dr[i];
            int nextC = c + dc[i];

            if(nextR < 1 || nextR >= map.size() || nextC < 1 || nextC >= map.size()) {
                continue;
            }
            if(map[nextR][nextC] == -1 || dist[nextR][nextC] != INF) {
                continue;
            }

            if(nextR == destR && nextC == destC) {
                return dist[r][c] + 1;
            } else {
                q.push(make_pair(nextR, nextC));
                dist[nextR][nextC] = dist[r][c] + 1;
            }
        }
    }
    return -1;
}
void findCustoms(int N, vector<vector<int>>& map, pair<int, int>& startPoint, int& dist, int& customIdx) {
    vector<vector<bool>> isVisited(N+1, vector<bool>(N+1, false));
    queue<pair<int, int>> q;
    vector<pair<int, int>> nearCustoms;

    q.push(make_pair(startPoint.first, startPoint.second));
    isVisited[startPoint.first][startPoint.second] = true;
    bool findCustom = false;
    while(!q.empty()) {
        int qSize = q.size();

        for(int i=0; i<qSize; ++i) {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();

            if(map[r][c] > 0) {
                nearCustoms.push_back(make_pair(r, c));
                findCustom = true;
                continue;
            }

            for(int j=0; j<4; ++j) {
                int nextR = r + dr[j];
                int nextC = c + dc[j];

                if(nextR < 1 || nextR > N || nextC < 1 || nextC > N) {
                    continue;
                }
                if(isVisited[nextR][nextC] || map[nextR][nextC] == WALL) {
                    continue;
                }

                q.push(make_pair(nextR, nextC));
                isVisited[nextR][nextC] = true;
            }
        }

        if(findCustom) {
            break;
        } else {
            dist++;
        }
    }

    //손님이 없는 경우
    if(nearCustoms.empty()) {
        customIdx = -1;
        return;
    } else {
        sort(nearCustoms.begin(), nearCustoms.end(), cmp);
        customIdx = map[nearCustoms[0].first][nearCustoms[0].second];
        return;
    }
}
int solve(int N, int M, int oil, vector<vector<int>>& map, pair<int, int>& startPoint, vector<custom>& customs) {
    int customCnt = 0;

    //존재하는 손님들 정보 map에 추가.
    for(int i=1; i<=M; ++i) {
        map[customs[i].startR][customs[i].startC] = i;
    }

    while(true) {

        //BFS로 제일 가까운 손님 찾기
        int dist = 0;
        int customIdx = -1;
        findCustoms(N, map, startPoint, dist, customIdx);

        if(customIdx == -1 || dist > oil) {
            oil = -1;
            break;
        }

        //손님한테 가기
        oil -= dist;
        startPoint.first = customs[customIdx].startR;
        startPoint.second = customs[customIdx].startC;
        map[customs[customIdx].startR][customs[customIdx].startC] = 0;

        //손님 목적지
        dist = findDistToDest(map, startPoint, customs[customIdx].destR, customs[customIdx].destC);

        //목적지까지 가지 못하는 경우
        if(dist == -1 || dist > oil) {
            oil = -1;
            break;
        }

        oil -= dist;
        oil += (dist * 2);
        startPoint.first = customs[customIdx].destR;
        startPoint.second = customs[customIdx].destC;
        customCnt++;

        if(customCnt == M) {
            break;
        }
    }
    return oil;
}
void input(int& N, int& M, int& oil, vector<vector<int>>& map, pair<int, int>& startPoint, vector<custom>& customs) {
    cin >> N >> M >> oil;
    map.assign(N+1, vector<int>(N+1, 0));
    for(int i=1; i<=N; ++i) {
        for(int j=1; j<=N; ++j) {
            cin >> map[i][j];
            if(map[i][j] == 1) {
                map[i][j] = WALL;
            }
        }
    }
    cin >> startPoint.first >> startPoint.second;

    customs.assign(M+1, {0, 0, 0, 0});
    int startR, startC, destR, destC;
    for(int i=1; i<=M; ++i) {
        cin >> startR >> startC >> destR >> destC;
        customs[i].startR = startR;
        customs[i].startC = startC;
        customs[i].destR = destR;
        customs[i].destC = destC;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, oil;
    vector<vector<int>> map;
    pair<int, int> startPoint;
    vector<custom> customs;
    input(N, M, oil, map, startPoint, customs);

    int answer = solve(N, M, oil, map, startPoint, customs);

    cout << answer;
    return 0;
}
