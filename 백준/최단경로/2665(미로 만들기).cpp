#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int INF = 987654321;
const int dy[4] = {0, 0, -1, 1};
const int dx[4] = {-1, 1, 0, 0};
struct cmp {
    bool operator () (const pair<pair<int, int>, int>& a, const pair<pair<int, int>, int>& b) {
        return a.second > b.second;
    }
};

int main() {
    //  입력 받아, 격자 생성.
    int n;
    cin >> n;

    vector<vector<int>> map(n, vector<int>(n));
    for(int i=0; i<n; ++i) {
        string info;
        cin >> info;
        for(int j=0; j<info.size(); ++j)
            map[i][j] = info[j] - '0';
    }

    // (0,0)을 시작점으로 두고, Dijkstra 알고리즘 수행.
    // 흰방이면 가중치: 0, 검은방이면 가중치: 1
    vector<vector<int>> dist(n, vector<int>(n, INF));
    priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, cmp > pq;

    dist[0][0] = 0;
    pq.push(make_pair(make_pair(0, 0), dist[0][0]));
    while(!pq.empty()) {
        int y = pq.top().first.first;
        int x = pq.top().first.second;
        int cost = pq.top().second;
        pq.pop();

        if(dist[y][x] < cost)
            continue;
        for(int i=0; i<4; ++i) {
            int next_y = y + dy[i];
            int next_x = x + dx[i];
            if((0 <= next_y && next_y < n) && (0 <= next_x && next_x < n)) {
                int next_cost = dist[y][x];
                if(map[next_y][next_x] == 0)
                    ++next_cost;
                if(dist[next_y][next_x] > next_cost) {
                    dist[next_y][next_x] = next_cost;
                    pq.push(make_pair(make_pair(next_y, next_x), dist[next_y][next_x]));
                }
            }
        }
    }

    // 정답 출력.
    cout << dist[n-1][n-1];
    return 0;
}
