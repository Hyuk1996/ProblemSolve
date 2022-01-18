#include <iostream>
#include <stack>
#include <vector>
#include <deque>
using namespace std;
const int MAX = 1000;
const int dr[5] = {0, 0, 0, -1, 1};
const int dc[5] = {0, 1, -1, 0, 0};
struct horse {
    int r, c, d;
    horse(int r, int c, int d) {
        this->r = r;
        this->c = c;
        this->d = d;
    }
};

int solve(int N, int K, vector<vector<int>>& board, vector<horse>& horses, vector<vector<stack<int>>>& horseInfo) {
    int turn = 1;
    bool isFinish = false;

    while(turn <= MAX) {
        for(int i=1; i<=K; ++i) {
            int r = horses[i].r;
            int c = horses[i].c;
            int d = horses[i].d;

            int nextR = r + dr[d];
            int nextC = c + dc[d];

            //처음 이동하려는 칸이 파락색이거나, 체스판을 벗아나는 경우
            if((nextR < 1 || nextR > N || nextC < 1 || nextC > N) || board[nextR][nextC] == 2) {
                if(d == 1) {
                    d = 2;
                } else if(d == 2) {
                    d = 1;
                } else if(d == 3) {
                    d = 4;
                } else {
                    d = 3;
                }
                horses[i].d = d;
                nextR = r + dr[d];
                nextC = c + dc[d];
            }

            //파란칸 or 체스판을 벗어나는 경우
            if((nextR < 1 || nextR > N || nextC < 1 || nextC > N) || board[nextR][nextC] == 2) {
                continue;
            }

            deque<int> curHorses;
            while(true) {
                if(horseInfo[r][c].top() == i) {
                    curHorses.push_back(horseInfo[r][c].top());
                    horseInfo[r][c].pop();
                    break;
                }
                curHorses.push_back(horseInfo[r][c].top());
                horseInfo[r][c].pop();
            }
            // 흰칸
            if(board[nextR][nextC] == 0) {
                while(!curHorses.empty()) {
                    int h = curHorses.back();
                    horses[h].r = nextR;
                    horses[h].c = nextC;
                    horseInfo[nextR][nextC].push(h);
                    curHorses.pop_back();
                }
            } else if(board[nextR][nextC] == 1) { //빨간칸
                while(!curHorses.empty()) {
                    int h = curHorses.front();
                    horses[h].r = nextR;
                    horses[h].c = nextC;
                    horseInfo[nextR][nextC].push(h);
                    curHorses.pop_front();
                }
            }
            if(horseInfo[nextR][nextC].size() >= 4) { //게임 종료 조건
                isFinish = true;
                break;
            }
        }

        if(isFinish) {
            break;
        }
        turn++;
    }

    if(turn > MAX) {
        return -1;
    } else {
        return turn;
    }
}
void input(int& N, int& K, vector<vector<int>>& board, vector<horse>& horses, vector<vector<stack<int>>>& horseInfo) {
    cin >> N >> K;
    board.assign(N+1, vector<int>(N+1, 0));
    horseInfo.assign(N+1, vector<stack<int>>(N+1, stack<int>()));
    for(int i=1; i<=N; ++i) {
        for(int j=1; j<=N; ++j) {
            cin >> board[i][j];
        }
    }
    int r, c, d;
    horses.push_back(horse(0, 0, 0));
    for(int i=1; i<=K; ++i) {
        cin >> r >> c >> d;
        horses.push_back(horse(r, c, d));
        horseInfo[r][c].push(i);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, K;
    vector<vector<int>> board;
    vector<vector<stack<int>>> horseInfo; // board에 말이 쌓여있는 정보.
    vector<horse> horses;
    input(N, K, board, horses, horseInfo);

    int answer = solve(N, K, board, horses, horseInfo);

    cout << answer;
    return 0;
}
