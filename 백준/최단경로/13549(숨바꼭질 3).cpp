#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int MAX_VERTICES = 100001;
const int INF = 987654321;
struct cmp {
    bool operator () (const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }
};

int main() {
    // 출발점, 도착점 입력 받기.
    int N, K;
    cin >> N >> K;

    // 그래프 만들기.
    vector<vector<pair<int, int>>> graph(MAX_VERTICES);
    for(int i=0; i<MAX_VERTICES; ++i) {
        if((i-1) >= 0)
            graph[i].push_back(make_pair(i-1, 1));

        if((i+1) < MAX_VERTICES)
            graph[i].push_back(make_pair(i+1, 1));

        if((i*2) < MAX_VERTICES)
            graph[i].push_back(make_pair(i*2, 0));
    }


    // Dijkstra 알고리즘 이용해 최단거리 구하기.
    vector<int> dist(MAX_VERTICES, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp > pq;

    dist[N] = 0;
    pq.push(make_pair(N, 0));
    while(!pq.empty()) {
        int v = pq.top().first;
        int cost = pq.top().second;
        pq.pop();

        if(dist[v] < cost)
            continue;
        for(int i=0; i<graph[v].size(); ++i) {
            int next_v = graph[v][i].first;
            int next_cost = dist[v] + graph[v][i].second;
            if(dist[next_v] > next_cost) {
                dist[next_v] = next_cost;
                pq.push(make_pair(next_v, dist[next_v]));
            }
        }
    }

    // 정답 출력.
    cout << dist[K];
    return 0;
}
