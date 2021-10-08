#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

string solution(string number, int k) {
    string answer;
    stack<char> s; // 정답을 담을 stack.
    
    for(int i=0; i<number.size(); i++){
        while(!s.empty() && k > 0){
            if(s.top() < number[i]){
                s.pop();
                k--;
            }
            else
                break;
        }
        s.push(number[i]);
    }
    
    while(k > 0){
        s.pop();
        k--;
    }
    
    
    while(!s.empty()){
        answer = s.top() + answer;
        s.pop();
    }

    return answer;
}
