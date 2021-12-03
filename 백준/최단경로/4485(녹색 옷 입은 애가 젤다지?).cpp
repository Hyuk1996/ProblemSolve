#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int INF = 987654321;
const int dy[4] = {0, 0, -1, 1};
const int dx[4] = {-1, 1, 0, 0};
struct cmp {
    bool operator () (const pair<pair<int, int>, int>& a, const pair<pair<int, int>, int>& b){
        return a.second > b.second;
    }
};

int getMinCost(const vector<vector<int>>& cave) {
    //Dijkstra
    int N = cave.size();
    vector<vector<int>> dist(N, vector<int>(N, INF));
    priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, cmp> pq;

    dist[0][0] = cave[0][0];
    pq.push(make_pair(make_pair(0, 0), dist[0][0]));
    while(!pq.empty()) {
        int y = pq.top().first.first;
        int x = pq.top().first.second;
        int cost = pq.top().second;
        pq.pop();

        // 이미 최단거리가 구해진 경우.
        if(dist[y][x] < cost)
            continue;

        for(int i=0; i<4; ++i) {
            int next_y = y + dy[i];
            int next_x = x + dx[i];
            if((0 <= next_y && next_y < N) && (0 <= next_x && next_x < N)) {
                int next_cost = dist[y][x] + cave[next_y][next_x];
                if(dist[next_y][next_x] > next_cost) {
                    dist[next_y][next_x] = next_cost;
                    pq.push(make_pair(make_pair(next_y, next_x), dist[next_y][next_x]));
                }
            }
        }
    }

    return dist[N-1][N-1];
}
int main() {
    // TestCase 마다 동굴의 크기(N) 입력 받기.
    int N;
    vector<int> answers;
    while(true) {
        cin >> N;
        if(N == 0)
            break;

        // vector 이용 동굴 정보 저장.
        vector<vector<int>> cave(N, vector<int>(N));
        for(int i=0; i<N; ++i) {
            for(int j=0; j<N; ++j) {
                int thief_rupee;
                cin >> thief_rupee;
                cave[i][j] = thief_rupee;
            }
        }

        // Dijkstra 이용해 (0,0) -> (N-1, N-1) 최소비용 구하기.
        answers.push_back(getMinCost(cave));
    }

    // 정답 출력.
    for(int i=0; i<answers.size(); ++i)
        cout << "Problem " << i+1 << ": " << answers[i] << '\n';
    return 0;
}
