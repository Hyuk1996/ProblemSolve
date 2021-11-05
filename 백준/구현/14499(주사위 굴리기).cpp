#include <iostream>
#include <vector>
#include <deque>
using namespace std;

void test(const deque<int>& r, const deque<int>& c, const int top){
    cout << "\nr:\n";
    for(auto it = r.begin(); it != r.end(); it++)
        cout << *it << ' ';
    cout << "\nc:\n";
    for(auto it = c.begin(); it != c.end(); it++)
        cout << *it << ' ';
    cout << "\ntop: " << top << '\n';
}
void changeCenter(deque<int>& dice, int new_center){
    for(int i=0; i<3; i++){
        if(i == 1){
            dice.pop_front();
            dice.push_back(new_center);
        }
        else {
            int tmp = dice.front();
            dice.pop_front();
            dice.push_back(tmp);
        }
    }
}
int main() {
    // 입력.
    int N, M, x, y, K;
    cin >> N >> M >> x >> y >> K;
    vector<vector<int>> m(N, vector<int>(M, 0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            int num;
            cin >> num;
            m[i][j] = num;
        }

    // 시뮬레이션.
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {1, -1, 0, 0};
    deque<int> dice_row;
    deque<int> dice_column;
    int dice_top = 0;
    for(int i=0; i<3; i++){
        dice_row.push_back(0);
        dice_column.push_back(0);
    }

    vector<int> answers;
    int cur_x = x;
    int cur_y = y;
    while(K--){
        int cmd;
        cin >> cmd;
        --cmd;

        int next_x = cur_x + dx[cmd];
        int next_y = cur_y + dy[cmd];
        if((0 <= next_x && next_x < N) && (0 <= next_y && next_y < M)){
            if(cmd == 0){ // 동쪽
                if(m[next_x][next_y] != 0) {
                    dice_row.front() = m[next_x][next_y];
                    m[next_x][next_y] = 0;
                }
                else
                    m[next_x][next_y] = dice_row.front();
                changeCenter(dice_column, dice_row.front());

                dice_row.push_front(dice_top);
                dice_top = dice_row.back();
                dice_row.pop_back();
            }
            else if(cmd == 1){
                if(m[next_x][next_y] != 0){
                    dice_row.back() = m[next_x][next_y];
                    m[next_x][next_y] = 0;
                }
                else
                    m[next_x][next_y] = dice_row.back();
                changeCenter(dice_column, dice_row.back());

                dice_row.push_back(dice_top);
                dice_top = dice_row.front();
                dice_row.pop_front();
            }
            else if(cmd == 2){
                if(m[next_x][next_y] != 0){
                    dice_column.front() = m[next_x][next_y];
                    m[next_x][next_y] = 0;
                }
                else
                    m[next_x][next_y] = dice_column.front();
                changeCenter(dice_row, dice_column.front());

                dice_column.push_front(dice_top);
                dice_top = dice_column.back();
                dice_column.pop_back();
            }
            else{
                if(m[next_x][next_y] != 0){
                    dice_column.back() = m[next_x][next_y];
                    m[next_x][next_y] = 0;
                }
                else
                    m[next_x][next_y] = dice_column.back();
                changeCenter(dice_row, dice_column.back());

                dice_column.push_back(dice_top);
                dice_top = dice_column.front();
                dice_column.pop_front();
            }
            answers.push_back(dice_top);
            cur_x = next_x;
            cur_y = next_y;
            // test(dice_row, dice_column, dice_top);
        }
    }

    // 출력.
    for(int i=0; i<answers.size(); i++)
        cout << answers[i] << '\n';
    return 0;
}
