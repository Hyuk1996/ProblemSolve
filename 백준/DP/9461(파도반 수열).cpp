#include <iostream>
#include <vector>
using namespace std;
long long cache[101];

long long P(int n){
    if(n < 6){
        if(n <= 3)
            return 1;
        else
            return 2;
    }

    if(cache[n] != 0)
        return cache[n];
    else{
        cache[n] = P(n-1) + P(n-5);
        return cache[n];
    }
}
int main(){
    // 입력.
    int T;
    cin >> T;
    vector<long long> answers;
    while(T--){
        int N;
        cin >> N;
        answers.push_back(P(N));
    }

    // 출력.
    for(int i=0; i<answers.size(); i++)
        cout << answers[i] << '\n';
    return 0;
}
