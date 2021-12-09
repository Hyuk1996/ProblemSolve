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
    vector<int> cache(N);
    for(int i=0; i<N; ++i) {
        cache[i] = A[i];
        for(int j=0; j<i; ++j) {
            if(A[j] < A[i] && (cache[j] + A[i]) > cache[i]) {
                cache[i] = cache[j] + A[i];
            }
        }
        answer = max(answer, cache[i]);
    }

    // 정답 출력.
    cout << answer;
    return 0;
}
