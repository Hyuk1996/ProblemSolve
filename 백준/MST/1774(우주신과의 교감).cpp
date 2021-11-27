#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
struct DisjointSet{
    vector<int> parent, rank;
    DisjointSet(int n): parent(n), rank(n, 1){
        for(int i=0; i<n; ++i)
            parent[i] = i;
    }
    int find(int u){
        if(parent[u] == u)
            return u;
        return parent[u] = find(parent[u]);
    }
    void merge(int u, int v){
        u = find(u);
        v = find(v);
        if(u == v)
            return;
        if(rank[u] > rank[v])
            swap(u, v);
        parent[u] = v;
        if(rank[u] == rank[v])
            ++rank[v];
    }
};

double getWeight(pair<int, int>& x, pair<int, int>& y){
    double x_dist = pow((double)x.first - (double)y.first, 2);
    double y_dist = pow((double)x.second - (double)y.second, 2);
    return sqrt(x_dist + y_dist);
}
int main(){
    // 입력.
    int N, M;
    cin >> N >> M;

    // 정점 좌표 정보 저장.
    vector<pair<int, int>> vertices(N+1);
    for(int i=1; i<=N; ++i){
        int X, Y;
        cin >> X >> Y;
        vertices[i] = {X, Y};
    }

    // 이미 연결되어 있는 간선들 정보 저장.
    vector<pair<double, pair<int, int>>> essential_edge_list;
    for(int i=0; i<M; ++i){
        int X, Y;
        cin >> X >> Y;
        double weight = getWeight(vertices[X], vertices[Y]);
        essential_edge_list.push_back(make_pair(weight, make_pair(X, Y)));
    }

    // 그래프에서 가능한 모든 edge_list 구하기.
    vector<pair<double, pair<int, int>>> edge_list;
    for(int i=1; i<=N; ++i){
        for(int j=i+1; j<=N; ++j){
            double weight = getWeight(vertices[i], vertices[j]);
            edge_list.push_back(make_pair(weight, make_pair(i, j)));
        }
    }

    // 이미 연결된 간선들을 Tree 에 추가.
    DisjointSet sets(N+1);

    for(int i=0; i<essential_edge_list.size(); ++i){
        int u = essential_edge_list[i].second.first;
        int v = essential_edge_list[i].second.second;

        sets.merge(u, v);
    }

    // Kruskal's Algorithm 이용해 Tree를 만들기 위해서 필요한 최소비용의 간선들 구하기.
    int edge_cnt = M;
    double need_cost = 0;
    sort(edge_list.begin(), edge_list.end());
    for(int i=0; i<edge_list.size(); ++i){
        if(edge_cnt == N - 1)
            break;

        int u = edge_list[i].second.first;
        int v = edge_list[i].second.second;
        double w = edge_list[i].first;

        if(sets.find(u) == sets.find(v))
            continue;

        sets.merge(u, v);
        need_cost += w;
        ++edge_cnt;
    }

    // 정답 출력.
    cout << fixed;
    cout .precision(2);
    cout << round(need_cost * 100) / 100;
    return 0;
}


#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;
struct cmp{
    bool operator () (const pair<int, double>& a, const pair<int, double>& b){
        return a.second > b.second; // 가중치 기준으로 min heap
    }
};

double getWeight(const pair<int, int>& v, const pair<int, int>& u){
    double x_dist = pow((double)v.first - (double)u.first, 2);
    double y_dist = pow((double)v.second - (double)u.second, 2);
    return sqrt(x_dist + y_dist);
}
int main(){
    // 입력.
    int N, M;
    cin >> N >> M;

    // 정점들의 좌표 정보 저장.
    vector<pair<int, int>> vertices(N+1);
    for(int i=1; i<=N; ++i){
        int X, Y;
        cin >> X >> Y;
        vertices[i] = {X, Y};
    }

    // 정점 좌표정보 이용해 그래프로 표현하기.
    vector<vector<pair<int, double>>> graph(N+1);
    for(int i=1; i<=N; ++i){
        for(int j=i+1; j<=N; ++j){
            double weight = getWeight(vertices[i], vertices[j]);
            graph[i].push_back(make_pair(j, weight));
            graph[j].push_back(make_pair(i, weight));
        }
    }

    // 이미 이어진 간선들의 가중치는 0이라고 가정.
    for(int i=0; i<M; ++i){
        int v, u;
        cin >> v >> u;
        for(int j=0; j<graph[v].size(); ++j) {
            if (graph[v][j].first == u)
                graph[v][j].second = 0;
        }
        for(int j=0; j<graph[u].size(); ++j){
            if(graph[u][j].first == v)
                graph[u][j].second = 0;
        }
    }

    // Prim's algorithm 이용해 MST 구하기.
    vector<bool> visit(N+1, 0);
    priority_queue<pair<int, double>, vector<pair<int, double>>, cmp> pq;

    visit[1] = true;
    for(int i=0; i<graph[1].size(); ++i)
        pq.push(make_pair(graph[1][i].first, graph[1][i].second));

    double need_cost = 0;
    int vertex_cnt = 1;
    while(!pq.empty()){
        int v = pq.top().first;
        double w = pq.top().second;
        pq.pop();

        if(visit[v])
            continue;
        visit[v] = true;
        need_cost += w;
        ++vertex_cnt;

        if(vertex_cnt == N)
            break;
        for(int i=0; i<graph[v].size(); ++i){
            if(!visit[graph[v][i].first])
                pq.push(make_pair(graph[v][i].first, graph[v][i].second));
        }
    }

    // 정답 출력.
    cout << fixed;
    cout.precision(2);
    cout << round(need_cost * 100) / 100;
    return 0;
}
