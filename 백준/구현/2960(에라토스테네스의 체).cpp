#include <iostream>
#include <vector>
using namespace std;

int main(){
    // 입력.
    int N, K;
    cin >> N >> K;

    // 에라토스테네스의 체.
    vector<bool> v(N+1, 0);
    int P = 2;
    int ans;
    while(P != -1){
        v[P] = true;
        K--;
        if(K == 0){
            ans = P;
            break;
        }

        int idx = P * 2;
        while(idx <= N){
            if(!v[idx]) {
                v[idx] = true;
                K--;
                if(K == 0) {
                    ans = idx;
                    break;
                }
            }
            idx += P;
        }
        if(K == 0)
            break;

        int candidate_P = -1;
        for(int i=P; i<=N; i++){
            if(!v[i]){
                candidate_P = i;
                break;
            }
        }
        P = candidate_P;
    }

    // 출력.
    cout << ans;

    return 0;
}

// 2중 for문 이용해 깔끔한 코드.
#include <iostream>
#include <vector>
using namespace std;

int main(){
    // 입력.
    int N, K;
    cin >> N >> K;
    vector<bool> prime(N+1, 0);

    // 에라토스테네스의 체
    int ans = -1;
    for(int i=2; i<=N; i++){
        if(prime[i])
            continue;
        for(int j=i; j<=N; j+=i){
            if(prime[j])
                continue;
            prime[j] = true;
            K--;
            if(K == 0) {
                ans = j;
                break;
            }
        }
        if(K == 0)
            break;
    }

    // 출력.
    cout << ans;
    return 0;
}
