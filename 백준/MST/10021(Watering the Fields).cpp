#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;
const int UNSEEN = 0;
const int FRINGE = 1;
const int TREE = 2;

struct cmp{
    bool operator() (const pair<int, int>& a, const pair<int, int>& b){
        return a.second > b.second;
    }
};
int main(){
    // 입력 받기.
    int N, C;
    cin >> N >> C;
    vector<pair<int, int>> vertices;
    for(int i=0; i<N; i++){
        int x, y;
        cin >> x >> y;
        vertices.push_back(make_pair(x, y));
    }

    // 입력 정보 이용해 그래프 만들기.
    vector<vector<pair<int, int>>> graph(N, vector<pair<int, int>>());
    for(int i=0; i<vertices.size(); i++){
        for(int j=i+1; j<vertices.size(); j++){
            int cost = pow(vertices[i].first - vertices[j].first, 2) + pow(vertices[i].second - vertices[j].second, 2);
            if(cost >= C){
                graph[i].push_back(make_pair(j, cost));
                graph[j].push_back(make_pair(i, cost));
            }
        }
    }

    // 만든 그래프에서 MST 구하기. Prim algorithm 이용.
    vector<int> v(N, UNSEEN);
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> d;

    v[0] = TREE;
    for(int i=0; i<graph[0].size(); i++){
        int adj_v = graph[0][i].first;
        int cost = graph[0][i].second;
        if(v[adj_v] != TREE){
            v[adj_v] = FRINGE;
            d.push(make_pair(adj_v, cost));
        }
    }
    int ans = 0;
    while(!d.empty()){
        int cur_v = d.top().first;
        int weight = d.top().second;
        d.pop();

        if(v[cur_v] == TREE)
            continue;

        ans += weight;
        v[cur_v] = TREE;
        for(int i=0; i<graph[cur_v].size(); i++){
            int adj_v = graph[cur_v][i].first;
            int cost = graph[cur_v][i].second;
            if(v[adj_v] != TREE){
                v[adj_v] = FRINGE;
                d.push(make_pair(adj_v, cost));
            }
        }
    }

    // MST 만들 수 있는지 확인.
    bool possible = true;
    for(int i=0; i< v.size(); i++){
        if(v[i] != TREE){
            possible = false;
            break;
        }
    }

    // 정답 출력.
    if(possible)
        cout << ans;
    else
        cout << -1;
    return 0;
}

// Kruskal's Algorithm 이용.
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct DisjointSet{
    vector<int> parent, rank;
    // 초기화.
    DisjointSet(int n) : parent(n), rank(n, 1){
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
struct edge{
    int weight;
    int v;
    int u;
};

bool cmp(const edge& a, const edge& b){
    return a.weight < b.weight;
}
int main(){
    // 입력 받기.
    int N, C;
    cin >> N >> C;
    vector<pair<int, int>> vertices;
    for(int i=0; i<N; i++){
        int x, y;
        cin >> x >> y;
        vertices.push_back(make_pair(x, y));
    }

    // 입력 정보 edge list 만들기.
    vector<edge> edges;
    for(int i=0; i<vertices.size(); i++){
        for(int j=i+1; j<vertices.size(); j++){
            int cost = pow(vertices[i].first - vertices[j].first, 2) + pow(vertices[i].second - vertices[j].second, 2);
            if(cost >= C){
                edge e;
                e.weight = cost;
                e.v = i;
                e.u = j;
                edges.push_back(e);
            }
        }
    }
    sort(edges.begin(), edges.end(), cmp);

    // Kruskal Algorithm 이용해 MST 구하기.
    int ans = 0;
    DisjointSet ds(N);
    for(int i=0; i<edges.size(); i++){
        int w = edges[i].weight;
        int v = edges[i].v;
        int u = edges[i].u;

        if(ds.find(v) == ds.find(u))
            continue;
        ds.merge(u, v);
        ans += w;
    }

    // MST 만들 수 있는지 확인.
    int root = ds.parent[0];
    for(int i=1; i<N; i++){
        if(root != ds.find(i)){
            ans = -1;
            break;
        }
    }

    // 정답 출력.
    cout << ans;
}
