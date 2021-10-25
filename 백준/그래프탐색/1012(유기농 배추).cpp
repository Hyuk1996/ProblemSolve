#include <iostream>
#include <vector>
using namespace std;
int dr[4] = {0, 0, -1, 1};
int dc[4] = {-1, 1, 0, 0};

void DFS(vector<vector<bool>>& ground, int r, int c){
    ground[r][c] = false;

    for(int i=0; i<4; i++){
        int next_r = r + dr[i];
        int next_c = c + dc[i];
        if((0<=next_r && next_r < ground.size()) && (0<=next_c && next_c < ground[r].size())){
            if(ground[next_r][next_c])
                DFS(ground, next_r, next_c);
        }
    }
}
int main(){
    // 입력.
    int T;
    cin >> T;
    vector<int> answers;
    while(T--){
        int M, N, K;
        cin >> M >> N >> K;
        vector<vector<bool>> ground(N, vector<bool>(M, 0));
        while(K--){
            int X, Y;
            cin >> X >> Y;
            ground[Y][X] = true;
        }

        // 완탐 시작.
        int ans = 0;
        for(int i=0; i<ground.size(); i++) {
            for (int j = 0; j < ground[i].size(); j++) {
                if (ground[i][j]) {
                    DFS(ground, i, j);
                    ans++;
                }
            }
        }

        answers.push_back(ans);
    }

    // 출력.
    for(int i=0; i<answers.size(); i++)
        cout << answers[i] << '\n';
    return 0;
}

// BFS 이용.
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int dr[4] = {0, 0, -1, 1};
int dc[4] = {-1, 1, 0, 0};

void BFS(vector<vector<bool>>& ground, int r, int c){
    ground[r][c] = false;
    queue<pair<int, int>> q;
    q.push(make_pair(r, c));

    while(!q.empty()){
        int cur_r = q.front().first;
        int cur_c = q.front().second;
        q.pop();

        for(int i=0; i<4; i++){
            int next_r = cur_r + dr[i];
            int next_c = cur_c + dc[i];
            if((0 <= next_r && next_r < ground.size())&&(0 <= next_c && next_c < ground[cur_r].size())){
                if(ground[next_r][next_c]){
                    ground[next_r][next_c] = false;
                    q.push(make_pair(next_r, next_c));
                }
            }
        }
    }
}
int main(){
    // 입력.
    int T;
    cin >> T;
    vector<int> answers;
    while(T--){
        int M, N, K;
        cin >> M >> N >> K;
        vector<vector<bool>> ground(N, vector<bool>(M, 0));
        while(K--){
            int X, Y;
            cin >> X >> Y;
            ground[Y][X] = true;
        }

        // 완탐 시작.
        int ans = 0;
        for(int i=0; i<ground.size(); i++) {
            for (int j = 0; j < ground[i].size(); j++) {
                if (ground[i][j]) {
                    BFS(ground, i, j);
                    ans++;
                }
            }
        }

        answers.push_back(ans);
    }

    // 출력.
    for(int i=0; i<answers.size(); i++)
        cout << answers[i] << '\n';
    return 0;
}
