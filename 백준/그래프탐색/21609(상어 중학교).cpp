#include<iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
const int EMPTY = -2;
const int dr[4] = {0, 0, -1, 1};
const int dc[4] = {-1, 1, 0, 0};
struct group {
    int size;
    int rainbowCnt;
    int r;
    int c;

    group(int size, int rainbowCnt, int r, int c) {
        this->size = size;
        this->rainbowCnt = rainbowCnt;
        this->r = r;
        this->c = c;
    }
};

bool cmp(const group& a, const group& b) {
    if(a.size == b.size) {
        if(a.rainbowCnt == b.rainbowCnt) {
            if(a.r == b.r) {
                return a.c > b.c;
            } else {
                return a.r > b.r;
            }
        } else {
            return a.rainbowCnt > b.rainbowCnt;
        }
    }
    return a.size > b. size;
}
void rotate(int N, vector<vector<int>>& map) {
    queue<int> q;
    for(int r = 0; r < N; ++r) {
        for(int c = N - 1; c >= 0; --c) {
            q.push(map[r][c]);
        }
    }

    for(int c = 0; c < N; ++c) {
        for(int r = 0; r < N; ++r) {
            map[r][c] = q.front();
            q.pop();
        }
    }
}
void gravity(int N, vector<vector<int>>& map) {
    for(int c = 0; c < N; ++c) {
        for(int r = N -1; r >= 0; --r) {
            if(map[r][c] == -1) {
                continue;
            }

            int curR = r;
            while(true) {
                int nextR = curR + 1;
                if(nextR < N && map[nextR][c] == EMPTY) {
                    swap(map[curR][c], map[nextR][c]);
                    curR = nextR;
                } else {
                    break;
                }
            }
        }
    }
}
void removeGroup(int N, vector<vector<int>>& map, int r, int c) {
    queue<pair<int, int>> q;
    int blockIdx = map[r][c];

    map[r][c] = EMPTY;
    q.push(make_pair(r, c));
    while(!q.empty()) {
        int curR = q.front().first;
        int curC = q.front().second;
        q.pop();

        for(int i=0; i<4; ++i) {
            int nextR = curR + dr[i];
            int nextC = curC + dc[i];

            if(nextR < 0 || nextR >= N || nextC < 0 || nextC >= N) {
                continue;
            }

            if(map[nextR][nextC] == 0 || map[nextR][nextC] == blockIdx) {
                map[nextR][nextC] = EMPTY;
                q.push(make_pair(nextR, nextC));
            }
        }
    }
}
void dfs(vector<vector<int>>& map, int r, int c, vector<vector<bool>>& isVisited, vector<vector<bool>>& isGrouped, int& size, int& rainbowCnt, int& blockR, int& blockC) {

    isVisited[r][c] = true;

    size++;
    if(map[r][c] == map[blockR][blockC]) {
        isGrouped[r][c] = true;
        if(blockR > r) {
            blockR = r;
            blockC = c;
        } else if(blockR == r) {
            if(blockC > c) {
                blockC = c;
            }
        }
    } else {
        rainbowCnt++;
    }

    for(int i=0; i<4; ++i) {
        int nextR = r + dr[i];
        int nextC = c + dc[i];

        if(nextR < 0 || nextR >= map.size() || nextC < 0 || nextC >= map.size()) {
            continue;
        }
        if(isVisited[nextR][nextC]) {
            continue;
        }

        if(map[nextR][nextC] == 0 || map[nextR][nextC] == map[blockR][blockC]) {
            dfs(map, nextR, nextC, isVisited, isGrouped, size, rainbowCnt, blockR, blockC);
        }
    }

}
void findGroups(int N, int M, vector<vector<int>>& map, vector<group>& groups) {
    vector<vector<bool>> isGrouped(N, vector<bool>(N, false));
    int size, rainbowCnt, blockR, blockC;

    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            if(map[i][j] > 0 && !isGrouped[i][j]) {
                size = 0;
                rainbowCnt = 0;
                blockR = i;
                blockC = j;
                vector<vector<bool>> isVisited(N, vector<bool>(N, false));
                dfs(map, i, j, isVisited, isGrouped, size, rainbowCnt, blockR, blockC);

                if(size >= 2) {
                    groups.push_back(group(size, rainbowCnt, blockR, blockC));
                }
            }
        }
    }
}
int simulation(int N, int M, vector<vector<int>>& map) {
    int totalScore = 0;

    while(true) {

        vector<group> groups;
        findGroups(N, M, map, groups);

        if(groups.empty()) {
            break;
        }

        sort(groups.begin(), groups.end(), cmp);
        removeGroup(N, map, groups[0].r, groups[0].c);
        totalScore += groups[0].size * groups[0].size;

        gravity(N, map);

        rotate(N, map);

        gravity(N, map);
    }

    return totalScore;
}
void input(int& N, int& M, vector<vector<int>>& map) {
    cin >> N >> M;
    map.assign(N, vector<int>(N, 0));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cin >> map[i][j];
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M;
    vector<vector<int>> map;
    input(N, M, map);

    int answer = simulation(N, M, map);

    cout << answer;
    return 0;
}
