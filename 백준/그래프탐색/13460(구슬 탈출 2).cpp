#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

int main() {
    // 입력.
    int N, M;
    cin >> N >> M;

    int redR, redC, blueR, blueC;
    vector<string> board(N);
    for(int i=0; i<N; ++i) {
        string boardInfo;
        cin >> boardInfo;
        for(int j=0; j<boardInfo.size(); ++j) {
            if(boardInfo[j] == 'R') {
                redR = i;
                redC = j;
                boardInfo[j] = '.';
            }
            else if(boardInfo[j] == 'B') {
                blueR = i;
                blueC = j;
                boardInfo[j] = '.';
            }
        }
        board[i] = boardInfo;
    }

    // 완전탐색 이용해 최소 몇 번 만에 빨간 구슬을 구멍을 통해 빼낼 수 있는지 구하기.
    int dr[4] = {0, 0, -1, 1};
    int dc[4] = {-1, 1, 0, 0};

    queue<pair<int, int>> redQ;
    queue<pair<int, int>> blueQ;
    redQ.push(make_pair(redR, redC));
    blueQ.push(make_pair(blueR, blueC));

    int ans = 1;
    bool redFinish, blueFinish;
    bool gameFinish = false;

    while(ans <= 10) {
        int qSize = redQ.size();

        for(int i=0; i<qSize; ++i) {
            redR = redQ.front().first;
            redC = redQ.front().second;
            blueR = blueQ.front().first;
            blueC = blueQ.front().second;
            redQ.pop();
            blueQ.pop();

            for (int j = 0; j < 4; ++j) {
                int curRedR = redR;
                int curRedC = redC;
                int curBlueR = blueR;
                int curBlueC = blueC;
                redFinish = false;
                blueFinish = false;

                while(!redFinish || !blueFinish) {
                    if(!redFinish) {
                        curRedR += dr[j];
                        curRedC += dc[j];
                    }
                    if(!blueFinish) {
                        curBlueR += dr[j];
                        curBlueC += dc[j];
                    }

                    // 벽에 막하기나, 구멍에 도달하는 경우.
                    if(!redFinish) {
                        if (board[curRedR][curRedC] == '#') {
                            redFinish = true;
                            curRedR -= dr[j];
                            curRedC -= dc[j];
                        }
                        else if(board[curRedR][curRedC] == 'O') {
                            redFinish = true;
                            curRedR = -1;
                            curRedC = -1;
                        }
                    }

                    if(!blueFinish) {
                        if (board[curBlueR][curBlueC] == '#') {
                            blueFinish = true;
                            curBlueR -= dr[j];
                            curBlueC -= dc[j];
                        }
                        else if (board[curBlueR][curBlueC] == 'O') {
                            blueFinish = true;
                            curBlueR = -1;
                            curBlueC = -1;
                        }
                    }

                    // 빨간 구슬과 파란 구슬이 부딪히는 경우.
                    if(!blueFinish || !redFinish) {
                        if (curRedR == curBlueR && curRedC == curBlueC) {
                            if (blueFinish) {
                                redFinish = true;
                                curRedR -= dr[j];
                                curRedC -= dc[j];
                            } else {
                                blueFinish = true;
                                curBlueR -= dr[j];
                                curBlueC -= dc[j];
                            }
                        }
                    }
                }

                if(curRedR == -1 && curRedC == -1 && curBlueR != -1 && curBlueC != -1) {
                    gameFinish = true;
                    break;
                }
                else if(curRedR != -1 && curRedC != -1 && curBlueR != -1 && curBlueC != -1){
                    redQ.push(make_pair(curRedR, curRedC));
                    blueQ.push(make_pair(curBlueR, curBlueC));
                }
            }
            if(gameFinish)
                break;
        }
        if(gameFinish)
            break;
        ++ans;
    }

    // 정답 출력.
    if(gameFinish)
        cout << ans;
    else
        cout << -1;
    return 0;
}
