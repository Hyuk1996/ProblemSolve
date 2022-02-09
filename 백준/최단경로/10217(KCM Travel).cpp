#include <iostream>
#include <vector>
#include <string>
#include <queue>
#define INF 987654321
using namespace std;
int N, M, K;
struct Node {
    int v;
    int c, d;
    Node (int v, int c, int d) {
        this->v = v;
        this->c = c;
        this->d = d;
    }
};
struct cmp {
    bool operator() (const Node& a, const Node& b) {
        return a.d > b.d;
    }
};

void dijkstra(vector<vector<Node>>& graph, vector<vector<int>>& dp) {
    priority_queue<Node, vector<Node>, cmp> pq;

    dp[1][0] = 0;
    pq.push(Node(1, 0, 0));
    while(!pq.empty()) {
        int curV = pq.top().v;
        int curC = pq.top().c;
        int curD = pq.top().d;
        pq.pop();

        if(dp[curV][curC] < curD) {
            continue;
        }

        for(int i = 0; i < graph[curV].size(); ++i) {
            int nextV = graph[curV][i].v;
            int nextC = curC + graph[curV][i].c;
            int nextD = curD + graph[curV][i].d;

            if(nextC <= M && nextD < dp[nextV][nextC]) {
                dp[nextV][nextC] = nextD;
                pq.push(Node(nextV, nextC, nextD));

                //불필요한 시간 재설정
                for(int j = nextC + 1; j <= M; ++j) {
                    if(dp[nextV][j] < nextD) {
                        break;
                    }
                    dp[nextV][j] = nextD;
                }
            }
        }
    }
}
string solve(vector<vector<Node>>& graph) {
    vector<vector<int>> dp(N + 1, vector<int>(M + 1, INF));
    dijkstra(graph, dp);

    int answer = INF;
    for(int i = 1; i <= M; ++i) {
        answer = min(answer, dp[N][i]);
    }
    if(answer == INF) {
        return "Poor KCM";
    } else {
        return to_string(answer);
    }
}
void input(vector<vector<Node>>& graph) {
    cin >> N >> M >> K;

    graph.assign(N + 1, vector<Node>());
    int u, v, c, d;
    for(int i = 0; i <K; ++i) {
        cin >> u >> v >> c >> d;
        graph[u].push_back(Node(v, c, d));
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<string> answers;
    int TC;
    cin >> TC;
    while(TC--) {
        vector<vector<Node>> graph;
        input(graph);

        string answer = solve(graph);

        answers.push_back(answer);
    }

    for(int i = 0; i <answers.size(); ++i) {
        cout << answers[i] << '\n';
    }

    return 0;
}
