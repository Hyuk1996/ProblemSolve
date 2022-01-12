#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX = 987654321;
const int MIN = 0;
struct answer {
	int shortestEdge;
	int longestEdge;
	answer(int s, int l) {
		this->shortestEdge = s;
		this->longestEdge = l;
	}
};

answer lca(vector<int>& depth, vector<vector<int>>& parent, vector<vector<int>>& maxEdge, vector<vector<int>>& minEdge, int a, int b) {
	int shortestEdge = MAX;
	int longestEdge = MIN;
	
	// depth 맞추기
	if (depth[a] > depth[b]) {
		swap(a, b);
	}
	for (int i = parent.size() - 1; i >= 0; --i) {
		if (depth[b] - depth[a] >= (1 << i)) {
			shortestEdge = min(shortestEdge, minEdge[i][b]);
			longestEdge = max(longestEdge, maxEdge[i][b]);
			b = parent[i][b];
		}
	}

	if (a == b) {
		return answer(shortestEdge, longestEdge);
	}

	for (int i = parent.size() - 1; i >= 0; --i) {
		if (parent[i][a] != parent[i][b]) {
			shortestEdge = min(shortestEdge, minEdge[i][a]);
			longestEdge = max(longestEdge, maxEdge[i][a]);

			shortestEdge = min(shortestEdge, minEdge[i][b]);
			longestEdge = max(longestEdge, maxEdge[i][b]);

			a = parent[i][a];
			b = parent[i][b];
		}
	}
	
	shortestEdge = min(shortestEdge, minEdge[0][a]);
	longestEdge = max(longestEdge, maxEdge[0][a]);

	shortestEdge = min(shortestEdge, minEdge[0][b]);
	longestEdge = max(longestEdge, maxEdge[0][b]);
	return answer(shortestEdge, longestEdge);
}
void dfs(vector<vector<pair<int, int>>>& graph, int v, int d, vector<bool>& isVisited, vector<int>& depth, vector<vector<int>>& parent, vector<vector<int>>& maxEdge, vector<vector<int>>& minEdge) {
	isVisited[v] = true;
	depth[v] = d;
	for (int i = 0; i < graph[v].size(); ++i) {
		int adjV = graph[v][i].first;
		int weight = graph[v][i].second;
		if (isVisited[adjV]) {
			continue;
		}
		parent[0][adjV] = v;
		maxEdge[0][adjV] = weight;
		minEdge[0][adjV] = weight;
		dfs(graph, adjV, d + 1, isVisited, depth, parent, maxEdge, minEdge);
	}
}
void getInfo(int& N, vector<vector<pair<int, int>>>& graph, vector<int>& depth, vector<vector<int>>& parent, vector<vector<int>>& maxEdge, vector<vector<int>>& minEdge) {
	int height = 1;
	int power = 0;
	while (height < N) {
		height *= 2;
		power++;
	}

	depth.assign(N + 1, 0);
	parent.assign(power + 1, vector<int>(N + 1, 0));
	maxEdge.assign(power + 1, vector<int>(N + 1, MIN));
	minEdge.assign(power + 1, vector<int>(N + 1, MAX));

	vector<bool> isVisited(N + 1, false);
	dfs(graph, 1, 0, isVisited, depth, parent, maxEdge, minEdge);

	for (int i = 1; i <= power; ++i) {
		for (int j = 1; j <= N; ++j) {
			parent[i][j] = parent[i - 1][parent[i - 1][j]];
			maxEdge[i][j] = max(maxEdge[i - 1][j], maxEdge[i - 1][parent[i - 1][j]]);
			minEdge[i][j] = min(minEdge[i - 1][j], minEdge[i - 1][parent[i - 1][j]]);
		}
	}
}
void input(int& N, vector<vector<pair<int, int>>>& graph) {
	cin >> N;
	graph.assign(N + 1, vector<pair<int, int>>());
	int A, B, C;
	for (int i = 0; i < N - 1; ++i) {
		cin >> A >> B >> C;
		graph[A].push_back(make_pair(B, C));
		graph[B].push_back(make_pair(A, C));
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int N;
	vector<vector<pair<int, int>>> graph;
	input(N, graph);

	vector<int> depth;
	vector<vector<int>> parent;
	vector<vector<int>> maxEdge;
	vector<vector<int>> minEdge;
	getInfo(N, graph, depth, parent, maxEdge, minEdge);


	int K, D, E;
	cin >> K;
	vector<answer> answers;
	for (int i = 0; i < K; ++i) {
		cin >> D >> E;
		answers.push_back(lca(depth, parent, maxEdge, minEdge, D, E));
	}

	for (int i = 0; i < K; ++i) {
		cout << answers[i].shortestEdge << ' ' << answers[i].longestEdge << '\n';
	}
	return 0;
}
