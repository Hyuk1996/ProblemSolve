#include <iostream>
#include <vector>
using namespace std;

int blueGame(vector<vector<bool>>& blue, int t, int x) {
    int score = 0;
    int nextY = 0;

    //block 쌓기
    if(t == 1) {
        while(true) {
            if(nextY > 5 || blue[x][nextY]) {
                blue[x][nextY - 1] = true;
                break;
            }
            nextY++;
        }
    } else if(t ==2) {
        while(true) {
            if(nextY > 5 || blue[x][nextY]) {
                blue[x][nextY - 1] = true;
                blue[x][nextY - 2] = true;
                break;
            }
            nextY++;
        }
    } else {
        while(true) {
            if(nextY > 5 || (blue[x][nextY] || blue[x+1][nextY])) {
                blue[x][nextY - 1] = true;
                blue[x + 1][nextY - 1] = true;
                break;
            }
            nextY++;
        }
    }

    // 꽉찬 열 확인
    int blockCnt;
    int fullIdx = -1;
    while(true) {
        for (int c = 5; c >= 0; --c) {
            blockCnt = 0;
            for (int r = 0; r < 4; ++r) {
                if(blue[r][c]) {
                    blockCnt++;
                }
            }
            if(blockCnt == 4) {
                fullIdx = c;
                break;
            }
        }

        if(blockCnt != 4) {
            break;
        }

        score++;
        for(int r=0; r<4; ++r) {
            for(int c=fullIdx; c>=1; --c) {
                blue[r][c] = blue[r][c-1];
            }
            blue[r][0] = false;
        }
    }

    //특수 열 확인
    int cnt = 0;
    for(int c=0; c<2; ++c) {
        for(int r=0; r<4; ++r) {
            if(blue[r][c]) {
                cnt++;
                break;
            }
        }
    }
    for(int r = 0; r < 4; ++r) {
        for(int c = 5; c >= cnt; --c) {
            blue[r][c] = blue[r][c - cnt];
        }
        for(int c = 0; c < cnt; ++c) {
            blue[r][c] = false;
        }
    }
    return score;
}
int greenGame(vector<vector<bool>>& green, int t, int y) {
    int score = 0;
    int nextX = 0;

    //block 쌓기
    if(t == 1) {
        while(true) {
            if(nextX > 5 || green[nextX][y]) {
                green[nextX - 1][y] = true;
                break;
            }
            nextX++;
        }
    } else if(t ==2) {
        while(true) {
            if(nextX > 5 || (green[nextX][y] || green[nextX][y + 1])) {
                green[nextX - 1][y] = true;
                green[nextX - 1][y + 1] = true;
                break;
            }
            nextX++;
        }
    } else {
        while(true) {
            if(nextX > 5 || green[nextX][y]) {
                green[nextX - 1][y] = true;
                green[nextX - 2][y] = true;
                break;
            }
            nextX++;
        }
    }

    // 꽉찬 행 확인
    int blockCnt;
    int fullIdx = -1;
    while(true) {
        for (int r = 5; r >= 0; --r) {
            blockCnt = 0;
            for (int c = 0; c < 4; ++c) {
                if(green[r][c]) {
                    blockCnt++;
                }
            }
            if(blockCnt == 4) {
                fullIdx = r;
                break;
            }
        }

        if(blockCnt != 4) {
            break;
        }

        score++;
        for(int c=0; c<4; ++c) {
            for(int r=fullIdx; r>=1; --r) {
                green[r][c] = green[r-1][c];
            }
            green[0][c] = false;
        }
    }

    //특수 행 확인
    int cnt = 0;
    for(int r=0; r<2; ++r) {
        for(int c=0; c<4; ++c) {
            if(green[r][c]) {
                cnt++;
                break;
            }
        }
    }
    for(int c = 0; c < 4; ++c) {
        for(int r = 5; r >= cnt; --r) {
            green[r][c] = green[r - cnt][c];
        }
        for(int r=0; r<cnt; ++r) {
            green[r][c] = false;
        }
    }
    return score;
}
pair<int, int> solve(int N, vector<vector<bool>>& green, vector<vector<bool>>& blue) {
    int t, x, y;
    int score = 0;
    int blockCnt = 0;
    while(N--) {
        cin >> t >> x >> y;

        score += greenGame(green, t, y);
        score += blueGame(blue, t, x);
    }

    for(int r = 0; r < 6; ++r) {
        for(int c = 0; c < 4; ++c) {
            if(green[r][c]) {
                blockCnt++;
            }
        }
    }
    for(int r = 0; r < 4; ++r) {
        for(int c = 0; c < 6; ++c) {
            if(blue[r][c]) {
                blockCnt++;
            }
        }
    }
    return make_pair(score, blockCnt);
}
void input(int& N, vector<vector<bool>>& green, vector<vector<bool>>& blue) {
    cin >> N;
    green.assign(6, vector<bool>(4, false));
    blue.assign(4, vector<bool>(6, false));
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    vector<vector<bool>> green;
    vector<vector<bool>> blue;
    input(N, green, blue);

    pair<int, int> answer = solve(N, green, blue);

    cout << answer.first << '\n';
    cout << answer.second << '\n';
    return 0;
}
