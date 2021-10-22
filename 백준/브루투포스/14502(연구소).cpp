#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int bfs(vector<vector<int>>& lab, vector<vector<bool>>& visit, int r, int c){
    int dr[4] = {0, 0, -1, 1};
    int dc[4] = {-1, 1, 0, 0};

    int cnt = 1;
    visit[r][c] = true;
    queue<pair<int, int>> q;
    q.push(make_pair(r, c));
    while(!q.empty()){
        int cur_r = q.front().first;
        int cur_c = q.front().second;
        q.pop();

        for(int i=0; i<4; i++){
            int next_r = cur_r + dr[i];
            int next_c = cur_c + dc[i];
            if((0 <= next_r && next_r < lab.size()) && (0 <= next_c && next_c < lab[0].size())){
                if(!visit[next_r][next_c] && lab[next_r][next_c] != 1){
                    visit[next_r][next_c] = true;
                    cnt++;
                    q.push(make_pair(next_r, next_c));
                }
            }
        }
    }
    return cnt;
}
int getSafeArea(vector<vector<int>>& lab){
    vector<vector<bool>> visit(lab.size(), vector<bool>(lab[0].size(), 0));
    int safe_area = lab.size() * lab[0].size();
    for(int i=0; i<lab.size(); i++){
        for(int j=0; j<lab[i].size(); j++){
            if(lab[i][j] == 2 && !visit[i][j]){
                safe_area -= bfs(lab, visit, i, j);
            }
            else if(lab[i][j] == 1)
                safe_area--;
        }
    }
    return safe_area;
}
void getCombi(vector<vector<int>>& lab, int r, int c, int depth, int& answer){
    if(depth == 3){
        // 해당 조합일 경우의 안전 구역 넓이 구하기.
        int safe_area = getSafeArea(lab);
        answer = max(safe_area, answer);
        return;
    }
    // 세울 수 있는 벽의 모든 조합 구하기.
    if(c == lab[r].size()){
        c = 0;
        r++;
    }
    for(int i=r; i<lab.size(); i++){
        int start;
        if(i == r)
            start = c;
        else
            start = 0;
        for (int j = start; j < lab[i].size(); j++) {
            if (lab[i][j] == 0) {
                lab[i][j] = 1;
                getCombi(lab, i, j + 1, depth + 1, answer);
                lab[i][j] = 0;
            }
        }
    }

}
int main(){
    // 입력.
    int N, M;
    cin >> N >> M;
    vector<vector<int>> lab(N, vector<int>(M, 0));
    for(int i=0; i<N; i++)
        for(int j=0; j<M; j++){
            int tmp;
            cin >> tmp;
            lab[i][j] = tmp;
        }

    // 완전 탬색 이용해서 가능한 벽 조합에 대한 안전구역 넓이 중 최대값 구하기.
    int answer = 0;
    getCombi(lab, 0, 0, 0, answer);
    cout << answer;
}
