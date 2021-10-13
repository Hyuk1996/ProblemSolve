#include <iostream>
#include <vector>
#include <queue>

using namespace std;
struct cmp{
  bool operator() (const pair<int,int>& a, const pair<int, int>& b){
      if(a.second == b.second)
          return a.first > b.first;
      return a.second > b.second; 
  }  
};
void dijkstra(vector<vector<pair<int, int>>>& g, vector<int>& d, int N){
    vector<int> visit(N+1, 0); // 0: unseen, 1: fringe, 2: tree
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
    
    pq.push(make_pair(1, 0));
    visit[1] = 1;
    while(!pq.empty()){
        int dest = pq.top().first;
        int dist = pq.top().second;
        pq.pop();
        
        if(visit[dest] == 2)
            continue;
        else{
            d[dest] = dist;
            visit[dest] = 2;
            
            for(int i=0; i<g[dest].size(); i++){
                if(visit[g[dest][i].first] != 2){
                    visit[g[dest][i].first] = 1;
                    pq.push(make_pair(g[dest][i].first, d[dest] + g[dest][i].second));
                }
            }
        }
    }
}
int solution(int N, vector<vector<int> > road, int K) {
    int answer = 0;

    // 주어진 정보를 이용해 그래프 만들기.
    vector<vector<pair<int, int>>> g(N+1, vector<pair<int, int>>());
    for(int i=0; i<road.size(); i++){
        int source = road[i][0];
        int dest = road[i][1];
        int w = road[i][2];
        g[source].push_back(make_pair(dest, w));
        g[dest].push_back(make_pair(source, w));
    }
    
    // dijkstra 이용 시작점부터 최단경로 구하기.
    vector<int> d(N+1, -1);
    dijkstra(g, d, N);

    for(int i=1; i<=N; i++){
        if(d[i] <= K)
            answer++;
    }
    return answer;
}
