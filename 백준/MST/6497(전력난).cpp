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
    vector<int> answers;
    while(true){
        // 입력받아 edge_list 생성.
        int m, n;
        cin >> m >> n;
        if(m == 0 && n == 0)
            break;
        int graph_total_weight = 0;
        vector<pair<int, pair<int, int>>> edge_list;
        for(int i=0; i<n; ++i){
            int x, y, z;
            cin >> x >> y >> z;
            edge_list.push_back(make_pair(z, make_pair(x, y)));
            graph_total_weight += z;
        }

        // kruskal's algorithm 이용해 MST 구하기.
        sort(edge_list.begin(), edge_list.end());
        DisjointSet sets(n);

        int MST_total_weight = 0;
        int MST_edge_cnt = 0;
        for(int i=0; i<edge_list.size(); ++i){
            int u = edge_list[i].second.first;
            int v = edge_list[i].second.second;
            int w = edge_list[i].first;

            if(sets.find(u) == sets.find(v))
                continue;
            sets.merge(u, v);
            MST_total_weight += w;
            ++MST_edge_cnt;
            if(MST_edge_cnt == n-1)
                break;
        }

        int ans = graph_total_weight - MST_total_weight;
        answers.push_back(ans);
    }

    // 정답 출력.
    for(int i=0; i<answers.size(); ++i)
        cout << answers[i] << '\n';
    return 0;
}
