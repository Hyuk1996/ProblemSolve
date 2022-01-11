#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 987654321;
struct edge {
	int u;
	int v;
	int w;

	edge(int u, int v, int w) {
		this->u = u;
		this->v = v;
		this->w = w;
	}
};

bool bellmanFord(vector<edge>& edgeList, vector<long long>& dist, int N, int M) {
	dist[1] = 0;
	int from, to, weight;
	for (int i = 0; i < N - 1; ++i) {
		for (int j = 0; j < M; ++j) {
			from = edgeList[j].u;
			to = edgeList[j].v;
			weight = edgeList[j].w;

			if (dist[from] == INF) {
				continue;
			}
			dist[to] = min(dist[to], dist[from] + weight);
		}
	}

	bool isCycle = false;
	for (int i = 0; i < M; ++i) {
		from = edgeList[i].u;
		to = edgeList[i].v;
		weight = edgeList[i].w;

		if (dist[from] == INF) {
			continue;
		}
		if (dist[to] > dist[from] + weight) {
			isCycle = true;
			break;
		}
	}
	return isCycle;
}
void input(int& N, int& M, vector<edge>& edgeList) {
	cin >> N >> M;
	int A, B, C;
	for (int i = 0; i < M; ++i) {
		cin >> A >> B >> C;
		edgeList.push_back(edge(A, B, C));
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int N, M;
	vector<edge> edgeList; 
	input(N, M, edgeList);

	vector<long long> dist(N + 1, INF);
	bool isCycle = bellmanFord(edgeList, dist, N, M);
	
	if (isCycle) {
		cout << -1;
	}
	else {
		for (int i = 2; i <= N; ++i) {
			if (dist[i] == INF) {
				cout << -1 << '\n';
			}
			else {
				cout << dist[i] << '\n';
			}
		}
	}
	return 0;
}
