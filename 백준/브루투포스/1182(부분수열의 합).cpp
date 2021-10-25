#include <iostream>
#include <vector>
using namespace std;

void getCombi(vector<int>& v, int idx, int cur_depth, int depth, int sum, int S, int& ans){
    if(cur_depth == depth){
        if(sum == S)
            ans++;
        return;
    }

    for(int i=idx; i<v.size(); i++)
        getCombi(v, i+1, cur_depth+1, depth, sum + v[i], S, ans);
}
int main(){
    // 입력.
    int N, S;
    cin >> N >> S;
    vector<int> v;
    for(int i=0; i<N; i++){
        int tmp;
        cin >> tmp;
        v.push_back(tmp);
    }

    // 모든 부분 수열 하구하기.
    int ans = 0;
    for(int i=1; i<=N; i++) // 부분 수열의 크기 1~N
        getCombi(v, 0, 0, i, 0, S, ans);

    // 출력.
    cout << ans;
    return 0;
}
