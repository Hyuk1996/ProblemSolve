#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

int binarySearch(vector<int>& compress, int key) {
	int lo = 0;
	int hi = compress.size();
	while (lo + 1 < hi) {
		int mid = lo + (hi - lo) / 2;
		if (compress[mid] <= key) {
			lo = mid;
		}
		else {
			hi = mid;
		}
	}
	return lo;
}
void updateIndexTree(vector<int>& indexTree, int p) {
	p += indexTree.size() / 2;
	indexTree[p] = 1;
	while (p > 1) {
		p = p / 2;
		indexTree[p] = indexTree[p * 2] + indexTree[p * 2 + 1];
	}
}
int rangeSum(vector<int>& indexTree, int right) {
	int startIdx = indexTree.size() / 2;
	int left = startIdx;
	right += startIdx;
	int sum = 0;
	while (left <= right) {
		if (left % 2 == 1) {
			sum += indexTree[left];
		}
		if (right % 2 == 0) {
			sum += indexTree[right];
		}

		left = (left + 1) / 2;
		right = (right - 1) / 2;
	}
	return sum;
}
void makeIndexTree(vector<int>& indexTree, int N) {
	int startIdx = 1;
	while (startIdx < N) {
		startIdx *= 2;
	}
	indexTree.assign(startIdx * 2, 0);
}
void solve(int N, vector<int>& players, vector<int>& answers) {
	//좌표 압축하기.
	vector<int> compress(players);
	sort(compress.begin(), compress.end());
	/*
	unordered_map<int, int> dict; //압축정보 저장
	for (int i = 0; i < compress.size(); ++i) {
		dict[compress[i]] = i;
	}*/

	//indexTree 만들기
	vector<int> indexTree;
	makeIndexTree(indexTree, N);

	//각 선수의 최선의 등수 구하기
	for (int i = 0; i < N; ++i) {
		//int compressIdx = dict[players[i]];
		int compressIdx = binarySearch(compress, players[i]);
		
		// 자신보다 못한 선수 구하기
		int notGoodPlayerCnt = rangeSum(indexTree, compressIdx);
		answers.push_back((i + 1) - notGoodPlayerCnt);
		updateIndexTree(indexTree, compressIdx);
	}
}
void input(int& N, vector<int>& players) {
	cin >> N;
	players.assign(N, 0);
	for (int i = 0; i < N; ++i) {
		cin >> players[i];
	}
}
int main() {
	int N;
	vector<int> players;
	input(N, players);

	vector<int> answers;
	solve(N, players, answers);

	for (int i = 0; i < answers.size(); ++i) {
		cout << answers[i] << '\n';
	}
	return 0;
}
