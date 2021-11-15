#include <iostream>
#include <vector>
#include <deque>
using namespace std;
const int W = 0;
const int R = 1;
const int B = 2;

struct horse_info{
    int r;
    int c;
    deque<pair<int, int>> horse_list;
};


bool isFinish(const vector<horse_info>& h){
    for(int i=1; i<h.size(); i++)
        if(h[i].horse_list.size() >= 4)
            return true;
    return false;
}
void test(const vector<horse_info>& h){
    for(int i=1; i<h.size(); i++){
        if(h[i].horse_list.empty())
            continue;
        cout << h[i].r << ' ' << h[i].c << '\n';
        for(auto it = h[i].horse_list.begin(); it != h[i].horse_list.end(); it++)
            cout << it->first << ' ';
        cout << '\n';
    }
}
int main(){
    // input.
    int N, K;
    cin >> N >> K;
    // 체스판 만들기.
    vector<vector<int>> board(N+2, vector<int>(N+2, 0));
    for(int i=0; i<=N+1; i++){
        // 체스판 범위 벗어나면 파란색으로 인식하기.
        if(i == 0 || i == N+1){
            for(int j=0; j<=N+1; j++)
                board[i][j] = B;
        }
        else{
            board[i][0] = B;
            board[i][N+1] = B;
            for(int j=1; j<=N; j++){
                int info;
                cin >> info;
                board[i][j] = info;
            }
        }
    }
    // 말 정보 저장.
    vector<horse_info> horse(K+1);
    vector<vector<int>> visit(N+1, vector<int>(N+1, 0)); // 체스판의 말 정보.
    int idx = 1;
    while(idx <= K){
        int r, c, d;
        cin >> r >> c >> d;
        horse[idx].r = r;
        horse[idx].c = c;
        horse[idx].horse_list.push_back(make_pair(idx, d));
        visit[r][c] = idx;
        ++idx;
    }

    // 게임 시작.
    int dr[5] = {-1, 0, 0, -1, 1};
    int dc[5] = {-1, 1, -1, 0, 0};
    int turn = 1;
    while(true) {
        for (int i = 1; i <= K; i++) {
            // 해당 말이 다른 말 위에 존재할 경우.
            if(horse[i].horse_list.empty())
                continue;

            int cur_r = horse[i].r;
            int cur_c = horse[i].c;
            int d = horse[i].horse_list.front().second;

            int next_r = cur_r + dr[d];
            int next_c = cur_c + dc[d];

            if(board[next_r][next_c] == B){
                if(d == 1) d = 2;
                else if(d == 2) d = 1;
                else if (d == 3) d = 4;
                else if (d == 4) d = 3;

                horse[i].horse_list.front().second = d;
                next_r = cur_r + dr[d];
                next_c = cur_c + dc[d];
            }

            if(board[next_r][next_c] == W){
                if(visit[next_r][next_c] == 0){
                    horse[i].r = next_r;
                    horse[i].c = next_c;

                    visit[next_r][next_c] = i;
                    visit[cur_r][cur_c] = 0;
                }
                else{
                    int h = visit[next_r][next_c];
                    while(!horse[i].horse_list.empty()){
                        horse[h].horse_list.push_back(make_pair(horse[i].horse_list.front().first, horse[i].horse_list.front().second));
                        horse[i].horse_list.pop_front();
                    }
                    visit[cur_r][cur_c] = 0;
                }
            }
            else if(board[next_r][next_c] == R){
                if(visit[next_r][next_c] == 0){
                    int h = horse[i].horse_list.back().first;
                    horse[h].r = next_r;
                    horse[h].c = next_c;
                    if(h != i) {
                        while (!horse[i].horse_list.empty()) {
                            horse[h].horse_list.push_back(
                                    make_pair(horse[i].horse_list.back().first, horse[i].horse_list.back().second));
                            horse[i].horse_list.pop_back();
                        }
                    }
                    visit[cur_r][cur_c] = 0;
                    visit[next_r][next_c] = h;
                }
                else{
                    int h = visit[next_r][next_c];
                    while(!horse[i].horse_list.empty()){
                        horse[h].horse_list.push_back(make_pair(horse[i].horse_list.back().first, horse[i].horse_list.back().second));
                        horse[i].horse_list.pop_back();
                    }
                    visit[cur_r][cur_c] = 0;
                }
            }
        }
        if(isFinish(horse))
            break;
        ++turn;
        if(turn > 1000){
            turn = -1;
            break;
        }
    }

    // 정답 출력.
    cout << turn;

    return 0;
}
