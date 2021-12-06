#include <iostream>
#include <vector>
using namespace std;

int dp(vector<int>& cache, int n) {
    if(n <= 3)
        return cache[n];

    if(cache[n] == 0)
        cache[n] = dp(cache, n-1) + dp(cache, n-2) + dp(cache, n-3);
    return cache[n];
}
int main() {
    vector<int> cache(11, 0);
    cache[1] = 1;
    cache[2] = 2;
    cache[3] = 4;

    // 입력.
    int T;
    cin >> T;
    vector<int> answers;
    while(T--) {
        int n;
        cin >> n;

        answers.push_back(dp(cache, n));
    }

    // 정답 출력.
    for(int ans : answers)
        cout << ans << '\n';
    return 0;
}
