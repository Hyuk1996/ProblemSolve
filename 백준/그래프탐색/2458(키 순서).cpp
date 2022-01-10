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
