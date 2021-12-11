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

    // 그리디 방식 & 이분 탐색 이용해 최단길이 찾기 , 추가적인 vector 이용해 부분 수열 찾기.
    int ansIndex = -1;
    vector<int> answer;
    vector<int> answerIndex;
    vector<int> parent(n);
    for(int i=0; i<n; ++i) {
        if(answer.empty() || answer.back() < a[i]) {
            answer.push_back(a[i]);
            answerIndex.push_back(i);
            if(answer.size() > 1)
                parent[i] = answerIndex[answerIndex.size() - 2];
            else
                parent[i] = i;

            ansIndex = i;
        }
        else {
            auto it = lower_bound(answer.begin(), answer.end(), a[i]);
            *it = a[i];
            int idx = it - answer.begin();
            answerIndex[idx] = i;

            if(idx > 0)
                parent[i] = answerIndex[idx - 1];
            else
                parent[i] = i;
        }
    }

    // 정답 출력.
    cout << answer.size() << '\n';

    int index = ansIndex;
    stack<int> s;
    while(true) {
        s.push(a[index]);
        if(parent[index] == index)
            break;
        index = parent[index];
    }
    while(!s.empty()) {
        cout << s.top() << ' ';
        s.pop();
    }
    return 0;
}

#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

int main() {
    // 입력.
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i=0; i<n; ++i) {
        int val;
        cin >> val;
        a[i] = val;
    }

    // 그리디 & 이분탐색 이용해 길이구하고, 추가적인 vector 이용해 부분 수열 구하기.
    vector<int> LIS;
    vector<int> index(n);
    for(int i=0; i<n; ++i) {
        if(LIS.empty() || LIS.back() < a[i]) {
            LIS.push_back(a[i]);
            index[i] = LIS.size() - 1;
        }
        else {
            auto it = lower_bound(LIS.begin(), LIS.end(), a[i]);
            *it = a[i];
            index[i] = it - LIS.begin();
        }
    }

    // 정답 출력.
    cout << LIS.size() << '\n';

    int tmp = LIS.size() - 1;
    stack<int> s;
    for(int i=n-1; i>=0; --i) {
        if(index[i] == tmp) {
            s.push(a[i]);
            --tmp;
        }
    }

    while(!s.empty()) {
        cout << s.top() << ' ';
        s.pop();
    }
    return 0;
}
