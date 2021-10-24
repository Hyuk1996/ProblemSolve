#include <iostream>
#include <deque>
#include <vector>
using namespace std;

int main(){
    // 입력.
    int N, K;
    cin >> N >> K;

    vector<vector<bool>> board(N+1, vector<bool>(N+1, 0));
    for(int i=0; i<K; i++){
        int r, c;
        cin >> r >> c;
        board[r][c] = true;
    }
    int L;
    cin >> L;
    vector<pair<int, char>> move;
    for(int i=0; i<L; i++){
        int x;
        char C;
        cin >> x >> C;
        move.push_back(make_pair(x, C));
    }

    // 게임 시작.
    int cur_time = 0;
    int cur_dr = 0;
    int cur_dc = 1;
    int idx = 0;
    vector<vector<bool>> visit(N+1, vector<bool>(N+1, 0));
    deque<pair<int, int>> snake;
    snake.push_back(make_pair(1, 1));
    visit[1][1] = true;
    while(true){
        // 방향을 바꿔야 하면 바꾸기.
        if(cur_time == move[idx].first){
            char dir = move[idx].second;
            idx++;
            if(dir == 'D'){
                if(cur_dr == 0 && cur_dc == 1){
                    cur_dr = 1;
                    cur_dc = 0;
                }
                else if(cur_dr == 1 && cur_dc == 0){
                    cur_dr = 0;
                    cur_dc = -1;
                }
                else if(cur_dr == 0 && cur_dc == -1){
                    cur_dr = -1;
                    cur_dc = 0;
                }
                else{
                    cur_dr = 0;
                    cur_dc = 1;
                }
            }
            else{
                if(cur_dr == 0 && cur_dc == 1){
                    cur_dr = -1;
                    cur_dc = 0;
                }
                else if(cur_dr == -1 && cur_dc == 0){
                    cur_dr = 0;
                    cur_dc = -1;
                }
                else if(cur_dr == 0 && cur_dc == -1){
                    cur_dr = 1;
                    cur_dc = 0;
                }
                else{
                    cur_dr = 0;
                    cur_dc = 1;
                }
            }
        }
        cur_time++;

        // 뱀 움직이기.
        int next_r = snake.front().first + cur_dr;
        int next_c = snake.front().second + cur_dc;
        if((1 <= next_r && next_r <= N) && (1 <= next_c && next_c <= N)){
            if(!visit[next_r][next_c]){ // 움직일 수 있는 경우.
                visit[next_r][next_c] = true;
                snake.push_front(make_pair(next_r, next_c));

                if(board[next_r][next_c] == 0){ // 사과 있는 없는 경우.
                    // 꼬리 줄어들기.
                    visit[snake.back().first][snake.back().second] = false;
                    snake.pop_back();
                }
                else // 사과 있는 경우.
                    board[next_r][next_c] = 0;

            }
            else // 머리가 몸에 부딪히는 경우.
                break;
        }
        else // 뱀의 머리가 벽에 부딪히는 경우.
            break;
    }

    cout << cur_time;
    return 0;
}
