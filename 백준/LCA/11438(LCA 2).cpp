#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int lca(vector<int>& depth, vector<vector<int>>& parent, int a, int b) {
	//a, b node의 depth 맞춰주기
	if (depth[a] > depth[b]) {
		swap(a, b);
	}
	for (int i = parent.size() - 1; i >= 0; --i) {
		if (depth[b] - depth[a] >= (1 << i)) {
			b = parent[i][b];
		}
	}
	if (a == b) return a;

	//LCA 구하기
	for (int i = parent.size() - 1; i >= 0; --i) {
		if (parent[i][a] != parent[i][b]) {
			a = parent[i][a];
			b = parent[i][b];
		}
	}
	return parent[0][a];
}
void dfs(vector<vector<int>>& graph, int v, int d, vector<bool>& isVisited, vector<int>& depth, vector<vector<int>>& parent) {
	isVisited[v] = true;
	depth[v] = d;
	for (int i = 0; i < graph[v].size(); ++i) {
		int adjV = graph[v][i];
		if (isVisited[adjV]) {
			continue;
		}
		parent[0][adjV] = v;
		dfs(graph, adjV, d + 1, isVisited, depth, parent);
	}
}
void getInfo(int N, vector<vector<int>>& graph, vector<int>& depth, vector<vector<int>>& parent) {
	int height = 1;
	int power = 0;
	while (height < N) {
		height *= 2;
		power++;
	}

	depth.assign(N + 1, 0);
	parent.assign(power + 1, vector<int>(N+1, 0));
	vector<bool> isVisited(N + 1, false);
	dfs(graph, 1, 0, isVisited, depth, parent);

	for (int i = 1; i < parent.size(); ++i) {
		for (int j = 1; j <= N; ++j) {
			parent[i][j] = parent[i - 1][parent[i - 1][j]];
		}
	}
}
void input(int& N, vector<vector<int>>& graph) {
	cin >> N;
	graph.assign(N + 1, vector<int>());
	int u, v;
	for (int i = 0; i < N - 1; ++i) {
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int N;
	vector<vector<int>> graph;
	input(N, graph);

	vector<int> depth;
	vector<vector<int>> parent;
	getInfo(N, graph, depth, parent);


	int M;
	cin >> M;
	int a, b;
	vector<int> answers(M, 0);
	for (int i = 0; i < M; ++i) {
		cin >> a >> b;
		answers[i] = lca(depth, parent, a, b);
	}

	for (int i = 0; i < M; ++i) {
		cout << answers[i] << '\n';
	}
	return 0;
}
