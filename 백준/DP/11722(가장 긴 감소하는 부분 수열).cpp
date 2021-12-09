#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // 입력.
    int N;
    cin >> N;
    vector<int> A(N);
    for(int i=0; i<N; ++i) {
        int val;
        cin >> val;
        A[i] = val;
    }

    // 동적 계획법 이용한 풀이. (bottom-up)
    int answer = -1;
    vector<int> cache(N, 1);
    for(int i=0; i<N; ++i) {
        for(int j=0; j<i; ++j) {
            if(A[j] > A[i] && (cache[j] + 1) > cache[i]) {
                cache[i] = cache[j] + 1;
            }
        }
        answer = max(answer, cache[i]);
    }

    // 정답 출력.
    cout << answer;
    return 0;
}
