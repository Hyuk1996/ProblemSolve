#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // 입력
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i=0; i<n; ++i) {
        int val;
        cin >> val;
        a[i] = val;
    }

    // 그리디 & 이분탐색 이용 가장 긴 증가하는 부분 수열 구하기.
    vector<int> answer;
    for(int i=0; i<n; ++i) {
        if(answer.empty() || answer.back() < a[i])
            answer.push_back(a[i]);
        else {
            auto it = lower_bound(answer.begin(), answer.end(), a[i]);
            *it = a[i];
        }
    }

    // 정답 출력.
    cout << answer.size();
    return 0;
}
