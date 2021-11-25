#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
const int VISIT = 2;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
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

int getColumnEdgeWeight(vector<pair<int, int>>& v, vector<pair<int, int>>& u, vector<vector<int>>& map){
    int weight = 11;
    for(int i=0; i<v.size(); ++i){
        for(int j=0; j<u.size(); ++j){
            if(v[i].second == u[j].second){
                int c = v[i].second;
                int r1 = v[i].first;
                int r2 = u[j].first;
                if(r1 > r2)
                    swap(r1, r2);

                int tmp_weight = 0;
                for(int k=r1+1; k<r2; ++k){
                    if(map[k][c] != 0){
                        tmp_weight = -1;
                        break;
                    }
                    ++tmp_weight;
                }
                if(tmp_weight > 1)
                    weight = min(weight, tmp_weight);
            }
        }
    }
    return weight;
}
int getRowEdgeWeight(vector<pair<int, int>>& v, vector<pair<int, int>>& u, vector<vector<int>>& map){
    int weight = 11;
    for(int i=0; i<v.size(); ++i){
        for(int j=0; j<u.size(); ++j){
            if(v[i].first == u[j].first){
                int r = v[i].first;
                int c1 = v[i].second;
                int c2 = u[j].second;
                if(c1 > c2)
                    swap(c1, c2);

                int tmp_weight = 0;
                for(int k=c1+1; k<c2; ++k){
                    if(map[r][k] != 0){
                        tmp_weight = -1;
                        break;
                    }
                    ++tmp_weight;
                }
                if(tmp_weight > 1)
                    weight = min(weight, tmp_weight);
            }
        }
    }
    return weight;
}
void dfs(vector<vector<int>>& map, vector<pair<int, int>>& vertex, int y, int x){
    map[y][x] = VISIT;
    vertex.push_back(make_pair(y, x));

    for(int i=0; i<4; ++i){
        int next_y = y + dy[i];
        int next_x = x + dx[i];
        if((0 <= next_y && next_y < map.size()) && (0 <= next_x && next_x < map[y].size())) {
            if (map[next_y][next_x] == 1)
                dfs(map, vertex, next_y, next_x);
        }
    }
}
int main(){
    // 입력.
    int N, M;
    cin >> N >> M;
    vector<vector<int>> map(N, vector<int>(M));
    for(int i=0; i<N; ++i){
        for(int j=0; j<M; ++j){
            int info;
            cin >> info;
            map[i][j] = info;
        }
    }

    // DFS 이용해 인접한 땅들을 그룹화.
    vector<vector<pair<int, int>>> vertices;
    for(int i=0; i<N; ++i){
        for(int j=0; j<M; ++j){
            if(map[i][j] == 1){
                vector<pair<int, int>> vertex;
                dfs(map, vertex, i, j);
                vertices.push_back(vertex);
            }
        }
    }

    // 정점들 사이의 만들 수 있는 모든 간선 정보 리스트 만들기.
    vector<pair<int, pair<int, int>>> edge_list;
    for(int i=0; i<vertices.size(); ++i){
        for(int j=i+1; j<vertices.size(); ++j){
            // 가능한 가로 다리.
            int w = getRowEdgeWeight(vertices[i], vertices[j], map);
            if(w <= 10)
                edge_list.push_back(make_pair(w, make_pair(i, j)));

            // 가능한 세로 다리.
            w = getColumnEdgeWeight(vertices[i], vertices[j], map);
            if( w <= 10)
                edge_list.push_back(make_pair(w, make_pair(i, j)));
        }
    }

    // kruskal's algorithm 이용해 MST 구하기.
    sort(edge_list.begin(), edge_list.end());
    DisjointSet sets(vertices.size());

    int total_weight = 0;
    int edge_cnt = 0;
    for(int i=0; i<edge_list.size(); ++i){
        int v = edge_list[i].second.first;
        int u = edge_list[i].second.second;
        int w = edge_list[i].first;

        if(sets.find(u) == sets.find(v))
            continue;

        sets.merge(u, v);
        total_weight += w;
        ++edge_cnt;
        if(edge_cnt == vertices.size() - 1)
            break;
    }

    // 정답 출력.
    if(edge_cnt == vertices.size() - 1)
        cout << total_weight;
    else
        cout << -1;
    return 0;
}
