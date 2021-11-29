#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int INF = 987654321;
struct cmp {
    bool operator () (const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; // 거리 기준 min heap;
    }
};

int main(){
    // 정점 개수, 간선 개수.
    int V, E;
    cin >> V >> E;

    // 시작 정점.
    int start_vertex;
    cin >> start_vertex;

    // 인접 리스트로 방향 그래프 생성.
    vector<vector<pair<int, int>>> graph(V+1);
    for(int i=0; i<E; ++i){
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back(make_pair(v, w));
    }

    // Dijkstra's Shortest-Path Algorithm 이용.
    vector<int> dist(V+1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp > pq;

    dist[start_vertex] = 0;
    for(int i=0; i<graph[start_vertex].size(); ++i)
        pq.push(make_pair(graph[start_vertex][i].first, graph[start_vertex][i].second));

    while(!pq.empty()){
        int v = pq.top().first;
        int cost = pq.top().second;
        pq.pop();

        if(dist[v] < cost)
            continue;
        dist[v] = cost;
        for(int i=0; i<graph[v].size(); ++i){
            if(dist[graph[v][i].first] == INF)
                pq.push(make_pair(graph[v][i].first, dist[v] + graph[v][i].second));
        }
    }

    // 정답 출력.
    for(int i=1; i<=V; ++i){
        if(dist[i] == INF)
            cout << "INF\n";
        else
            cout << dist[i] << '\n';
    }
    return 0;
}
