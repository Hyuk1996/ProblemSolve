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
