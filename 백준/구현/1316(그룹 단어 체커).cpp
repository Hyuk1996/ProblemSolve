#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main(){
    // 입력.
    int N;
    cin >> N;

    // 그룹 단어 찾기.
    int ans = 0;
    while(N--){
        string str;
        cin >> str;
        unordered_map<char, int> hash;

        bool is_group_word = true;
        for(int i=0; i<str.size(); i++){
            if(hash.find(str[i]) == hash.end())
                hash[str[i]] = 1;
            else{
                if(str[i-1] != str[i]){
                    is_group_word = false;
                    break;
                }
            }
        }
        if(is_group_word)
            ans++;
    }

    // 출력.
    cout << ans;
    return 0;
}
