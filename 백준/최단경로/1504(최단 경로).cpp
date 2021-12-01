#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int INF = 987654321;
struct cmp {
    bool operator () (const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }
};

int getDistance(vector<vector<pair<int, int>>>& graph, int start_vertex, int end_vertex) {
    vector<int> dist(graph.size(), INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp > pq;

    dist[start_vertex] = 0;
    pq.push(make_pair(start_vertex, 0));
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

    if(dist[end_vertex] == INF)
        return -1;
    else
        return dist[end_vertex];
}
int main() {
    // 정점 개수(N), 간선 개수(E) 입력.
    int N, E;
    cin >> N >> E;

    // 간선 정보 이용해, 그래프 만들기.
    vector<vector<pair<int, int>>> graph(N+1);
    for(int i=0; i<E; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back(make_pair(b, c));
        graph[b].push_back(make_pair(a, c));
    }

    // 거쳐야 하는 정점.
    int v, u;
    cin >> v >> u;

    // 1 -> v -> u -> N, 1 -> u -> v -> N 두 경우 중 더 짧은 경로 구하기.
    // Dijkstra 알고리즘 이용 1 -> v -> u -> N
    int dist = INF;
    int dist_to_v = getDistance(graph, 1, v);
    int dist_to_u = getDistance(graph, v, u);
    int dist_to_N = getDistance(graph, u, N);

    if(dist_to_v != -1 || dist_to_u != -1 || dist_to_N != -1)
        dist = min(dist, dist_to_v + dist_to_u + dist_to_N);

    // Dijkstra 알고리즘 이용 1 -> u -> v -> N
    dist_to_u = getDistance(graph, 1, u);
    dist_to_v = getDistance(graph, u, v);
    dist_to_N = getDistance(graph, v, N);

    if(dist_to_u != -1 && dist_to_v != -1 && dist_to_N != -1)
        dist = min(dist, dist_to_u + dist_to_v + dist_to_N);

    // 정답 출력.
    if(dist == INF)
        cout << -1;
    else
        cout << dist;
    return 0;
}
