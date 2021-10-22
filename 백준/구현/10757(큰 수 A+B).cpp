#include <string>
#include <iostream>
using namespace std;

int main(){
    // 입력.
    string A;
    string B;
    cin >> A;
    cin >> B;

    string ans;
    if(A.size() >= B.size()){
        int idx = B.size() - 1;
        int check = 0; // 올림 수.
        for(int i=A.size() - 1; i>=0; i--){
            if(idx >= 0){
                int sum = (A[i] - '0') + (B[idx] - '0') + check;
                check = sum / 10;
                sum = sum % 10;
                ans += to_string(sum);
                idx--;
            }
            else{
                int sum = A[i] - '0' + check;
                check = sum / 10;
                sum = sum % 10;
                ans += to_string(sum);
            }
        }
        if(check == 1)
            ans += '1';
    }
    else{
        int idx = A.size() - 1;
        int check = 0; // 올림 수.
        for(int i=B.size() - 1; i>=0; i--){
            if(idx >= 0){
                int sum = (B[i] - '0') + (A[idx] - '0') + check;
                check = sum / 10;
                sum = sum % 10;
                ans += to_string(sum);
                idx--;
            }
            else{
                int sum = B[i] - '0' + check;
                check = sum / 10;
                sum = sum % 10;
                ans += to_string(sum);
            }
        }
        if(check == 1)
            ans += '1';
    }

    // 출력
    for(int i=ans.size() - 1; i>=0; i--)
        cout << ans[i];

    return 0;
}
