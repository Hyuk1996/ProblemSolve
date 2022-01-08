#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool checkWord(string& word, int L) {
	int vowelCnt = 0;
	for (int i = 0; i < L; ++i) {
		if (word[i] == 'a' || word[i] == 'e' || word[i] == 'i' || word[i] == 'o' || word[i] == 'u') {
			vowelCnt++;
		}
	}

	if (vowelCnt >= 1) {
		if (L - vowelCnt >= 2) {
			return true;
		}
	}
	return false;
}
void getCombi(vector<char>& chars, int idx, string curWord, int L, vector<string>& answers) {
	if (curWord.size() == L) {
		if (checkWord(curWord, L)) {
			answers.push_back(curWord);
		}
		return;
	}
	for (int i = idx; i < chars.size(); ++i) {
		getCombi(chars, i + 1, curWord + chars[i], L, answers);
	}
}
void input(int& L, int& C, vector<char>& chars) {
	cin >> L >> C;
	chars.assign(C, 0);
	for (int i = 0; i < C; ++i) {
		cin >> chars[i];
	}
	sort(chars.begin(), chars.end());
}
int main() {
	int L, C;
	vector<char> chars;
	input(L, C, chars);

	vector<string> answers;
	getCombi(chars, 0, "", L, answers);

	for (int i = 0; i < answers.size(); ++i) {
		cout << answers[i] << '\n';
	}
	return 0;
}
