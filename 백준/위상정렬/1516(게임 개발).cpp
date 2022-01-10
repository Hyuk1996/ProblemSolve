#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
	return a.second > b.second;
}
void topologicalSort(vector<vector<int>>& graph, vector<int>& inDegree, vector<int>& times, vector<int>& dist) {
	queue<int> q;
	for (int i = 1; i < inDegree.size(); ++i) {
		if (inDegree[i] == 0) {
			dist[i] = times[i];
			q.push(i);
		}
	}

	while (!q.empty()) {
		int v = q.front();
		q.pop();

		for (int i = 0; i < graph[v].size(); ++i) {
			int nextV = graph[v][i];
			int time = dist[v];
			dist[nextV] = max(dist[v] + times[nextV], dist[nextV]);
			inDegree[nextV]--;
			if (inDegree[nextV] == 0) {
				q.push(nextV);
			}
		}
	}
}
void input(int& N, vector<int>& times, vector<vector<int>>& graph, vector<int>& inDegree) {
	cin >> N;
	times.assign(N + 1, 0);
	graph.assign(N + 1, vector<int>());
	inDegree.assign(N + 1, 0);
	for (int i = 1; i <= N; ++i) {
		int time;
		cin >> time;
		times[i] = time;
		
		int v;
		while (true) {
			cin >> v;
			if (v == -1) {
				break;
			}
			graph[v].push_back(i);
			inDegree[i]++;
		}
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int N;
	vector<int> times;
	vector<vector<int>> graph;
	vector<int> inDegree;
	input(N, times, graph, inDegree);

	vector<int> dist(N + 1, 0);
	topologicalSort(graph, inDegree, times, dist);
	
	for (int i = 1; i <= N; ++i) {
		cout << dist[i] << '\n';
	}
	return 0;
}
