#include <string>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

string getAnswer(string w){
    if(w == "")
        return "";
    else{
        string u;
        stack<char> s;
        // find u
        s.push(w[0]);
        u += w[0];
        int idx = 1;
        while(!s.empty()){
            if(s.top() == w[idx])
                s.push(w[idx]);
            else
                s.pop();
            u += w[idx];
            idx++;
        }
        string v = w.substr(idx);
        
        bool flag = false;
        if(u[0] == ')')
            flag = false;
        else{
            stack<char> s2;
            s2.push(u[0]);
            idx = 1;
            while(idx < u.size()){
                if(u[idx] == ')'){
                    if(s2.size() > 0){
                        s2.pop();
                        idx++;
                    }
                    else{
                        s2.push(' ');
                        break;
                    }
                }
                else{
                    s2.push(u[idx]);
                    idx++;
                }
            }
            if(s2.empty())
                flag = true;
            else
                flag = false;
        }
        
        if(flag){
            return u + getAnswer(v);
        }
        else{
            string tmp = "(";
            tmp += getAnswer(v);
            tmp += ")";
            
            
            for(int i=0; i<u.size(); ++i){
                if(0 < i && i < u.size() - 1){
                    if(u[i] == ')')
                        tmp += '(';
                    else
                        tmp += ')';
                }
            }
            return tmp;
        }
    }
}

string solution(string p) {
    string answer = getAnswer(p);
    return answer;
}
