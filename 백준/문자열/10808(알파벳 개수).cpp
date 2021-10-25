#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    // 입력
    string S;
    cin >> S;

    // S의 알파벳 체크.
    vector<int> alphabet(26, 0);
    for(int i=0; i<S.size(); i++)
        alphabet[S[i] - 'a']++;

    // 출력
    for(int i=0; i<alphabet.size(); i++)
        cout << alphabet[i] << ' ';
    return 0;
}
