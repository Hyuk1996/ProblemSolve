#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int INF = 987654321;
struct cmp {
    bool operator () (const pair<int, int>& a, const pair<int, int>& b){
        return a.second > b.second;
    }
};

void getDistances(vector<vector<pair<int, int>>>& graph, int start_vertex, vector<int>& dist){
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;

    dist[start_vertex] = 0;
    pq.push(make_pair(start_vertex, 0));
    while(!pq.empty()){
        int v = pq.top().first;
        int cost = pq.top().second;
        pq.pop();

        if(dist[v] < cost)
            continue;
        for(int i=0; i<graph[v].size(); ++i){
            int next_v = graph[v][i].first;
            int next_cost = dist[v] + graph[v][i].second;
            if(dist[next_v] > next_cost){
                dist[next_v] = next_cost;
                pq.push(make_pair(next_v, dist[next_v]));
            }
        }
    }
}
int main(){
    // 정점 개수(N), 간선 개수(M), X 입력.
    int N, M ,X;
    cin >> N >> M >> X;

    // 간선 정보 이용해, graph 와 transpose graph 만들기.
    vector<vector<pair<int, int>>> graph(N+1);
    vector<vector<pair<int, int>>> transpose_graph(N+1);
    for(int i=0; i<M; ++i){
        int v, u, w;
        cin >> v >> u >> w;
        graph[v].push_back(make_pair(u, w));
        transpose_graph[u].push_back(make_pair(v, w));
    }

    // 각각의 그래프에서 dijkstra 알고리즘 이용해 x를 출발점으로 최단경로의 거리 구하기.
    vector<int> transpose_dist(N+1, INF);
    getDistances(transpose_graph, X, transpose_dist);

    vector<int> dist(N+1, INF);
    getDistances(graph, X, dist);

    // 정답 구하기.
    int answer = -1;
    for(int i=1; i<=N; ++i)
        answer = max(answer, transpose_dist[i] + dist[i]);
    cout << answer;
    return 0;
}
