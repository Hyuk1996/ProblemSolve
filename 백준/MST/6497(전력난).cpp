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


#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct cmp{
    bool operator () (const pair<int, int>& a, const pair<int, int>& b){
        return a.second > b.second; // second 기준으로 min heap
    }
};

int main(){
    vector<int> answers;

    while(true){
        // 입력받아 그래프 만들기.
        int m, n;
        cin >> m >> n;
        if(m == 0 && n == 0)
            break;

        vector<vector<pair<int, int>>> graph(m);
        int graph_total_weight = 0;
        for(int i=0; i<n; ++i){
            int x, y, z;
            cin >> x >> y >> z;
            graph_total_weight += z;
            graph[x].push_back(make_pair(y, z));
            graph[y].push_back(make_pair(x, z));
        }

        // Prim's algorithm 이용해 MST 구하기.
        vector<bool> visit(m, 0);
        priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;

        visit[0] = true;
        for(int i=0; i<graph[0].size(); ++i)
            pq.push(make_pair(graph[0][i].first, graph[0][i].second));

        int MST_total_weight = 0;
        int MST_vertex_cnt = 1;
        while(!pq.empty()){
            int v = pq.top().first;
            int w = pq.top().second;
            pq.pop();

            if(visit[v])
                continue;

            visit[v] = true;
            MST_total_weight += w;
            ++MST_vertex_cnt;
            if(MST_vertex_cnt == n)
                break;

            for(int i=0; i<graph[v].size(); ++i){
                if(!visit[graph[v][i].first])
                    pq.push(make_pair(graph[v][i].first, graph[v][i].second));
            }
        }
        answers.push_back(graph_total_weight - MST_total_weight);
    }

    // 정답 출력.
    for(int i=0; i<answers.size(); ++i)
        cout << answers[i] << '\n';
    return 0;
}
