#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

void bfs(const vector<vector<int>>& graph, int start_vertex, int K, vector<int>& vertices) {
    queue<int> q;
    vector<bool> visit(graph.size(), 0);
    int dist = 0;

    q.push(start_vertex);
    visit[start_vertex] = true;
    while(!q.empty()) {
        int q_size = q.size();
        for(int i=0; i<q_size; ++i) {
            int v = q.front();
            q.pop();

            for(int j=0; j<graph[v].size(); ++j) {
                int next_v = graph[v][j];
                if(!visit[next_v]) {
                    q.push(next_v);
                    visit[next_v] = true;
                }
            }
        }
        ++dist;
        if(dist == K)
            break;
    }

    while(!q.empty()) {
        vertices.push_back(q.front());
        q.pop();
    }
    return;
}
int main() {
    // 도시의 개수(N), 도로의 개수(M), 거리 정보(K), 출발 도시 번호(X) 입력 받기.
    int N, M, K, X;
    cin >> N >> M >> K >> X;

    // Directed Graph 구현.
    vector<vector<int>> graph(N+1);
    for(int i=0; i<M; ++i) {
        int A, B;
        cin >> A >> B;
        graph[A].push_back(B);
    }

    // BFS 이용해 X에서 출발해 최단거리가 K인 정점들 구하기.
    vector<int> vertices;
    bfs(graph, X, K, vertices);

    // 정답 출력.
    sort(vertices.begin(), vertices.end());
    if(vertices.size() == 0)
        cout << -1;
    else {
        for(int vertex : vertices)
            cout << vertex << '\n';
    }
    return 0;
}
