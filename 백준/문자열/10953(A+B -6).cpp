#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    // 입력.
    int T;
    cin >> T;

    // 풀이.
    vector<int> answers;
    while(T--){
        string str;
        cin >> str;

        string A;
        for(int i=0; i<str.size(); i++){
            if(str[i] == ','){
                int a = stoi(A);
                int b = stoi(str.substr(i+1));
                answers.push_back(a+b);
                break;
            }
            else
                A += str[i];
        }
    }

    // 출력.
    for(int i=0; i<answers.size(); i++)
        cout << answers[i] << '\n';
}
