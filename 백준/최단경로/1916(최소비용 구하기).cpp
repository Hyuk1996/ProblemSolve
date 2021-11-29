#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const long long INF = 20000000000;
struct cmp {
    bool operator () (const pair<int, long long>& a, const pair<int, long long>& b) {
        return a.second > b.second;
    }
};

int main(){
    // 정점의 수, 간선의 수
    int N, M;
    cin >> N >> M;

    // 간선 정보 이용해 방향 그래프 만들기.
    vector<vector<pair<int, int>>> graph(N+1);
    for(int i=0; i<M; ++i){
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back(make_pair(v, w));
    }

    // 출발 도시, 도착 도시
    int start_vertex, arrive_vertex;
    cin >> start_vertex >> arrive_vertex;

    // 다익스트라 알고리즘 이용해 최소비용 구하기.
    vector<long long> dist(N+1, INF);
    priority_queue<pair<int, long long>, vector<pair<int, long long>>, cmp > pq;

    dist[start_vertex] = 0;
    for(int i=0; i<graph[start_vertex].size(); ++i)
        pq.push(make_pair(graph[start_vertex][i].first, graph[start_vertex][i].second));

    long long min_cost = 0;
    while(!pq.empty()){
        int v = pq.top().first;
        long long cost = pq.top().second;
        pq.pop();

        if(v == arrive_vertex){
            min_cost = cost;
            break;
        }

        if(dist[v] < cost)
            continue;
        dist[v] = cost;
        for(int i=0; i<graph[v].size(); ++i){
            if(dist[graph[v][i].first] == INF)
                pq.push(make_pair(graph[v][i].first, dist[v] + graph[v][i].second));
        }
    }

    // 정답 출력.
    cout << min_cost;
    return 0;
}
