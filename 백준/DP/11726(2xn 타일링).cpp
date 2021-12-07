#include <iostream>
#include <vector>
using namespace std;
const int DIVISOR = 10007;

int main() {
    // 입력.
    int n;
    cin >> n;

    // 동젝 계획법 이용해 문제 풀이, bottom up 방식 이용.
    vector<int> cache(n+1, 0);
    cache[1] = 1;
    cache[2] = 2;
    for(int i=3; i<=n; ++i) {
        cache[i] = (cache[i-1] + cache[i-2]) % DIVISOR;
    }

    // 정답 출력.
    cout << cache[n];
    return 0;
}
