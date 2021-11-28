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
