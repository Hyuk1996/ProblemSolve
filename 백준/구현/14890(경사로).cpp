#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
const int ROW = 0;
const int COLUMN = 1;

bool isReachablePath(const vector<vector<int>>& map, int start, int L, int type) {
    vector<bool> isRampExist(map.size(), false);
    bool isPossible = true;
    if(type == ROW) {
        int curC = 0;

        while(curC < map.size()-1 && isPossible) {
            int nextC = curC + 1;

            if(abs(map[start][curC] - map[start][nextC]) > 1) {
                isPossible = false;
                break;
            }

            if(map[start][curC] < map[start][nextC]) {
                int tempHeight = map[start][curC];
                int tmpC = curC;
                for(int i=0; i<L; ++i) {
                    if(tmpC < 0 || map[start][tmpC] != tempHeight || isRampExist[tmpC]) {
                        isPossible = false;
                        break;
                    }

                    isRampExist[tmpC] = true;
                    --tmpC;
                }
            } else if(map[start][curC] > map[start][nextC]) {
                int tempHeight = map[start][nextC];
                int tmpC = nextC;
                for(int i=0; i<L; ++i) {
                    if(tmpC >= map.size() || map[start][tmpC] != tempHeight || isRampExist[tmpC]) {
                        isPossible = false;
                        break;
                    }

                    isRampExist[tmpC] = true;
                    ++tmpC;
                }
            }
            ++curC;
        }
    } else {
        int curR = 0;

        while(curR < map.size()-1 && isPossible) {
            int nextR = curR + 1;

            if(abs(map[curR][start] - map[nextR][start]) > 1) {
                isPossible = false;
                break;
            }

            if(map[curR][start] < map[nextR][start]) {
                int tempHeight = map[curR][start];
                int tmpR = curR;
                for(int i=0; i<L; ++i) {
                    if(tmpR < 0 || map[tmpR][start] != tempHeight || isRampExist[tmpR]) {
                        isPossible = false;
                        break;
                    }

                    isRampExist[tmpR] = true;
                    --tmpR;
                }
            } else if(map[curR][start] > map[nextR][start]){
                int tempHeight = map[nextR][start];
                int tmpR = nextR;
                for(int i=0; i<L; ++i) {
                    if(tmpR >= map.size() || map[tmpR][start] != tempHeight || isRampExist[tmpR]) {
                        isPossible = false;
                        break;
                    }

                    isRampExist[tmpR] = true;
                    ++tmpR;
                }
            }
            ++curR;
        }
    }

    if(isPossible) {
        return true;
    } else {
        return false;
    }
}
int findReachablePath(const vector<vector<int>>& map, const int L) {
    int reachablePath = 0;
    for(int i=0; i<map.size(); ++i) {
        if(isReachablePath(map, i, L, ROW)) {
            ++reachablePath;
        }
        if(isReachablePath(map, i, L, COLUMN)) {
            ++reachablePath;
        }
    }
    return reachablePath;
}
int main() {
    // 입력.
    int N, L;
    cin >> N >> L;
    vector<vector<int>> map(N, vector<int>(N));
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            int height;
            cin >> height;
            map[i][j] = height;
        }
    }

    int answer = findReachablePath(map, L);
    cout << answer;
    return 0;
}
