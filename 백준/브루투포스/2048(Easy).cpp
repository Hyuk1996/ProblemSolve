#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int DOWN = 0;
const int UP = 1;
const int RIGHT = 2;
const int LEFT = 3;

int getMaxVal(const vector<vector<int>>& board) {
    int maxVal = -1;
    for(int i=0; i<board.size(); ++i) {
        for(int j=0; j<board.size(); ++j) {
            maxVal = max(maxVal, board[i][j]);
        }
    }
    return maxVal;
}
void move(vector<vector<int>>& board, int dir) {
    if(dir == DOWN) {
        for(int x=0; x<board.size(); ++x) {
            vector<bool> alreadyMerge(board.size(), 0);
            for(int y=board.size()-2; y>=0; --y) {
                if(board[y][x] == 0)
                    continue;

                while(y < board.size()-1) {
                    if(board[y+1][x] == 0) {
                        swap(board[y+1][x], board[y][x]);
                        ++y;
                        continue;
                    }

                    if(board[y+1][x] != board[y][x])
                        break;
                    if(board[y+1][x] == board[y][x]) {
                        if(alreadyMerge[y+1])
                            break;
                        alreadyMerge[y+1] = true;
                        board[y+1][x] *= 2;
                        board[y][x] = 0;
                        break;
                    }
                }
            }
        }
    } else if(dir == UP) {
        for(int x=0; x<board.size(); ++x) {
            vector<bool> alreadyMerge(board.size(), 0);
            for(int y=1; y<board.size(); ++y) {
                if(board[y][x] == 0)
                    continue;

                while(y > 0) {
                    if(board[y-1][x] == 0) {
                        swap(board[y-1][x], board[y][x]);
                        --y;
                        continue;
                    }

                    if(board[y-1][x] != board[y][x])
                        break;
                    if(board[y-1][x] == board[y][x]){
                        if(alreadyMerge[y-1])
                            break;
                        alreadyMerge[y-1] = true;
                        board[y-1][x] *= 2;
                        board[y][x] = 0;
                        break;
                    }
                }
            }
        }
    } else if(dir == RIGHT) {
        for(int y=0; y<board.size(); ++y) {
            vector<bool> alreadyMerge(board.size(), 0);
            for(int x=board.size()-2; x>=0; --x) {
                if(board[y][x] == 0)
                    continue;

                while(x < board.size()-1) {
                    if(board[y][x+1] == 0) {
                        swap(board[y][x+1], board[y][x]);
                        ++x;
                        continue;
                    }

                    if(board[y][x+1] != board[y][x])
                        break;
                    if(board[y][x+1] == board[y][x]) {
                        if(alreadyMerge[x+1])
                            break;
                        alreadyMerge[x+1] = true;
                        board[y][x+1] *= 2;
                        board[y][x] = 0;
                        break;
                    }
                }
            }
        }
    } else if(dir == LEFT) {
        for(int y=0; y<board.size(); ++y) {
            vector<bool> alreadyMerge(board.size(), 0);
            for(int x=1; x<board.size(); ++x) {
                if(board[y][x] == 0)
                    continue;

                while(x > 0) {
                    if(board[y][x-1] == 0) {
                        swap(board[y][x-1], board[y][x]);
                        --x;
                        continue;
                    }

                    if(board[y][x-1] != board[y][x])
                        break;
                    if(board[y][x-1] == board[y][x]) {
                        if(alreadyMerge[x-1])
                            break;
                        alreadyMerge[x-1] = true;
                        board[y][x-1] *= 2;
                        board[y][x] = 0;
                        break;
                    }
                }
            }
        }
    }
}
void dfs(vector<vector<int>> board, int depth, int& maxVal) {
    // 5번 이동완료.
    if(depth == 5) {
        maxVal = max(maxVal, getMaxVal(board));
        return;
    }

    for(int i=0; i<4; ++i) {
        vector<vector<int>> newBoard(board.size(), vector<int>(board.size()));
        copy(board.begin(), board.end(), newBoard.begin());
        move(newBoard, i);
        dfs(newBoard, depth + 1, maxVal);
    }
}
int main() {
    // 입력.
    int N;
    cin >> N;
    vector<vector<int>> board(N, vector<int>(N));
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            int val;
            cin >> val;
            board[i][j] = val;
        }
    }


    // dfs 이용해 최대 5번 이동해서 만들 수 있는 가장 큰 블록의 값을 구하기.
    int maxVal = -1;
    dfs(board, 0, maxVal);

    // 정답 출력.
    cout << maxVal;
    return 0;
}
