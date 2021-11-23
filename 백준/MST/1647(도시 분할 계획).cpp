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


#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
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
        int A, B, C;
        cin >> A >> B >> C;
        graph[A].push_back(make_pair(B, C));
        graph[B].push_back(make_pair(A, C));
    }

    // Prim's algorithm 이용해 MST 구하기.
    vector<int> visit(N+1, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;

    visit[1] = true;
    for(int i=0; i<graph[1].size(); ++i)
        pq.push(make_pair(graph[1][i].first, graph[1][i].second));

    int total_weights = 0;
    int max_weight = -1;
    while(!pq.empty()){
        int v = pq.top().first;
        int w = pq.top().second;
        pq.pop();

        if(visit[v])
            continue;
        visit[v] = true;
        total_weights += w;
        max_weight = max(max_weight, w);
        for(int i=0; i<graph[v].size(); ++i){
            if(!visit[graph[v][i].first])
                pq.push(make_pair(graph[v][i].first, graph[v][i].second));
        }
    }

    // 정답 출력.
    int ans = total_weights - max_weight;
    cout << ans;
    return 0;
}
