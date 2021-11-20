#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    // 입력.
    int n;
    cin >> n;
    vector<int> stair(n+1, 0);
    for(int i=1; i<=n; i++){
        int score;
        cin >> score;
        stair[i] = score;
    }

    // DP를 이용해 문제 해결. bottom-up 방식 이용.
    // cache[i]: i 번째 계단을 밟았을 경우의 점수의 최댓값.
    vector<int> cache(n+1, 0);
    for(int i=1; i<=n; i++){
        if(i == 1)
            cache[i] = stair[i];
        else if(i == 2)
            cache[i] = cache[i-1] + stair[i];
        else
            cache[i] = max(cache[i-2], cache[i-3] + stair[i-1]) + stair[i];
    }

    // 정답 출력.
    cout << cache[n];
    return 0;
}
