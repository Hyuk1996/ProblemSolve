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

// stack 이용하 풀이.
#include <iostream>
#include <stack>
using namespace std;

int main(){
    // 입력.
    string S;
    cin >> S;

    // stack을 이용해 압축 해제 문자열 길이 저장.
    stack<pair<char, int>> st;
    for(int i=0; i<S.size(); i++){
        if(S[i] == ')'){
            int Q = 0;
            while(st.top().first != '('){
                Q += st.top().second;
                st.pop();
            }
            st.pop();
            int K = st.top().first - '0';
            st.top().second = Q * K;
        }
        else
            st.push(make_pair(S[i], 1));
    }

    // 출력.
    int ans = 0;
    while(!st.empty()) {
        ans += st.top().second;
        st.pop();
    }
    cout << ans << '\n';
}
