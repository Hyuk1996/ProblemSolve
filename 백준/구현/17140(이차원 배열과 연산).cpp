#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX = 101;

bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    if(a.second == b.second) {
        return a.first < b.first;
    }
    return a.second < b.second;
}
int solve(int r, int c, int k, vector<vector<int>>& A) {
    int curTime = 0;
    if(A[r][c] == k) {
        return curTime;
    }

    int rLen = 3;
    int cLen = 3;
    while(curTime < 100) {
        ++curTime;
        if(rLen >= cLen) {
            int maxLen = 0;
            for(int i=1; i<=rLen; ++i) {
                //숫자 개수 세기
                vector<int> count(MAX, 0);
                for(int j=1; j<=cLen; ++j) {
                    count[A[i][j]]++;
                    A[i][j] = 0;
                }

                //정렬
                vector<pair<int, int>> tmp;
                for(int j=1; j<=100; ++j) {
                    if(count[j] > 0) {
                        tmp.push_back(make_pair(j, count[j]));
                    }
                }
                sort(tmp.begin(), tmp.end(), cmp);

                //정렬 값 A에 대입
                int idx = 1;
                for(int j=0; j<tmp.size(); ++j) {
                    if(idx > 100) {
                        break;
                    } else {
                        A[i][idx] = tmp[j].first;
                        idx++;
                    }

                    if(idx > 100) {
                        break;
                    } else {
                        A[i][idx] = tmp[j].second;
                        idx++;
                    }
                }
                maxLen = max(maxLen, idx - 1);
            }
            cLen = maxLen;
        } else {
            int maxLen = 0;
            for(int i=1; i<=cLen; ++i) {
                //숫자 카운트
                vector<int> count(MAX, 0);
                for(int j=1; j<=rLen; ++j) {
                    count[A[j][i]]++;
                    A[j][i] = 0;
                }
                //정렬
                vector<pair<int, int>> tmp;
                for(int j=1; j<=100; ++j) {
                    if(count[j] > 0) {
                        tmp.push_back(make_pair(j, count[j]));
                    }
                }
                sort(tmp.begin(), tmp.end(), cmp);
                //대입
                int idx = 1;
                for(int j=0; j<tmp.size(); ++j) {
                    if(idx > 100) {
                        break;
                    } else {
                        A[idx][i] = tmp[j].first;
                        idx++;
                    }

                    if(idx > 100) {
                        break;
                    } else {
                        A[idx][i] = tmp[j].second;
                        idx++;
                    }
                }
                maxLen = max(maxLen, idx - 1);
            }
            rLen = maxLen;
        }

        if(A[r][c] == k) {
            return curTime;
        }
    }
    return -1;
}
void input(int& r, int& c, int& k, vector<vector<int>>& A) {
    cin >> r >> c >> k;
    A.assign(MAX, vector<int>(MAX, 0));
    for(int i=1; i<=3; ++i) {
        for(int j=1; j<=3; ++j) {
            cin >> A[i][j];
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int r, c, k;
    vector<vector<int>> A;
    input(r, c, k, A);

    int answer = solve(r, c, k, A);

    cout << answer;
    return 0;
}
