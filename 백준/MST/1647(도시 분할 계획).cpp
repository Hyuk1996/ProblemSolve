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
        if(u == parent[u])
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
    vector<pair<int, pair<int, int>>> edge_list(M);
    for(int i=0; i<M; ++i){
        int A, B, C;
        cin >> A >> B >> C;
        edge_list.push_back(make_pair(C, make_pair(A, B)));
    }

    // kruskal's algorithm 이용해 MST 구하기.
    sort(edge_list.begin(), edge_list.end());
    DisjointSet sets(N+1);

    int total_weight = 0;
    int max_weight_in_MST = -1;
    for(int i=0; i<edge_list.size(); ++i){
        int u = edge_list[i].second.first;
        int v = edge_list[i].second.second;
        int w = edge_list[i].first;

        if(sets.find(u) == sets.find(v))
            continue;
        sets.merge(u, v);
        total_weight += w;
        max_weight_in_MST = max(max_weight_in_MST, w);
    }

    // 정답 출력.
    int ans = total_weight - max_weight_in_MST;
    cout << ans;
    return 0;
}
