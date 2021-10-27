#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int INF = 1000000001;
void BFS(vector<vector<pair<int, int>>>& g, int start, vector<vector<int>>& USADOs){
    vector<bool> visit(g.size(), 0);
    visit[start] = true;
    USADOs[start][start] = 0;
    queue<pair<int, int>> q;
    q.push(make_pair(start, INF));

    while(!q.empty()){
        int cur_v = q.front().first;
        int cur_USADO = q.front().second;
        q.pop();

        for(int i=0; i<g[cur_v].size(); i++){
            int next_v = g[cur_v][i].first;
            int next_USADO = g[cur_v][i].second;
            if(!visit[next_v]){
                visit[next_v] = true;
                next_USADO = min(next_USADO, cur_USADO);
                USADOs[start][next_v] = next_USADO;
                q.push(make_pair(next_v, next_USADO));
            }
        }
    }
}
int main(){
    // 입력.
    int N, Q;
    cin >> N >> Q;
    vector<vector<pair<int, int>>> g(N+1, vector<pair<int, int>>());
    for(int i=0; i<N-1; i++){
        int p, q, r;
        cin >> p >> q >> r;
        g[p].push_back(make_pair(q, r));
        g[q].push_back(make_pair(p, r));
    }

    // 동영상 끼리의 USADO 구하기.
    vector<vector<int>> USADOs(N+1, vector<int>(N+1, INF));
    for(int i=1; i<=N; i++){
        BFS(g, i, USADOs);
    }

    // query 응답.
    vector<int> answers;
    while(Q--){
        int k, v;
        cin >> k >> v;
        int ans = 0;
        for(int i=1; i<=N; i++)
            if(k <= USADOs[v][i])
                ans++;

        answers.push_back(ans);
    }

    // 정답 출력.
    for(int i=0; i<answers.size(); i++)
        cout << answers[i] << '\n';
    return 0;
}


// DFS 이용 풀이.
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int INF = 1000000001;

void DFS(vector<vector<pair<int, int>>>& g, int start, int USADO, vector<int>& USADOs, vector<bool>& visit){
    visit[start] = true;
    USADOs[start] = USADO;

    for(int i=0; i<g[start].size(); i++){
        int next_v = g[start][i].first;
        int next_USADO = g[start][i].second;
        if(!visit[next_v]){
            next_USADO = min(USADO, next_USADO);
            DFS(g, next_v, next_USADO, USADOs, visit);
        }
    }
}
int main(){
    // 입력.
    int N, Q;
    cin >> N >> Q;
    vector<vector<pair<int, int>>> g(N+1, vector<pair<int, int>>());
    for(int i=0; i<N-1; i++){
        int p, q, r;
        cin >> p >> q >> r;
        g[p].push_back(make_pair(q, r));
        g[q].push_back(make_pair(p, r));
    }

    // 동영상 끼리의 USADO 구하기.
    vector<vector<int>> USADOs(N+1, vector<int>(N+1, INF));
    for(int i=1; i<=N; i++){
        vector<bool> visit(N+1, 0);
        DFS(g, i, INF, USADOs[i], visit);
    }

    // query 응답.
    vector<int> answers;
    while(Q--){
        int k, v;
        cin >> k >> v;
        int ans = 0;
        for(int i=1; i<=N; i++) {
            if( i == v)
                continue;
            if (k <= USADOs[v][i])
                ans++;
        }

        answers.push_back(ans);
    }

    // 정답 출력.
    for(int i=0; i<answers.size(); i++)
        cout << answers[i] << '\n';
    return 0;
}
