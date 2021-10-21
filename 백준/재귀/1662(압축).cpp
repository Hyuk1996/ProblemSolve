#include <iostream>
#include <string>
using namespace std;
bool visit[51];

int dfs(string& S, int start){
    int cnt = 0;

    for(int i=start; i<S.size(); i++){
        if(S[i] == '(' && !visit[i]){
            visit[i] = true;
            int K = S[i-1] - '0';
            cnt--;
            cnt += (K * dfs(S, i + 1));
        }
        else if(S[i] == ')' && !visit[i]){
            visit[i] = true;
            return cnt;
        }
        else if(!visit[i]){
            visit[i] = true;
            cnt++;
        }
    }
    return cnt;
}

int main(){
    // 입력.
    string S;
    cin >> S;

    // dfs 이용해 압축풀린 문자열 길이 구하기.
    int answer = dfs(S, 0);
    cout << answer << '\n';
}
