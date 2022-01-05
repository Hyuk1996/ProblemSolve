#include <iostream>
#include <vector>
using namespace std;

void postOrder(vector<vector<int>>& tree, int v) {
	for (int i = 0; i < tree[v].size(); ++i) {
		if (tree[v][i] == -1) {
			continue;
		}
		postOrder(tree, tree[v][i]);
	}
	cout << char(v + 'A');
}
void inOrder(vector<vector<int>>& tree, int v) {
	if (tree[v][0] != -1) {
		inOrder(tree, tree[v][0]);
	}
	cout << (char)(v + 'A');
	if (tree[v][1] != -1) {
		inOrder(tree, tree[v][1]);
	}
}
void preOrder(vector<vector<int>>& tree, int v) {
	cout << (char)(v + 'A');
	for (int i = 0; i < tree[v].size(); ++i) {
		if (tree[v][i] == -1) {
			continue;
		}
		preOrder(tree, tree[v][i]);
	}
}
void input(int& N, vector<vector<int>>& tree) {
	cin >> N;
	tree.assign(N, vector<int>());
	for (int i = 0; i < N; ++i) {
		char parent, left, right;
		cin >> parent >> left >> right;
		if (left == '.') {
			tree[parent - 'A'].push_back(-1);
		}
		else {
			tree[parent - 'A'].push_back(left - 'A');
		}

		if (right == '.') {
			tree[parent - 'A'].push_back(-1);
		}
		else {
			tree[parent - 'A'].push_back(right - 'A');
		}
	}
}
int main() {
	int N;
	vector<vector<int>> tree;
	input(N, tree);

	preOrder(tree, 0);
	cout << '\n';
	inOrder(tree, 0);
	cout << '\n';
	postOrder(tree, 0);
	return 0;
}
