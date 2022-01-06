#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int getRangeMax(vector<int>& rainIndexTree, int left, int right) {
	left += rainIndexTree.size() / 2;
	right += rainIndexTree.size() / 2;
	int maxRain = 0;
	while (left <= right) {
		if (left % 2 == 1) {
			maxRain = max(maxRain, rainIndexTree[left]);
		}
		if (right % 2 == 0) {
			maxRain = max(maxRain, rainIndexTree[right]);
		}

		left = (left + 1) / 2;
		right = (right - 1) / 2;
	}
	return maxRain;
}
int getYearIdx(vector<int>& years, int key) {
	// 동일한 값이 있으면 해당 값의 index, 없으면 상한값의 index return

	int lo = -1;
	int hi = years.size() - 1;
	while (lo + 1 < hi) {
		int mid = lo + (hi - lo) / 2;
		if (years[mid] >= key) {
			hi = mid;
		}
		else {
			lo = mid;
		}
	}

	if (years[hi] < key) {
		return years.size();
	}
	return hi;
}
int solve(vector<int>& rainIndexTree, vector<int>& years, int y, int x) {
	
	// Y, X 존재하는지 확인
	int yIdx = getYearIdx(years, y);
	int xIdx = getYearIdx(years, x);
	
	bool existY = (yIdx < years.size() && years[yIdx] == y);
	bool existX = (xIdx < years.size() && years[xIdx] == x);

	
	// Y < Z < X를 만족하는 최대 강수량 구하기
	int rangeMax;
	int nextYIdx = getYearIdx(years, y + 1);
	if (nextYIdx >= years.size()) {
		rangeMax = 0;
	}
	else {
		rangeMax = getRangeMax(rainIndexTree, nextYIdx, xIdx - 1);
	}
	
	// 구한 정보들 이용해 결과 반환
	int startIdx = rainIndexTree.size() / 2;
	if (existY && existX && rainIndexTree[startIdx + xIdx] > rainIndexTree[startIdx + yIdx]) {
		return 1;
	}
	else if (existX && rangeMax >= rainIndexTree[startIdx + xIdx]) {
		return 1;
	}
	else if (existY && rangeMax >= rainIndexTree[startIdx + yIdx]) {
		return 1;
	}
	else if (existY && existX && xIdx - yIdx == x - y) {
		return 0;
	}
	else {
		return 2;
	}
}
void makeIndexTree(vector<int>& rainIndexTree, vector<int>& rains) {
	int startIdx = 1;
	while (startIdx < rains.size()) {
		startIdx *= 2;
	}
	rainIndexTree.assign(startIdx * 2, 0);
	for (int i = 0; i < rains.size(); ++i) {
		rainIndexTree[i + startIdx] = rains[i];
	}
	for (int i = startIdx - 1; i > 0; --i) {
		rainIndexTree[i] = max(rainIndexTree[i * 2], rainIndexTree[i * 2 + 1]);
	}
}
void input(int& n, vector<int>& years, vector<int>& rains) {
	cin >> n;
	years.assign(n, 0);
	rains.assign(n, 0);
	for (int i = 0; i < n; ++i) {
		cin >> years[i] >> rains[i];
	}
}
int main() {
	int n;
	vector<int> years;
	vector<int> rains;
	input(n, years, rains);

	vector<int> rainIndexTree;
	makeIndexTree(rainIndexTree, rains);

	int m;
	cin >> m;
	vector<string> answers(m, "");
	for (int i = 0; i < m; ++i) {
		int y, x;
		cin >> y >> x;
		int state = solve(rainIndexTree, years, y, x);

		if (state == 0) {
			answers[i] = "true";
		}
		else if (state == 1) {
			answers[i] = "false";
		}
		else {
			answers[i] = "maybe";
		}
	}

	for (int i = 0; i < m; ++i) {
		cout << answers[i] << '\n';
	}
	return 0;
}
