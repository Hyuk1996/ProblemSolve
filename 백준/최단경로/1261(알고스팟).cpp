#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int INF = 987654321;
struct cmp{
    bool operator () (const pair<int, int>& a, const pair<int, int>& b){
        return a.second > b.second;
    }
};

int main(){
    // 입력 받아 미로 만들기.
    int M, N;
    cin >> M >> N;
    vector<vector<int>> miro(N, vector<int>(M));
    for(int i=0; i<N; ++i){
        string miro_info;
        cin >> miro_info;
        for(int j=0; j<miro_info.size(); ++j)
            miro[i][j] = miro_info[j] - '0';
    }

    // miro의 한칸을 정점이라 가정, 칸이 벽이라면 가중치:1 아니면 가중치:0
    // dijkstra 알고리즘 이용해 최단거리 구하기.
    int dy[4] = {0, 0, -1, 1};
    int dx[4] = {-1, 1, 0, 0};
    vector<vector<int>> dist(N, vector<int>(M, INF));
    vector<vector<bool>> visit(N, vector<bool>(M, 0));
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;

    dist[0][0] = 0;
    pq.push(make_pair(0, 0));
    while(!pq.empty()){
        int y = pq.top().first / 100;
        int x = pq.top().first % 100;
        pq.pop();

        if(visit[y][x])
            continue;
        visit[y][x] = true;
        for(int i=0; i<4; ++i){
            int next_y = y + dy[i];
            int next_x = x + dx[i];
            if((0 <= next_y && next_y < N) && (0 <= next_x && next_x < M)){
                if(!visit[next_y][next_x] && dist[y][x] + miro[next_y][next_x] < dist[next_y][next_x])
                    dist[next_y][next_x] = dist[y][x] + miro[next_y][next_x];
                    pq.push(make_pair(next_y * 100 + next_x, dist[next_y][next_x]));
            }
        }
    }

    // 정답 출력.
    cout << dist[N-1][M-1];
    return 0;
}
