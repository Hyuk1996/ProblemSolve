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
int main(){
    // 입력.
    int N;
    cin >> N;
    vector<pair<int, int>> x_vertices;
    vector<pair<int, int>> y_vertices;
    vector<pair<int, int>> z_vertices;
    for(int i=0; i<N; ++i){
        int x, y, z;
        cin >> x >> y >> z;
        x_vertices.push_back(make_pair(x, i));
        y_vertices.push_back(make_pair(y, i));
        z_vertices.push_back(make_pair(z, i));
    }

    // 좌표를 분리해 각 좌표에서의 MST 구하기. 정렬 후 인접한 정점을 연결하면 그 간선들이 해당 좌표에서의 MST
    sort(x_vertices.begin(), x_vertices.end());
    sort(y_vertices.begin(), y_vertices.end());
    sort(z_vertices.begin(), z_vertices.end());

    // 각 좌표에서의 MST에 속한 간선들을 후보로 전체 좌표에서의 MST 구하기.
    vector<pair<int, pair<int, int>>> edge_list;
    for(int i=0; i<N-1; ++i){
        edge_list.push_back(make_pair(x_vertices[i+1].first - x_vertices[i].first, make_pair(x_vertices[i].second, x_vertices[i+1].second)));
        edge_list.push_back(make_pair(y_vertices[i+1].first - y_vertices[i].first, make_pair(y_vertices[i].second, y_vertices[i+1].second)));
        edge_list.push_back(make_pair(z_vertices[i+1].first - z_vertices[i].first, make_pair(z_vertices[i].second, z_vertices[i+1].second)));
    }

    // Kruskal's Algorithm 이용해 최종 MST 구하기.
    sort(edge_list.begin(), edge_list.end());
    DisjointSet sets(N);

    long long total_weight = 0;
    int cnt_edge = 0;
    for(int i=0; i<edge_list.size(); ++i){
        int u = edge_list[i].second.first;
        int v = edge_list[i].second.second;
        int w = edge_list[i].first;

        if(sets.find(u) == sets.find(v))
            continue;
        sets.merge(u, v);
        total_weight += w;
        ++cnt_edge;

        if(cnt_edge == N-1)
            break;
    }

    // 정답 출력.
    cout << total_weight;
    return 0;
}
