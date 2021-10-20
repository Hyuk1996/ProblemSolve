// 백준 2304(창고 다각형)과 유사 문제.
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int main(){
    // 입력 받기.
    int H, W;
    cin >> H >> W;
    vector<vector<int>> v(W, vector<int>(3,0)); // 2차원 세계 정보.
    for(int i=0; i<v.size(); i++){
        int h;
        cin >> h;
        v[i][0] = h;
    }

    // 물이 고인 2차원 세계 - 기존 2차원 세계 = 빗물의 총량.

    // 물이 고인 2차원 세계 구하기.
    int max_val = -1;
    for(int i=0; i<v.size(); i++){
        max_val = max(max_val, v[i][0]);
        v[i][1] = max_val;
    }

    max_val = -1;
    for(int i=v.size()-1; i >= 0; i--){
        max_val = max(max_val, v[i][0]);
        v[i][2] = max_val;
    }

    // 물이 고인 2차원 세계 - 기존 2차원 세계.
    int ans = 0;
    for(int i=0; i<v.size(); i++)
        ans += (min(v[i][1], v[i][2]) - v[i][0]);
    cout << ans;
}
