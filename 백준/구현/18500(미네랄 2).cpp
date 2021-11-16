#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
const int LEFT_TO_RIGHT = 1;
int dr[4] = {0, 0, -1, 1};
int dc[4] = {-1, 1, 0, 0};

int searchMineral(const vector<vector<char>>& cave, int h, int d){
    if(d == LEFT_TO_RIGHT){
        for(int i=0; i<cave[h].size(); i++){
            if(cave[h][i] == 'x')
                return i;
        }
    }
    else{
        for(int i = cave[h].size() - 1; i >= 0; i--){
            if(cave[h][i] == 'x')
                return i;
        }
    }
    return -1;
}
void DFS(const vector<vector<char>>& cave, int r, int c, vector<vector<int>>& visit, vector<pair<int, int>>& cluster, int flag){
    visit[r][c] = flag;
    cluster.push_back(make_pair(r, c));

    for(int i=0; i<4; i++){
        int next_r = r + dr[i];
        int next_c = c + dc[i];
        if((0 <= next_r && next_r < cave.size()) && (0 <= next_c && next_c < cave[r].size())) {
            if(visit[next_r][next_c] == -1 && cave[next_r][next_c] == 'x')
                DFS(cave, next_r, next_c, visit, cluster, flag);
        }
    }
}
int main(){
    // 입력 받아 동굴 생성.
    int R, C;
    cin >> R >> C;
    vector<vector<char>> cave(R, vector<char>(C, '.'));
    for(int i=0; i<R; i++){
        string state;
        cin >> state;
        for(int j=0; j<state.size(); j++){
            if(state[j] == 'x')
                cave[i][j] = 'x';
        }
    }

    // 막대 던지기 시뮬레이션.
    int N;
    cin >> N;
    int cnt = 1;
    while(cnt <= N){
        int dir = cnt % 2;
        int h;
        cin >> h;
        h = R - h;
        int mineral_pos = searchMineral(cave, h, dir);

        // 막대기 경로에 미네랄이 없는 경우.
        if(mineral_pos == -1) {
            ++cnt;
            continue;
        }

        // 없어진 미네랄과 인접한 클러스터들 구하기.
        cave[h][mineral_pos] = '.';
        vector<vector<int>> visit(R, vector<int>(C, -1));
        vector<vector<pair<int, int>>> clusters(4, vector<pair<int,int>>());
        if(h-1 >= 0 && cave[h-1][mineral_pos] == 'x')
            DFS(cave, h - 1, mineral_pos, visit, clusters[0], 0);
        if(mineral_pos - 1 >= 0 && visit[h][mineral_pos - 1] == -1 && cave[h][mineral_pos - 1] == 'x')
            DFS(cave, h, mineral_pos - 1, visit, clusters[1], 1);
        if(mineral_pos + 1 < C && visit[h][mineral_pos + 1] == -1 && cave[h][mineral_pos + 1] == 'x')
            DFS(cave, h, mineral_pos + 1, visit, clusters[2], 2);
        if(h+1 < R && visit[h+1][mineral_pos] == -1 && cave[h + 1][mineral_pos] == 'x')
            DFS(cave, h + 1, mineral_pos, visit, clusters[3], 3);

        // 분리된 클러스터들과, 바닥 또는 다른 클러스들 사이의 최단거리 구하기.
        int need_down_cluster_idx = -1;
        int min_distance;
        for(int i=0; i<clusters.size(); i++){
            if(clusters[i].size() == 0)
                continue;

            min_distance = 101;
            for(int j=0; j<clusters[i].size(); j++){
                for(int k = clusters[i][j].first; k < R; k++){
                    if(cave[k][clusters[i][j].second] == 'x' && visit[k][clusters[i][j].second] != i)
                        min_distance = min(min_distance, k - clusters[i][j].first);

                    if(k == R - 1)
                        min_distance = min(min_distance, R-clusters[i][j].first);
                }
            }

            if(min_distance > 1){
                need_down_cluster_idx = i;
                break;
            }
        }

        // 분리된 cluster가 공중에 있는 경우.
        if(need_down_cluster_idx != -1){
            // 기존에 있던 cluster 지우기.
            for(int i=0; i<clusters[need_down_cluster_idx].size(); i++){
                int tmp_r = clusters[need_down_cluster_idx][i].first;
                int tmp_c = clusters[need_down_cluster_idx][i].second;
                cave[tmp_r][tmp_c] = '.';
            }
            // cluster 아래로 이동.
            for(int i=0; i<clusters[need_down_cluster_idx].size(); i++){
                int tmp_r = clusters[need_down_cluster_idx][i].first + min_distance - 1;
                int tmp_c = clusters[need_down_cluster_idx][i].second;
                cave[tmp_r][tmp_c] = 'x';
            }
        }
        ++cnt;
    }

    // 결과 출력
    for(int i=0; i<cave.size(); i++){
        for(int j=0; j<cave[i].size(); j++)
            cout << cave[i][j];
        cout << '\n';
    }
    return 0;
}
