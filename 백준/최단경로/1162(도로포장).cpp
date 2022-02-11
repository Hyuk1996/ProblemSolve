#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define INF 10000000001
using namespace std;
int N, M, K;
vector<vector<pair<int, int>>> graph;
struct info {
    int v, paveCnt;
    long long dist;
    info(int v, int paveCnt, long long dist) {
        this->v = v;
        this->paveCnt = paveCnt;
        this->dist = dist;
    }
};
struct cmp {
    bool operator() (const info& a, const info& b) {
        return a.dist > b.dist;
    }
};

void dijkstra(vector<vector<long long>>& dist) {
    priority_queue<info, vector<info>, cmp> pq;

    dist[1][0] = 0;
    pq.push(info(1, 0, 0));
    while(!pq.empty()) {
        int curV = pq.top().v;
        int curPaveCnt = pq.top().paveCnt;
        long long curDist = pq.top().dist;
        pq.pop();

        if(curDist > dist[curV][curPaveCnt]) {
            continue;
        }

        for(int i = 0; i < graph[curV].size(); ++i) {
            int nextV = graph[curV][i].first;
            int weight = graph[curV][i].second;

            //포장도로 가는 경우
            if(curPaveCnt < K && curDist < dist[nextV][curPaveCnt + 1]) {
                dist[nextV][curPaveCnt + 1] = curDist;
                pq.push(info(nextV, curPaveCnt + 1, dist[nextV][curPaveCnt + 1]));
            }
            //비포장 도로 가는 경우
            if(weight + curDist < dist[nextV][curPaveCnt]) {
                dist[nextV][curPaveCnt] = weight + curDist;
                pq.push(info(nextV, curPaveCnt, dist[nextV][curPaveCnt]));
            }
        }
    }
}
long long solve() {
    vector<vector<long long>> dist(N + 1, vector<long long>(K + 1, INF));
    dijkstra(dist);

    long long answer = *min_element(dist[N].begin(), dist[N].end());
    return answer;
}
void input() {
    cin >> N >> M >> K;
    graph.assign(N + 1, vector<pair<int, int>>());
    int u, v, d;
    for(int i = 0; i < M; ++i) {
        cin >> u >> v >> d;
        graph[u].push_back({v, d});
        graph[v].push_back({u, d});
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    input();

    cout << solve();
    return 0;
}
