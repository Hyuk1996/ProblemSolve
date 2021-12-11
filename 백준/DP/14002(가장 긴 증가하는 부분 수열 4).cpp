#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
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

    // 동적 계획법을 이용해 길이를 구하고, 추가적인 vector을 이용해 부분 수열의 내용 구하기.
    vector<int> cache(n, 1);
    vector<int> parent(n);
    int ans = -1;
    int ans_idx = -1;
    for(int i=0; i<n; ++i) {
        parent[i] = i;
        for(int j=0; j<i; ++j) {
            if(a[j] < a[i] && cache[j] + 1 > cache[i]) {
                cache[i] = cache[j] + 1;
                parent[i] = j;
            }
        }
        if(ans < cache[i]) {
            ans = cache[i];
            ans_idx = i;
        }
    }

    // 정답 출력.
    cout << ans << '\n';

    int idx = ans_idx;
    stack<int> s;
    while(true) {
        s.push(a[idx]);
        if(parent[idx] == idx)
            break;
        idx = parent[idx];
    }
    while(!s.empty()) {
        cout << s.top() << ' ';
        s.pop();
    }

    return 0;
}
