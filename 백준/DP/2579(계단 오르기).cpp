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

#include <iostream>
#include <vector>
using namespace std;

int recursive(vector<int>& stairs, int N, vector<int>& dp) {
	if (N <= 1) {
		return stairs[N];
	}
	else if (N == 2) {
		if (dp[N - 1] == 0) {
			dp[N - 1] = recursive(stairs, N - 1, dp);
		}
		return dp[N - 1] + stairs[N];
	}
	else {
		if (dp[N] == 0) {
			dp[N] = max(recursive(stairs, N - 2, dp), recursive(stairs, N - 3, dp) + stairs[N-1]) + stairs[N];
		}
		return dp[N];
	}
}
void input(int& N, vector<int>& stairs) {
	cin >> N;
	stairs.assign(N + 1, 0);
	for (int i = 1; i <= N; ++i) {
		cin >> stairs[i];
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int N;
	vector<int> stairs;
	input(N, stairs);

	vector<int> dp(N + 1, 0);
	int answer = recursive(stairs, N, dp);
	cout << answer;
	return 0;
}
