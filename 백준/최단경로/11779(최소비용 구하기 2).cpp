#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
const int INF = 987654321;
struct cmp {
    bool operator () (const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }
};

int main() {
    // 도시의 개수, 버스의 개수 입력 받기.
    int n, m;
    cin >> n >> m;

    // 버스들 정보 이용해 그래프 구현.
    vector<vector<pair<int, int>>> graph(n+1);
    for(int i=0; i<m; ++i) {
        int source, destination, weight;
        cin >> source >> destination >> weight;
        graph[source].push_back(make_pair(destination, weight));
    }

    // 출발 도시 번호, 도착 도시 번호.
    int start_city, arrival_city;
    cin >> start_city >> arrival_city;

    // Dijkstra 이용해 최소비용 찾기.
    vector<int> dist(n+1, INF);
    vector<int> parent(n+1, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp > pq;

    dist[start_city] = 0;
    pq.push(make_pair(start_city, dist[start_city]));
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
                parent[next_v] = v;
                pq.push(make_pair(next_v, dist[next_v]));
            }
        }
    }

    // 도시 개수, 도시 방문 순서 구하기.
    int city_cnt = 0;
    int idx = arrival_city;
    stack<int> path;
    while(true) {
        path.push(idx);
        ++city_cnt;

        if(parent[idx] == 0)
            break;
        idx = parent[idx];
    }

    // 정답 출력.
    cout << dist[arrival_city] << '\n';
    cout << city_cnt << '\n';
    while(!path.empty()) {
        cout << path.top() << ' ';
        path.pop();
    }
    return 0;
}
