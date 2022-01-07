#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
using namespace std;

void getPermutation(vector<int>& cards, vector<bool>& visit, int curDepth, int k, string curNum, unordered_set<string>& nums) {
	if (curDepth == k) {
		nums.insert(curNum);
		return;
	}
	for (int i = 0; i < cards.size(); ++i) {
		if (!visit[i]) {
			visit[i] = true;
			getPermutation(cards, visit, curDepth + 1, k, curNum + to_string(cards[i]), nums);
			visit[i] = false;
		}
	}
}
void input(int& n, int& k, vector<int>& cards) {
	cin >> n >> k;
	cards.assign(n, 0);
	for (int i = 0; i < n; ++i) {
		cin >> cards[i];
	}
}
int main() {
	int n, k;
	vector<int> cards;
	input(n, k, cards);

	unordered_set<string> nums;
	vector<bool> visit(n, false);
	getPermutation(cards, visit, 0, k, "", nums);

	cout << (int)nums.size();
	return 0;
}
