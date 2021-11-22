#include <iostream>
#include <vector>
using namespace std;

int getButtonCnt(int& T, int button){
    int q = T / button;
    T %= button;
    return q;
}
int main(){
    // 입력.
    int T;
    cin >> T;

    // Greedy Method 이용해 최소버튼 조작 방법 구하기.
    vector<int> button = {300, 60, 10};
    vector<int> answers(3, 0);
    for(int i=0; i<3; i++)
        answers[i] = getButtonCnt(T, button[i]);

    // 정답 출력.
    if(T != 0)
        cout << -1;
    else
        for(int i=0; i<3; i++)
            cout << answers[i] << ' ';
    return 0;
}
