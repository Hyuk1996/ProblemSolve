#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct DisjointSet{
    vector<int> parent, rank;
    DisjointSet(int n) : parent(n), rank(n, 1) {
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
        parent[u] = v; // u -> v에 merge
        if(rank[u] == rank[v])
            ++rank[v];
    }
};


int main(){
    // 입력.
    int N;
    cin >> N;
    int M;
    cin >> M;
    vector<pair<int, pair<int, int>>> edges;
    for(int i=0; i<M; ++i){
        int a, b, c;
        cin >> a >> b >> c;
        edges.push_back(make_pair(c, make_pair(a, b)));
    }

    // kruskal's algorithm 이용해 MST 구하기.
    sort(edges.begin(), edges.end());
    DisjointSet sets(N+1);

    int total_weight = 0;
    int idx = 0;
    while(idx <= edges.size()){
        int a = edges[idx].second.first;
        int b = edges[idx].second.second;
        int c = edges[idx].first;

        if(sets.find(a) != sets.find(b)) {
            sets.merge(a, b);
            total_weight += c;
        }

        ++idx;
    }

    // 정답 출력.
    cout << total_weight;
    return 0;
}
