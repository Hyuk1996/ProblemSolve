#include <iostream>
#include <vector>
using namespace std;

void travelGraph(vector<vector<int>>& graph, int v, vector<bool>& visit, vector<int>& visitCnt, int& cnt) {
	visit[v] = true;
	visitCnt[v]++;
	cnt++;
	for (int i = 0; i < graph[v].size(); ++i) {
		int adjV = graph[v][i];
		if (!visit[adjV]) {
			travelGraph(graph, graph[v][i], visit, visitCnt, cnt);
		}
	}
}
int solve(int N, vector<vector<int>>& graph) {
	vector<int> visitCnt(N + 1, 0);
	for (int i = 1; i <= N; ++i) {
		int tallerCnt = 0;
		vector<bool> check(N + 1, false);
		travelGraph(graph, i, check, visitCnt, tallerCnt);
		visitCnt[i] += tallerCnt - 1;
	}

	int answer = 0;
	for (int i = 1; i <= N; ++i) {
		if (visitCnt[i] == N) {
			answer++;
		}
	}
	return answer;
}
void input(int& N, int& M, vector<vector<int>>& graph) {
	cin >> N >> M;
	graph.assign(N + 1, vector<int>());
	for (int i = 0; i < M; ++i) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int N, M;
	vector<vector<int>> graph;
	input(N, M, graph);

	int answer = solve(N, graph);

	cout << answer;
	return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 987654321;

void floydWarshall(vector<vector<int>>& graph, int N) {
	for (int k = 1; k <= N; ++k) {
		for (int i = 1; i <= N; ++i) {
			if (i == k) {
				continue;
			}
			for (int j = 1; j <= N; ++j) {
				if (graph[i][k] == INF || graph[k][j] == INF) {
					continue;
				}
				graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
			}
		}
	}
}
void input(int& N, int& M, vector<vector<int>>& graph) {
	cin >> N >> M;
	graph.assign(N + 1, vector<int>(N + 1, INF));
	int a, b;
	for (int i = 0; i < M; ++i) {
		cin >> a >> b;
		graph[a][b] = 0;
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int N, M;
	vector<vector<int>> graph;
	input(N, M, graph);

	floydWarshall(graph, N);

	int answer = 0;
	int cnt;
	for (int i = 1; i <= N; ++i) {
		cnt = 0;
		for (int j = 1; j <= N; ++j) {
			if (graph[i][j] == 0) {
				cnt++;
			}
			if (graph[j][i] == 0) {
				cnt++;
			}
		}
		if (cnt == N - 1) {
			answer++;
		}
	}
	cout << answer;
	return 0;
}
