#include <iostream>
#include <vector>
using namespace std;
const int MAX = 30;

int getCombi(int M, int N, vector<vector<int>>& cache) {
    // base case
    if(M == N || N == 0)
        return 1;
    else {
        if(cache[M][N] == 0)
            cache[M][N] = getCombi(M-1, N-1, cache) + getCombi(M-1, N, cache);
        return cache[M][N];
    }
}
int main() {
    // 정답을 담을 배열.
    vector<int> answers;

    // 동적 계획법에 사용할 cache
    vector<vector<int>> cache(MAX, vector<int>(MAX, 0));

    // 입력.
    int T;
    cin >> T;
    while(T--) {
        int N, M;
        cin >> N >> M;

        // 동적 계획법 이용해 mCn 구하기.
        int ans = getCombi(M, N, cache);
        answers.push_back(ans);
    }


    // 정답 출력.
    for(int ans : answers)
        cout << ans << '\n';
    return 0;
}
