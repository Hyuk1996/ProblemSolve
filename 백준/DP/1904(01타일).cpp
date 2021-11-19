#include <iostream>
using namespace std;
int cache[1000001];

int getAnswer(int n){
    if(n <= 2)
        return n;

    if(cache[n] != 0)
        return cache[n];
    else{
        cache[n] = (getAnswer(n-1) + getAnswer(n-2)) % 15746;
        return cache[n];
    }
}
int main(){
    // 입력.
    int N;
    cin >> N;

    // 동적 계획법을 이용해 답 구하기.
    int answer = getAnswer(N);
    cout << answer;
    return 0;
}
