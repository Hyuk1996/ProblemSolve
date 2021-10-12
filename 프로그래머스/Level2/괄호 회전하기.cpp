#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

int solution(string s) {
    int answer = 0;
    
    int x = 0;
    int s_len = s.size();
    while(x < s_len){
        // s가 x 만큼 회전했을 경우, 올바른 문자열인지 확인.
        int idx = 0 + x;
        stack<char> check;
        for(int i=idx; i<s.size(); i++){
            if(s[i] == '(' || s[i] == '[' || s[i] == '{')
                check.push(s[i]);
            else{
                if(check.empty()){
                    check.push('x');
                    break;
                }
                else{
                    if(s[i] == ')' && check.top() == '(')
                        check.pop();
                    else if(s[i] == ']' && check.top() == '[')
                        check.pop();
                    else if(s[i] == '}' && check.top() == '{')
                        check.pop();
                    else
                        break;
                }
            }
        }
        
        if(check.empty())
            answer++;
        
        // rotation
        s += s[x];
        x++;
    }
    return answer;
}
