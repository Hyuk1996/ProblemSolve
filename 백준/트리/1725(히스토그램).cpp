#include <iostream>
#include <vector>
#include <algorithm>
#define INF 1000000001
using namespace std;
int N;
vector<int> histogram;

int getRangeMinIdx(vector<int>& IDT, int left, int right) {
    left += (IDT.size() / 2) - 1;
    right += (IDT.size() / 2) - 1;

    int minIdx = 0;
    while(left <= right) {
        if(left % 2 == 1) {
            if(histogram[minIdx] > histogram[IDT[left]]) {
                minIdx = IDT[left];
            }
        }
        if(right % 2 == 0) {
            if(histogram[minIdx] > histogram[IDT[right]]) {
                minIdx = IDT[right];
            }
        }

        left = (left + 1) / 2;
        right = (right - 1) / 2;
    }
    return minIdx;
}
void makeMinIdxIDT(vector<int>& IDT) {
    int leafSize = 1;
    while(leafSize < N) {
        leafSize *= 2;
    }

    IDT.assign(leafSize * 2, 0);

    //leaf node 채우기
    int startIdx = leafSize;
    for(int i = 1; i <= N; ++i) {
        IDT[i + startIdx - 1] = i;
    }

    //internal node 채우기
    for(int i = startIdx - 1; i >= 1; --i) {
        if(histogram[IDT[i * 2]] <= histogram[IDT[i * 2 + 1]]) {
            IDT[i] = IDT[i * 2];
        } else {
            IDT[i] = IDT[i * 2 + 1];
        }
    }
}
int getMaxSize(vector<int>& IDT, int left, int right) {
    int minIdx = getRangeMinIdx(IDT, left, right);
    int size = (right - left + 1) * histogram[minIdx];

    if(left < minIdx) {
        size = max(size, getMaxSize(IDT, left, minIdx - 1));
    }
    if(minIdx < right) {
        size = max(size, getMaxSize(IDT, minIdx + 1, right));
    }
    return size;
}
int solve() {
    vector<int> IDT;
    makeMinIdxIDT(IDT);

    return getMaxSize(IDT, 1, N);
}
void input() {
    cin >> N;
    histogram.assign(N+1, INF);
    for(int i = 1; i <= N; ++i) {
        cin >> histogram[i];
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    input();

    cout << solve();
    return 0;
}
