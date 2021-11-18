#include <iostream>
#include <vector>
using namespace std;

int dpForZero(int N, vector<int>& memo_0){
    if(memo_0[N] != -1)
        return memo_0[N];
    else{
        memo_0[N] = dpForZero(N-1, memo_0) + dpForZero(N-2, memo_0);
        return memo_0[N];
    }
}
int dpForOne(int N, vector<int>& memo_1){
    if(memo_1[N] != -1)
        return memo_1[N];
    else {
        memo_1[N] = dpForOne(N-1, memo_1) + dpForOne(N-2, memo_1);
        return memo_1[N];
    }
}
int main(){
    // 메모리제이션위한 배열 초기화.
    vector<int> memo_0(41, -1);
    memo_0[0] = 1;
    memo_0[1] = 0;
    vector<int> memo_1(41, -1);
    memo_1[0] = 0;
    memo_1[1] = 1;

    // 입력.
    int T;
    cin >> T;
    vector<pair<int, int>> answers;
    while(T--){
        int N;
        cin >> N;
        answers.push_back(make_pair(dpForZero(N, memo_0), dpForOne(N, memo_1)));
    }

    // 출력
    for(int i=0; i<answers.size(); i++){
        cout << answers[i].first << ' ' << answers[i].second << '\n';
    }
    return 0;
}
