#include <iostream>
#include <vector>
using namespace std;

int getChangeCnt(int& total_change, int change){
    int q = total_change / change;
    total_change %= change;
    return q;
}
int main(){
    // 입력.
    int price;
    cin >> price;
    int total_change = 1000 - price;

    // 탐욕법으로 최소 거스름돈 개수 구하기.
    vector<int> changes = {500, 100, 50, 10, 5, 1};
    int ans = 0;
    for(int i=0; i<changes.size(); i++){
        if(total_change >= changes[i])
            ans += getChangeCnt(total_change, changes[i]);
    }

    // 정답 출력.
    cout << ans;
    return 0;
}
