#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int n, m, t, s, g, h;
const int INF = 987654321;
struct cmp {
    bool operator() (const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }
};

bool check(vector<vector<int>>& parent, int start) {
    vector<bool> isVisited(n + 1, false);
    queue<int> q;

    q.push(start);
    isVisited[start] = true;
    while(!q.empty()) {
        int v = q.front();
        q.pop();

        for(int i = 0; i < parent[v].size(); ++i) {
            int nextV = parent[v][i];

            if(v == g) {
                if(nextV == h) {
                    return true;
                }
            }
            if(v == h) {
                if(nextV == g) {
                    return true;
                }
            }

            if(!isVisited[nextV]) {
                q.push(nextV);
                isVisited[nextV] = true;
            }
        }
    }
    return false;
}
void solve(vector<vector<pair<int, int>>>& graph, vector<int>& goals, vector<int>& answer) {
    //다익스트라
    vector<int> dists(n + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
    vector<vector<int>> parent(n + 1);

    dists[s] = 0;
    pq.push({s, dists[s]});
    while(!pq.empty()) {
        int curV = pq.top().first;
        int curDist = pq.top().second;
        pq.pop();

        if(curDist > dists[curV]) {
            continue;
        }
        for(int i = 0; i <graph[curV].size(); ++i) {
            int nextV = graph[curV][i].first;
            int weight = graph[curV][i].second;

            if(dists[curV] + weight < dists[nextV]) {
                dists[nextV] = dists[curV] + weight;
                pq.push({nextV, dists[nextV]});

                parent[nextV].clear();
                parent[nextV].push_back(curV);
            } else if(dists[curV] + weight == dists[nextV]) {
                parent[nextV].push_back(curV);
            }
        }
    }

    //Parent 정보 이용해 가능한 목적지 구하기.
    for(int i = 0; i < t; ++i) {
        if(check(parent, goals[i])) {
            answer.push_back(goals[i]);
        }
    }
    sort(answer.begin(), answer.end());
}
void input(vector<vector<pair<int, int>>>& graph, vector<int>& goals) {
    cin >> n >> m >> t;
    cin >> s >> g >> h;

    //그래프 만들기
    int a, b, d;
    graph.assign(n + 1, vector<pair<int, int>>());
    for(int i = 0; i < m; ++i) {
        cin >> a >> b >> d;
        graph[a].push_back(make_pair(b, d));
        graph[b].push_back(make_pair(a, d));
    }

    //목적지 후보
    goals.assign(t, 0);
    for(int i = 0; i < t; ++i) {
        cin >> goals[i];
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<vector<int>> answers;
    int TC;
    cin >> TC;
    while(TC--) {
        vector<vector<pair<int, int>>> graph;
        vector<int> goals;
        input(graph, goals);

        vector<int> answer;
        solve(graph, goals, answer);

        answers.push_back(answer);
    }

    for(int i = 0; i < answers.size(); ++i) {
        for(int j = 0; j < answers[i].size(); ++j) {
            cout << answers[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}

//역추적 이용하지 않고 3번의 다익스트라를 활용한 풀이
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int n, m, t, s, g, h;
int cost;
const int INF = 987654321;
struct cmp {
    bool operator() (const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    }
};

void dijkstra(vector<vector<pair<int, int>>>& graph, int startV, vector<int>& dists) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;

    dists[startV] = 0;
    pq.push({startV, dists[startV]});
    while(!pq.empty()) {
        int curV = pq.top().first;
        int curDist = pq.top().second;
        pq.pop();

        if(curDist > dists[curV]) {
            continue;
        }
        for(int i = 0; i < graph[curV].size(); ++i) {
            int adjV = graph[curV][i].first;
            int weight = graph[curV][i].second;

            if(dists[curV] + weight < dists[adjV]) {
                dists[adjV] = dists[curV] + weight;
                pq.push({adjV, dists[adjV]});
            }
        }
    }
}
void solve(vector<vector<pair<int, int>>>& graph, vector<int>& goals, vector<int>& answer) {

    vector<int> distFromS(n + 1, INF);
    dijkstra(graph, s, distFromS);

    vector<int> distFromG(n + 1, INF);
    dijkstra(graph, g, distFromG);

    vector<int> distFromH(n + 1, INF);
    dijkstra(graph, h, distFromH);

    //목적지가 gh 도로를 포함하는지 확인
    for(int i = 0; i < t; ++i) {
        int shortest = distFromS[goals[i]];
        int tmpPath = distFromS[g] + cost + distFromH[goals[i]];
        int tmpPath2 = distFromS[h] + cost + distFromG[goals[i]];

        if((shortest == tmpPath) || (shortest == tmpPath2)) {
            answer.push_back(goals[i]);
        }
    }
    sort(answer.begin(), answer.end());
}
void input(vector<vector<pair<int, int>>>& graph, vector<int>& goals) {
    cin >> n >> m >> t;
    cin >> s >> g >> h;

    graph.assign(n + 1, vector<pair<int, int>>());
    int a, b, d;
    for(int i = 0; i < m; ++i) {
        cin >> a >> b >> d;
        graph[a].push_back({b, d});
        graph[b].push_back({a, d});

        if(a == g && b == h) {
            cost = d;
        }
        if(a == h && b == g) {
            cost = d;
        }
    }

    goals.assign(t, 0);
    for(int i = 0; i < t; ++i) {
        cin >> goals[i];
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<vector<int>> answers;
    int testCase;
    cin >> testCase;
    while(testCase--) {
        vector<vector<pair<int, int>>> graph;
        vector<int> goals;
        input(graph, goals);

        vector<int> answer;
        solve(graph, goals, answer);

        answers.push_back(answer);
    }

    for(int i = 0; i < answers.size(); ++i) {
        for(int j = 0; j < answers[i].size(); ++j) {
            cout << answers[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}
