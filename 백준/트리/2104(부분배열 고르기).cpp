#include <iostream>
#include <vector>
#include <algorithm>
#define INF 987654321
using namespace std;
int N;
vector<int> A;

int rangeMinIdx(vector<pair<int, int>>& minIDT, int left, int right) {
    left += (minIDT.size() / 2) - 1;
    right += (minIDT.size() / 2) - 1;
    int minVal = INF;
    int idx = -1;
    while(left <= right) {
        if(left % 2 == 1) {
            if(minIDT[left].first < minVal) {
                minVal = minIDT[left].first;
                idx = minIDT[left].second;
            }
        }
        if(right % 2 == 0) {
            if(minIDT[right].first < minVal) {
                minVal = minIDT[right].first;
                idx = minIDT[right].second;
            }
        }

        left = (left + 1) / 2;
        right = (right - 1) / 2;
    }

    return idx;
}
long long rangeSum(vector<long long>& sumIDT, int left, int right) {
    left += (sumIDT.size() / 2) - 1;
    right += (sumIDT.size() / 2) - 1;
    long long sum = 0;
    while(left <= right) {
        if(left % 2 == 1) {
            sum += sumIDT[left];
        }
        if(right % 2 == 0) {
            sum += sumIDT[right];
        }

        left = (left + 1) / 2;
        right = (right - 1 ) / 2;
    }
    return sum;
}
long long getMaxScore(int left, int right, vector<long long>& sumIDT, vector<pair<int, int>>& minIDT) {

    int minIdx = rangeMinIdx(minIDT, left, right);
    long long score = rangeSum(sumIDT, left, right) * A[minIdx];
    
    if(left < minIdx) {
        score = max(score, getMaxScore(left, minIdx - 1, sumIDT, minIDT));
    }
    if(minIdx < right) {
        score = max(score, getMaxScore(minIdx + 1, right, sumIDT, minIDT));
    }

    return score;
}
void makeMinIDT(vector<pair<int, int>>& minIDT) {
    int start = 1;
    while(start < N) {
        start *= 2;
    }

    //first : 최솟값, second: 해당 값의 인덱스
    minIDT.assign(start * 2, {INF, N + 1});

    //leaf node 채우기
    for(int i = 1; i <= N; ++i) {
        minIDT[i + start - 1].first = A[i];
        minIDT[i + start - 1].second = i;
    }

    //internal node 채우기
    for(int i = start - 1; i >= 1; --i) {
        if(minIDT[i * 2].first <= minIDT[i * 2 + 1].first) {
            minIDT[i].first = minIDT[i * 2].first;
            minIDT[i].second = minIDT[i * 2].second;
        } else {
            minIDT[i].first = minIDT[i * 2 + 1].first;
            minIDT[i].second = minIDT[i * 2 + 1].second;
        }
    }
}
void makeSumIDT(vector<long long>& sumIDT) {
    int start = 1;
    while(start < N) {
        start *= 2;
    }

    sumIDT.assign(start * 2, 0);

    //leaf node 채우기
    for(int i = 1; i <= N; ++i) {
        sumIDT[i + start - 1] = A[i];
    }

    //internal node 채우기
    for(int i = start - 1; i >= 1; --i) {
        sumIDT[i] = sumIDT[i * 2] + sumIDT[i * 2 + 1];
    }
}
long long solve() {
    vector<long long> sumIDT;
    makeSumIDT(sumIDT);

    vector<pair<int, int>> minIDT;
    makeMinIDT(minIDT);

    return getMaxScore(1, N, sumIDT, minIDT);
}
void input() {
    cin >> N;
    A.assign(N + 1, 0);
    for(int i = 1; i <= N; ++i) {
        cin >> A[i];
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    input();

    long long answer = solve();

    cout << answer;
    return 0;
}
