#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
const int fishR[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1,};
const int fishC[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
const int sharkR[5] = {0, -1, 0, 1, 0};
const int sharkC[5] = {0, 0, -1, 0, 1};
struct fish {
    int r, c, d;
    fish(int r, int c, int d) {
        this->r = r;
        this->c = c;
        this->d = d;
    }
};


void copyFish(vector<vector<vector<int>>>& fishMap, vector<fish>& fishes, vector<fish>& copyFishes) {
    fishes.clear();

    for(int i = 1; i <= 4; ++i) {
        for(int j = 1; j <= 4; ++j) {
            for(int k = 0; k < fishMap[i][j].size(); ++k) {
                fishes.push_back(fish(i, j, fishMap[i][j][k]));
            }
        }
    }

    for(int i = 0; i < copyFishes.size(); ++i) {
        fishes.push_back(copyFishes[i]);
    }
}
void updateState(vector<vector<int>>& state) {
    for(int i = 1; i <= 4; ++i) {
        for(int j = 1; j <= 4; ++j) {
            if(state[i][j] > 0) {
                state[i][j]--;
            }
        }
    }
}
void recursive(int r, int c, int removeFishCnt, string move, pair<int, string>& tmp, vector<vector<int>>& fishCnt) {
    if(move.size() == 3) {
        if(removeFishCnt > tmp.first) {
            tmp.first = removeFishCnt;
            tmp.second = move;
        }
        return;
    }
    for(int i = 1; i <= 4; ++i) {
        int nextR = r + sharkR[i];
        int nextC = c + sharkC[i];

        if((1 <= nextR && nextR <= 4) && (1 <= nextC && nextC <= 4)) {
            int tmpCnt = fishCnt[nextR][nextC];
            fishCnt[nextR][nextC] = 0;

            recursive(nextR, nextC, removeFishCnt + tmpCnt, move + to_string(i), tmp, fishCnt);

            fishCnt[nextR][nextC] = tmpCnt;
        }
    }
}
void moveShark(pair<int, int>& shark, vector<vector<vector<int>>>& fishMap, vector<vector<int>>& state) {
    pair<int, string> tmp;
    tmp.first = -1;
    tmp.second = "";

    vector<vector<int>> fishCnt(5, vector<int>(5, 0));
    for(int i = 1; i <= 4; ++i) {
        for(int j = 1; j <=4; ++j) {
            fishCnt[i][j] = fishMap[i][j].size();
        }
    }

    recursive(shark.first, shark.second, 0, "", tmp, fishCnt);

    string move = tmp.second;
    int r = shark.first;
    int c = shark.second;
    for(int i = 0; i < move.size(); ++i) {
        r += sharkR[move[i] - '0'];
        c += sharkC[move[i] - '0'];

        if(fishMap[r][c].size() > 0) {
            state[r][c] = 3;
            fishMap[r][c].clear();
        }
    }
    shark.first = r;
    shark.second = c;
}
void moveFishes(vector<vector<vector<int>>>& fishMap, vector<fish>& fishes, vector<vector<int>>& smell, pair<int, int>& shark) {
    for(int i = 0; i < fishes.size(); ++i) {
        int r = fishes[i].r;
        int c = fishes[i].c;
        int d = fishes[i].d;

        bool isMoved = false;

        for(int j = 0; j < 8; ++j) {
            int nextR = r + fishR[d];
            int nextC = c + fishC[d];

            if((1 <= nextR && nextR <= 4) && (1 <= nextC && nextC <= 4)) {
                if(smell[nextR][nextC] == 0 && !(nextR == shark.first && nextC == shark.second)) {
                    fishMap[nextR][nextC].push_back(d);
                    isMoved = true;
                    break;
                }
            }

            if(d == 1) {
                d = 8;
            } else {
                d--;
            }
        }

        if(!isMoved) {
            fishMap[r][c].push_back(d);
        }
    }
}
int solve(int S, vector<fish>& fishes, pair<int, int>& shark) {
    vector<vector<int>> smell(5, vector<int>(5, 0));

    while(S--) {
        vector<fish> copyFishes(fishes);

        vector<vector<vector<int>>> fishMap(5, vector<vector<int>>(5, vector<int>()));
        moveFishes(fishMap, fishes, smell, shark);

        moveShark(shark, fishMap, smell);

        updateState(smell);

        copyFish(fishMap, fishes, copyFishes);
    }

    return (int)fishes.size();
}
void input(int& M, int& S, vector<fish>& fishes, pair<int ,int>& shark) {
    cin >> M >> S;
    fishes.assign(M, {0, 0, 0});
    for(int i = 0; i < M; ++i) {
        cin >> fishes[i].r >> fishes[i].c >> fishes[i].d;
    }
    cin >> shark.first >> shark.second;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int M, S;
    vector<fish> fishes;
    pair<int, int> shark;
    input(M, S, fishes, shark);

    int answer = solve(S, fishes, shark);

    cout << answer;
    return 0;
}
