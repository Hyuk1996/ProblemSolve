#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    // 입력.
    int N;
    cin >> N;

    // 동적 계획법을 이용해 풀이. bottom-up 방식 이용.
    // cache[i]: N = i 일 경우의, 필요한 최소 연산수.
    vector<int> cache(N+1, 0);
    for(int i=2; i<=N; i++){
        if(i % 3 == 0 && i % 2 == 0)
            cache[i] = min(cache[i/3], min(cache[i/2], cache[i-1])) + 1;
        else if(i % 3 == 0 && i % 2 != 0)
            cache[i] = min(cache[i/3], cache[i-1]) + 1;
        else if(i % 3 != 0 && i % 2 == 0)
            cache[i] = min(cache[i/2], cache[i-1]) + 1;
        else
            cache[i] = cache[i-1] + 1;
    }

    // 정답 출력.
    cout << cache[N];
    return 0;
}
