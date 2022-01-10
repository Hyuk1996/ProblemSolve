#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int INF = 1000001;
struct disjointSet {
	vector<int> parent;
	vector<int> dist;   // dist[i] 는 i node 와 i node의 root node와의 차이, ex) dist[i] = 3 이면 root = i + 3

	disjointSet(int n) :parent(n), dist(n, 0) {
		for (int i = 0; i < n; ++i) {
			parent[i] = i;
		}
	}

	int find(int u) {
		if (parent[u] == u) {
			return u;
		}
		int p = find(parent[u]);
		dist[u] += dist[parent[u]];
		return parent[u] = p;
	}

	void merge(int a, int b, int w) {
		int roota = find(a);
		int rootb = find(b);

		if (roota == rootb) {
			return;
		}

		dist[rootb] = dist[a] + w - dist[b];
		parent[rootb] = roota;
		return;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	while (true) {
		int N, M;
		cin >> N >> M;
		if (N == 0 && M == 0) {
			break;
		}

		disjointSet set(N + 1);
		while (M--) {
			char cmd;
			int a, b, w;
			cin >> cmd;
			if (cmd == '!') {
				cin >> a >> b >> w;
				set.merge(a, b, w);
			}
			else {
				cin >> a >> b;
				if (set.find(a) != set.find(b)) {
					cout << "UNKNOWN\n";
				}
				else {
					cout << set.dist[b] - set.dist[a] << '\n';
				}
			}
		}
	}

	return 0;
}
