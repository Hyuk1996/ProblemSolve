#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct disjointSet {
	vector<int> parent;

	disjointSet(int n): parent(n+1) {
		for (int i = 0; i <= n; ++i) {
			parent[i] = i;
		}
	}

	int find(int u) {
		if (parent[u] == u) {
			return u;
		}
		return parent[u] = find(parent[u]); //경로압축
	}

	void merge(int u, int v) {
		u = find(u);
		v = find(v);
		if (u == v) {
			return;
		}
		parent[u] = v;
	}
};

int main() {
	int n, m;
	cin >> n >> m;
	disjointSet set(n);

	vector<string> answers;
	while (m--) {
		int op, a, b;
		cin >> op >> a >> b;
		if (op == 0) {
			set.merge(a, b);
		}
		else {
			if (set.find(a) == set.find(b)) {
				answers.push_back("YES");
			}
			else {
				answers.push_back("NO");
			}
		}
	}

	for (int i = 0; i < answers.size(); ++i) {
		cout << answers[i] << '\n';
	}
	return 0;
}
