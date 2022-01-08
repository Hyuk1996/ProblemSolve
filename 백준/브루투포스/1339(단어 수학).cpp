#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int calculate(vector<string>& words, vector<char>& alphabet, vector<int>& nums) {
	vector<int> translate(26, 0);
	for (int i = 0; i < alphabet.size(); ++i) {
		translate[alphabet[i] - 'A'] = nums[i];
	}
	
	int sum = 0;
	for (int i = 0; i < words.size(); ++i) {
		int num = 0;
		for (int j = 0; j < words[i].size(); ++j) {
			num = (num * 10) + translate[words[i][j] - 'A'];
		}
		sum += num;
	}
	return sum;
}
void getPermutation(vector<char>& alphabet, int depth, vector<int>& nums, vector<bool>& visit, vector<string>& words, int& answer) {
	if (depth == alphabet.size()) {
		answer = max(answer, calculate(words, alphabet, nums));
		return;
	}

	for (int i = 10 - alphabet.size() ; i < 10; ++i) {
		if (!visit[i]) {
			visit[i] = true;
			nums.push_back(i);
			getPermutation(alphabet, depth + 1, nums, visit, words, answer);
			nums.pop_back();
			visit[i] = false;
		}
	}
}
void input(int& N, vector<string>& words, vector<char>& alpabet) {
	cin >> N;
	words.assign(N, "");

	vector<bool> check(26, false);
	for (int i = 0; i < N; ++i) {
		cin >> words[i];
		
		for (int j = 0; j < words[i].size(); ++j) {
			if (!check[words[i][j] - 'A']) {
				check[words[i][j] - 'A'] = true;
				alpabet.push_back(words[i][j]);
			}
		}
	}
}
int main() {
	int N;
	vector<string> words;
	vector<char> alphabet;
	input(N, words, alphabet);

	int answer = 0;
	vector<bool> visit(10, false);
	vector<int> nums; //알파벳에 대응되는 숫자를 넣을 벡터
	getPermutation(alphabet, 0, nums, visit, words, answer);

	cout << answer;
	return 0;
}
