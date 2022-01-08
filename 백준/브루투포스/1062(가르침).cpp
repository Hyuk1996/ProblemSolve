#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int readableWord(vector<int>& alpabet, vector<vector<int>>& words) {
	int wordCnt = 0;
	for (int i = 0; i < words.size(); ++i) {
		bool possible = true;
		for (int j = 0; j < 26; ++j) {
			if (words[i][j] == 1 && alpabet[j] == 0) {
				possible = false;
				break;
			}
		}
		if (possible) {
			wordCnt++;
		}
	}
	return wordCnt;
}
void getCombination(vector<int>& alpabet, int idx, int curK, int K, vector<vector<int>>& words, int& answer) {
	if (curK == K) {
		answer = max(answer, readableWord(alpabet, words));
		return;
	}

	for (int i = idx; i < 26; ++i) {
		if (alpabet[i] == 0) {
			alpabet[i] = 1;
			getCombination(alpabet, i + 1, curK + 1, K, words, answer);
			alpabet[i] = 0;
		}
	}
}
int solve(int N, int K, vector<vector<int>>& words) {
	if (K < 5) {
		return 0;
	}

	vector<int> alpabet(26, 0);
	alpabet['a' - 'a'] = 1;
	alpabet['n' - 'a'] = 1;
	alpabet['t' - 'a'] = 1;
	alpabet['i' - 'a'] = 1;
	alpabet['c' - 'a'] = 1;
	K -= 5;

	int answer = 0;
	getCombination(alpabet, 0, 0, K, words, answer);
	return answer;
}
void input(int& N, int& K, vector<vector<int>>& words) {
	cin >> N >> K;
	words.assign(N, vector<int>(26, 0));
	for (int i = 0; i < N; ++i) {
		string word;
		cin >> word;
		for (int j = 4; j < (word.size() - 4); ++j) {
			words[i][word[j] - 'a'] = 1;
		}
	}
}
int main() {
	int N, K;
	vector<vector<int>> words;
	input(N, K, words);

	int answer = solve(N, K, words);
	cout << answer;
	return 0;
}
