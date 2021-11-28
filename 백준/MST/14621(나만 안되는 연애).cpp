#include <iostream>
#include <vector>
#include <algorithm>
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

int main(){
    // 입력.
    int N, M;
    cin >> N >> M;

    // 정점들의 정보 저장.
    vector<char> vertices_info(N+1);
    for(int i=1; i<=N; ++i){
        char info;
        cin >> info;
        vertices_info[i] = info;
    }

    // 문제 조건의 부합하는 간선들을 리스트로 만들기.
    vector<pair<int, pair<int, int>>> edge_list;
    for(int i=0; i<M; ++i){
        int u, v, d;
        cin >> u >> v >> d;
        if(vertices_info[u] == vertices_info[v])
            continue;
        edge_list.push_back(make_pair(d, make_pair(u, v)));
    }

    // kruskal's algorithm 이용해 MST 구하기.
    sort(edge_list.begin(), edge_list.end());
    DisjointSet sets(N+1);

    int total_MST_weight = 0;
    int MST_edge_cnt = 0;
    for(int i=0; i<edge_list.size(); ++i){
        int u = edge_list[i].second.first;
        int v = edge_list[i].second.second;
        int w = edge_list[i].first;

        if(sets.find(u) == sets.find(v))
            continue;
        sets.merge(u, v);
        total_MST_weight += w;
        ++MST_edge_cnt;
        if(MST_edge_cnt == N-1)
            break;
    }

    // 정답 출력.
    if(MST_edge_cnt != N-1)
        cout << -1;
    else
        cout << total_MST_weight;
    return 0;
}


#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct cmp{
    bool operator () (const pair<int, int>& a, const pair<int, int>& b){
        return a.second > b.second; // 가중치 기준 min heap
    }
};

int main(){
    // 정점, 간선 수 입력받기.
    int N, M;
    cin >> N >> M;

    // 정점들 정보 입력받기.
    vector<char> vertices_info(N+1);
    for(int i=1; i<=N; ++i){
        char info;
        cin >> info;
        vertices_info[i] = info;
    }

    // 문제 조건에 부합하는 간선들 정보 이용해 그래프로 만들기.
    vector<vector<pair<int, int>>> graph(N+1);
    for(int i=0; i<M; ++i){
        int u, v, d;
        cin >> u >> v >> d;
        if(vertices_info[u] == vertices_info[v])
            continue;
        graph[u].push_back(make_pair(v, d));
        graph[v].push_back(make_pair(u, d));
    }

    // Prim's algorithm 이용해 MST 구하기.
    vector<bool> visit(N+1, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;

    visit[1] = true;
    for(int i=0; i<graph[1].size(); ++i)
        pq.push(make_pair(graph[1][i].first, graph[1][i].second));

    int total_MST_weight = 0;
    int MST_vertex_cnt = 1;
    while(!pq.empty()){
        int v = pq.top().first;
        int w = pq.top().second;
        pq.pop();

        if(visit[v])
            continue;
        visit[v] = true;
        total_MST_weight += w;
        ++MST_vertex_cnt;
        if(MST_vertex_cnt == N)
            break;
        for(int i=0; i<graph[v].size(); ++i){
            if(!visit[graph[v][i].first])
                pq.push(make_pair(graph[v][i].first, graph[v][i].second));
        }
    }

    // 정답 출력.
    if(MST_vertex_cnt != N)
        cout << -1;
    else
        cout << total_MST_weight;
    return 0;
}

