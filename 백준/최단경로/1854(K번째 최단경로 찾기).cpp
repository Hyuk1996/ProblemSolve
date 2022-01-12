#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int INF = 987654321;
struct cmp {
	bool operator() (const pair<int, int>& a, const pair<int, int>& b) {
		return a.second > b.second;
	}
};

void dijkstra(vector<vector<pair<int, int>>>& graph, int n, int k, vector<int>& answers) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
	vector<priority_queue<int>> dists(n + 1, priority_queue<int>()); // k번째 최단경로를 구하기위한 배열

	pq.push(make_pair(1, 0));
	dists[1].push(0);
	while (!pq.empty()) {
		int v = pq.top().first;
		int dist = pq.top().second;
		pq.pop();
		
		for (int i = 0; i < graph[v].size(); ++i) {
			int adjV = graph[v][i].first;
			int weight = graph[v][i].second;

			if (dists[adjV].size() < k) {
				dists[adjV].push(dist + weight);
				pq.push(make_pair(adjV, dist + weight));
			}
			else {
				int tmp = dists[adjV].top();
				if (tmp > dist + weight) {
					dists[adjV].pop();
					dists[adjV].push(dist + weight);
					pq.push(make_pair(adjV, dist + weight));
				}
			}
		}
	}


	for (int i = 1; i <= n; ++i) {
		if (dists[i].size() < k) {
			answers.push_back(-1);
		}
		else {
			answers.push_back(dists[i].top());
		}
	}
}
void input(int& n, int& m, int& k, vector<vector<pair<int, int>>>& graph) {
	cin >> n >> m >> k;
	graph.assign(n + 1, vector<pair<int, int>>());
	int a, b, c;
	for (int i = 0; i < m; ++i) {
		cin >> a >> b >> c;
		graph[a].push_back(make_pair(b, c));
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m, k;
	vector<vector<pair<int, int>>> graph;
	input(n, m, k, graph);

	vector<int> answers;
	dijkstra(graph, n, k, answers);


	for (int i = 0; i < answers.size(); ++i) {
		cout << answers[i] << '\n';
	}
	return 0;
}
