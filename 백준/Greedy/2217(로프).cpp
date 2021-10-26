#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    // 입력.
    int N;
    cin >> N;
    vector<int> lopes;
    for(int i=0; i<N; i++){
        int lope;
        cin >> lope;
        lopes.push_back(lope);
    }

    // 최대 중량 구하기.
    sort(lopes.begin(), lopes.end(), greater<int>());
    int max_weight = -1;
    for(int i=0; i<lopes.size(); i++){
        int cur_weight = lopes[i] * (i + 1);
        max_weight = max(cur_weight, max_weight);
    }
    // 출력.
    cout << max_weight;
    return 0;
}
