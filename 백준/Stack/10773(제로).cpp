#include <iostream>
#include <stack>
using namespace std;

int main(){
    // 입력.
    int K;
    cin >> K;

    // 수 저장.
    stack<int> s;
    while(K--){
        int num;
        cin >> num;
        if(num == 0)
            s.pop();
        else
            s.push(num);
    }

    // 정답 구하기 & 출력.
    int ans = 0;
    while(!s.empty()){
        ans += s.top();
        s.pop();
    }
    cout << ans;
    return 0;
}
