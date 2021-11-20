#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    // 입력.
    int n;
    cin >> n;
    vector<vector<int>> triangle(n+1, vector<int>(n+1, 0));
    for(int i=1; i<=n; i++){
        for(int j=1; j<=i; j++){
            int val;
            cin >> val;
            triangle[i][j] = val;
        }
    }

    // 동적 계획법을 이용해 문제 해결. bottom-up 사용.
    vector<vector<int>> cache(n+1, vector<int>(n+1, -1));
    cache[1][1] = triangle[1][1];
    for(int i=2; i<=n; i++){
        for(int j=1; j<=i; j++){
            if(j == 1)
                cache[i][j] = cache[i-1][j] + triangle[i][j];
            else if(j == n)
                cache[i][j] = cache[i-1][j-1] + triangle[i][j];
            else
                cache[i][j] = max(cache[i-1][j-1], cache[i-1][j]) + triangle[i][j];
        }
    }

    // 정답 구하기.
    int ans = *max_element(cache[n].begin() + 1, cache[n].end());
    cout << ans;

    return 0;
}
