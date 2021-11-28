#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct cmp{
    bool operator () (const pair<int, int>& a, const pair<int, int>& b){
        return a.second > b.second; // 가중치 기준 min heap
    }
};

int main(){
    // 입력 받아, 인접 행렬 기반 그래프 생성.
    int N;
    cin >> N;
    vector<vector<int>> graph(N, vector<int>(N));
    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            int weight;
            cin >> weight;
            graph[i][j] = weight;
        }
    }

    // Prim's algorithm 이용해 MST 구하기.
    vector<bool> visit(N, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;

    visit[0] = true;
    for(int i=0; i<N; ++i){
        if(!visit[i])
            pq.push(make_pair(i, graph[0][i]));
    }

    long long total_MST_weight = 0;
    int MST_vertex_cnt = 1;
    while(!pq.empty()){
        int v = pq.top().first;
        int w = pq.top().second;
        pq.pop();

        if(visit[v])
            continue;
        visit[v] = true;
        total_MST_weight += (long long)w;
        ++MST_vertex_cnt;
        if(MST_vertex_cnt == N)
            break;
        for(int i=0; i<N; ++i){
            if(!visit[i])
                pq.push(make_pair(i, graph[v][i]));
        }
    }

    // 정답 출력.
    cout << total_MST_weight;
    return 0;
}
