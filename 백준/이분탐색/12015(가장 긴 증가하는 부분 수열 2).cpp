#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // 입력.
    int n;
    cin >> n;
    vector<int> A(n);
    for(int i=0; i<n; ++i) {
        int val;
        cin >> val;
        A[i] = val;
    }

    // 이분 탐색을 이용한 풀이.
    vector<int> ans;
    for(int i=0; i<n; ++i) {
        if(ans.empty() || ans.back() < A[i])
            ans.push_back(A[i]);
        else {
            auto it = lower_bound(ans.begin(), ans.end(), A[i]);
            *it = A[i];
        }
    }

    // 정답 출력.
    cout << ans.size();
    return 0;
}
