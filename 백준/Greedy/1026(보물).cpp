#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    // 입력.
    int N;
    cin >> N;
    vector<int> A;
    vector<int> B;
    for(int i=0; i<N; i++){
        int tmp;
        cin >> tmp;
        A.push_back(tmp);
    }
    for(int i=0; i<N; i++){
        int tmp;
        cin >> tmp;
        B.push_back(tmp);
    }

    // B의 최대값 * A의 최솟값 (그리디 알고리즘)
    sort(A.begin(), A.end());
    sort(B.begin(), B.end(), greater<int>());

    int ans = 0;
    for(int i=0; i<A.size(); i++)
        ans += A[i] * B[i];
    cout << ans;
    return 0;
}
