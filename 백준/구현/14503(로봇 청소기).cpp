#include <iostream>
#include <vector>
using namespace std;
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};
const int VISIT = 2;
/*
void test(const vector<vector<int>>& m, int d){
    for(int i=0; i<m.size(); i++){
        for(int j=0; j<m[i].size(); j++)
            cout << m[i][j] << ' ';
        cout << '\n';
    }
    cout << d << "\n\n";
}
 */
void travel(vector<vector<int>>& m, int r, int c, int d, int& ans, int search_cnt){
    //  step 1 (if possible)
    if(m[r][c] == 0) {
        m[r][c] = VISIT;
        ++ans;

        // test(m, d);
    }

    // step 2
    if(search_cnt == 4){ // 4방향이 모두 청소가 되어있거나, 벽인 경우.
        int reverse_d = (d + 2) % 4;
        int next_r = r + dr[reverse_d];
        int next_c = c + dc[reverse_d];
        if(m[next_r][next_c] != 1){ // 후진
            travel(m, next_r, next_c, d, ans, 0);
        }
        else
            return;
    }
    else{
        int next_d;
        if(d == 0)
            next_d = 3;
        else
            next_d = d - 1;

        int next_r = r + dr[next_d];
        int next_c = c + dc[next_d];
        if(m[next_r][next_c] == 0)
            travel(m, next_r, next_c, next_d, ans, 0);
        else
            travel(m, r, c, next_d, ans, search_cnt + 1);
    }
}
int main(){
    // 입력.
    int N, M;
    cin >> N >> M;
    int start_r, start_c, dir;
    cin >> start_r >> start_c >> dir;

    vector<vector<int>> m(N, vector<int>(M, 0));
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            int info;
            cin >> info;
            m[i][j] = info;
        }
    }

    // 로봇 청소기 탐색시작.
    int ans = 0;
    travel(m, start_r, start_c, dir, ans, 0);

    // 출력
    cout << ans;


    return 0;
}
