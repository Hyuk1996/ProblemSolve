#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 987654321;

void floydWarshall(vector<vector<int>>& dp, int n) {
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (i == j) {
					continue;
				}
				if (dp[i][k] == INF || dp[k][j] == INF) {
					continue;
				}
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
			}
		}
	}
}
void input(int& n, int& m, vector<vector<int>>& graph) {
	cin >> n >> m;
	graph.assign(n + 1, vector<int>(n + 1, INF));
	int a, b, c;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b >> c;
		graph[a][b] = min(graph[a][b], c);
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	vector<vector<int>> graph;
	input(n, m, graph);

	floydWarshall(graph, n);
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (graph[i][j] == INF) {
				cout << 0 << ' ';
			}
			else {
				cout << graph[i][j] << ' ';
			}
		}
		cout << '\n';
	}
	return 0;
}
