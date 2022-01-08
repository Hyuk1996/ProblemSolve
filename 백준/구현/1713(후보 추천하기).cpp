#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX_STUDENT = 101;
struct student {
	int id;
	int recommendCnt = 1;
	int date;
	student(int id, int date) {
		this->id = id;
		this->date = date;
	}
};

bool cmp(const student& a, const student& b) {
	return a.id < b.id;
}
int main() {
	int N, totalRecomment;
	cin >> N >> totalRecomment;

	vector<student> candidates;
	vector<bool> check(MAX_STUDENT, false);	
	int curDay = 0;
	while (totalRecomment--) {
		int studentId;
		cin >> studentId;

		if (check[studentId]) {
			for (int i = 0; i < candidates.size(); ++i) {
				if (candidates[i].id == studentId) {
					candidates[i].recommendCnt++;
				}
			}
		}
		else {
			if (candidates.size() == N) {
				int idx = 0;
				for (int i = 1; i < candidates.size(); ++i) {
					if (candidates[idx].recommendCnt > candidates[i].recommendCnt) {
						idx = i;
					}
					else if (candidates[idx].recommendCnt == candidates[i].recommendCnt) {
						if (candidates[idx].date > candidates[i].date) {
							idx = i;
						}
					}
				}

				check[candidates[idx].id] = false;
				check[studentId] = true;
				candidates[idx].id = studentId;
				candidates[idx].recommendCnt = 1;
				candidates[idx].date = curDay;
			}
			else {
				candidates.push_back(student(studentId, curDay));
				check[studentId] = true;
			}
		}
		
		++curDay;
	}

	sort(candidates.begin(), candidates.end(), cmp);
	for (int i = 0; i < candidates.size(); ++i) {
		cout << candidates[i].id << ' ';
	}
	return 0;
}
