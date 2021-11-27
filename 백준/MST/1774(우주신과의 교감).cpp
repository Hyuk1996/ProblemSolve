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
