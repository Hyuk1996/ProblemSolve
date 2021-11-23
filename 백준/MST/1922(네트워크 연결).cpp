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

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct cmp{
    bool operator() (const pair<int, int>& a, const pair<int, int>& b){
        return a.second > b.second;
    }
};
int main(){
    // 입력.
    int N, M;
    cin >> N >> M;
    vector<vector<pair<int, int>>> graph(N+1);
    for(int i=0; i<M; ++i){
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back(make_pair(b, c));
        graph[b].push_back(make_pair(a, c));
    }

    // Prim's algorithm 이용해 MST 구하기.
    vector<bool> visit(N+1, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;

    // 시작 정점 1
    visit[1] = true;
    for(int i=0; i<graph[1].size(); ++i)
        pq.push(make_pair(graph[1][i].first, graph[1][i].second));

    int total_weights = 0;
    while(!pq.empty()){
        int next_v = pq.top().first;
        int weight = pq.top().second;
        pq.pop();

        if(visit[next_v])
            continue;

        visit[next_v] = true;
        total_weights += weight;
        for(int i=0; i<graph[next_v].size(); ++i){
            if(!visit[graph[next_v][i].first])
                pq.push(make_pair(graph[next_v][i].first, graph[next_v][i].second));
        }
    }

    // 정답 출력.
    cout << total_weights;
    return 0;
}
