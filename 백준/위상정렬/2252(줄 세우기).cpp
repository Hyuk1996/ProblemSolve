#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void topologicalSort(vector<vector<int>>& dag, vector<int>& inDegrees, vector<int>& answers) {
	queue<int> q;
	for (int i = 1; i < inDegrees.size(); ++i) {
		if (inDegrees[i] == 0) {
			q.push(i);
		}
	}
	while (!q.empty()) {
		int v = q.front();
		q.pop();

		answers.push_back(v);
		for (int i = 0; i < dag[v].size(); ++i) {
			inDegrees[dag[v][i]]--;
			if (inDegrees[dag[v][i]] == 0) {
				q.push(dag[v][i]);
			}
		}
	}
}
void input(int& N, int& M, vector<vector<int>>& dag, vector<int>& inDegrees) {
	cin >> N >> M;
	dag.assign(N+1, vector<int>());
	inDegrees.assign(N + 1, 0);
	for (int i = 0; i < M; ++i) {
		int A, B;
		cin >> A >> B;
		dag[A].push_back(B);
		inDegrees[B]++;
	}
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N, M;
	vector<vector<int>> dag;
	vector<int> inDegrees;
	input(N, M, dag, inDegrees);

	vector<int> answers;
	topologicalSort(dag, inDegrees, answers);
	
	for (int i = 0; i < N; ++i) {
		cout << answers[i] << ' ';
	}
	return 0;
}
