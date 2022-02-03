#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX_FISH = 10001;
const int dr[4] = {0, 0, -1, 1};
const int dc[4] = {-1, 1, 0, 0};

int getFishDiff(int N ,vector<stack<int>>& fish) {
    int maxFish = -1;
    int minFish = MAX_FISH;
    for(int i = 0; i < N; ++i) {
        maxFish = max(maxFish, fish[i].top());
        minFish = min(minFish, fish[i].top());
    }
    return maxFish - minFish;
}
void move2(int N, vector<stack<int>>& fish) {
    int left = 0;
    int right, curIdx;
    for(int i = 0; i < 2; ++i) {
        N /= 2;
        right = left + N - 1;

        curIdx = right + 1;
        for(int j = right; j >= left; --j) {
            while(!fish[j].empty()) {
                fish[curIdx].push(fish[j].top());
                fish[j].pop();
            }
            curIdx++;
        }

        left = right + 1;
    }
}
void mapToFish(int N, vector<stack<int>>& fish, vector<vector<int>>& map) {
    int idx = 0;
    for(int c = 0; c < N; ++c) {
        for(int r = N - 1; r >= 0; --r) {
            if(map[r][c] != -1) {
                fish[idx++].push(map[r][c]);
            }
        }
    }
}
void control(int N, vector<vector<int>>& map, vector<vector<int>>& controlCnt, int r, int c) {
    for(int i = 0; i < 4; ++i) {
        int nextR = r + dr[i];
        int nextC = c + dc[i];

        if(nextR < 0 || nextR >= N || nextC < 0 || nextC >= N) {
            continue;
        }
        if(map[nextR][nextC] == -1 || map[r][c] <= map[nextR][nextC]) {
            continue;
        }

        int diff = map[r][c] - map[nextR][nextC];
        diff /= 5;
        controlCnt[r][c] -= diff;
        controlCnt[nextR][nextC] += diff;
    }
}
void fishToMap(int N, vector<stack<int>>& fish, vector<vector<int>>& map) {
    for(int c = 0; c < N; ++c) {
        int r = N - fish[c].size();
        while(!fish[c].empty()) {
            map[r][c] = fish[c].top();
            fish[c].pop();
            r++;
        }
    }
}
void controlFish(int N, vector<stack<int>>& fish) {

    vector<vector<int>> map(N, vector<int>(N, -1));
    fishToMap(N, fish, map);

    //온도 조절
    vector<vector<int>> controlCnt(N, vector<int>(N, 0));
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if(map[i][j] > 0) {
                control(N, map, controlCnt, i, j);
            }
        }
    }

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            map[i][j] += controlCnt[i][j];
        }
    }

    mapToFish(N, fish, map);
}
void move(int N, vector<stack<int>>& fish) {
    fish[1].push(fish[0].top());
    fish[0].pop();

    while(true) {
        int startIdx = -1;

        for(int i = 0; i < N; ++i) {
            if(fish[i].size() == 1) {
                break;
            }
            startIdx++;
        }

        if((startIdx + fish[startIdx].size()) >= N) {
            break;
        }

        for(int i = startIdx; i >= 0; --i) {
            while(!fish[i].empty()) {
                fish[startIdx + fish[i].size()].push(fish[i].top());
                fish[i].pop();
            }
        }
    }
}
void addFish(int N, vector<stack<int>>& fish) {
    vector<int> idx;
    int minFish = MAX_FISH;
    for(int i = 0; i < N; ++i) {
        if(fish[i].top() < minFish) {
            idx.clear();
            idx.push_back(i);
            minFish = fish[i].top();
        } else if(fish[i].top() == minFish) {
            idx.push_back(i);
        }
    }

    for(int i = 0; i < idx.size(); ++i) {
        int tmpCnt = fish[idx[i]].top();
        fish[idx[i]].pop();

        fish[idx[i]].push(tmpCnt + 1);
    }
}
int solve(int N, int K, vector<stack<int>>& fish) {
    int count = 1;

    while(true) {
        addFish(N, fish);

        move(N, fish);

        controlFish(N, fish);

        move2(N, fish);

        controlFish(N, fish);

        if(K >= getFishDiff(N ,fish)) {
            break;
        }
        count++;
    }
    return count;
}
void input(int& N, int& K, vector<stack<int>>& fish) {
    cin >> N >> K;
    fish.assign(N, stack<int>());
    for(int i = 0; i < N; ++i) {
        int fishCnt;
        cin >> fishCnt;
        fish[i].push(fishCnt);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, K;
    vector<stack<int>> fish;
    input(N, K, fish);

    int answer = solve(N, K, fish);

    cout << answer;
    return 0;
}
