#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // 입력.
    int n;
    cin >> n;
    vector<int> t(n+1);  // index 번째 상담을 하는데 걸리는 시간.
    vector<int> p(n+1);  // index 번째 상담을 하면 얻는 수익.
    for(int i=1; i<=n; ++i) {
        int time, profit;
        cin >> time >> profit;
        t[i] = time;
        p[i] = profit;
    }

    // 동적 계획법 이용해 풀이.
    // cache[i] : i일 까지 얻을 수 있는 최대 이익 (i일 당일에 완료된 작업의 이익은 포함하지 않는다.)
    vector<int> cache(n+2, 0);
    for(int i=1; i<=n; ++i) {
        // i날의 상담을 하지 않는경우.
        cache[i+1] = max(cache[i], cache[i+1]);

        // i날의 상담을 하는 경우.
        if(i + t[i] > n+1)
            continue;
        cache[i + t[i]] = max(cache[i + t[i]], cache[i] + p[i]);
    }

    // 정답 출력.
    cout << cache[n+1];
    return 0;
}
