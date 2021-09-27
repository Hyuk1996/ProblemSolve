#include <iostream>
#include<string>
#include <stack>
using namespace std;

int solution(string s)
{
    int answer = -1;

    stack<char> check;
    
    check.push(s[0]);
    for(int i=1; i<s.size(); ++i){
        if(check.size() == 0)
            check.push(s[i]);
        else{
            if(check.top() == s[i])
                check.pop();
            else
                check.push(s[i]);
        }
    }
    
    if(check.empty())
        answer = 1;
    else
        answer = 0;

    return answer;
}
