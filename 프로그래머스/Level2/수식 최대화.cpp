#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <cstdlib>
#include <iostream>

using namespace std;

long long solution(string expression) {
    long long answer = 0;
    
    // 수식의 연산자 종류 구하기.
    bool plus = false;
    bool minus = false;
    bool multi = false;
    for(int i=0; i<expression.size(); i++){
        if(expression[i] == '+')
            plus = true;
        else if(expression[i] == '-')
            minus = true;
        else if(expression[i] == '*')
            multi = true;
    }
    
    string op;
    if(multi)
        op += '*';
    if(plus)
        op += '+';
    if(minus)
        op += '-';
    
    do{
        // 연산자 우선순위 정하기.
        unordered_map<char, int> m;
        for(int i=0; i<op.size(); i++)
            m[op[i]] = i;
        
        stack<long long> num_s;
        stack<char> op_s;
        
        // 연산자 우선순위 참고해 수식 계산하기.
        int next_num = 0;
        char next_op;
        for(int i=0; i<expression.size(); i++){
            if('0' <= expression[i] && expression[i] <= '9'){
                if(next_num == 0)
                    next_num = expression[i] - '0';
                else{
                    next_num *= 10;
                    next_num += expression[i] - '0';
                }
            }
            else{
                num_s.push((long long)next_num);
                next_num = 0;
                
                next_op = expression[i];
                while(!op_s.empty()){
                    char prev_op = op_s.top();
                    if(m[prev_op] <= m[next_op]){
                        long long b = num_s.top();
                        num_s.pop();
                        long long a = num_s.top();
                        num_s.pop();
                        
                        char cur_op = op_s.top();
                        op_s.pop();
                        
                        long long result = 0;
                        if(cur_op == '*')
                            result = a * b;
                        else if(cur_op == '+')
                            result = a + b;
                        else if(cur_op == '-')
                            result = a - b;
                        num_s.push(result);
                    }
                    else
                        break;
                }
                op_s.push(next_op);
            }
        }
        num_s.push(next_num);
        
        while(!op_s.empty()){
            char cur_op = op_s.top();
            op_s.pop();
            
            long long b = num_s.top();
            num_s.pop();
            long long a = num_s.top();
            num_s.pop();
            
            long long result = 0;
            if(cur_op == '*')
                result = a * b;
            else if(cur_op == '+')
                result = a + b;
            else if(cur_op == '-')
                result = a - b;
            num_s.push(result);
        }
        
        if(num_s.size() == 1){
            //test
            //cout << op << ": " << abs(num_s.top()) << '\n';
            
            answer = max(answer, abs(num_s.top()));
        }
        else{
            cout << "error\n"; 
        }
    }while(next_permutation(op.begin(), op.end()));

    
    
    return answer;
}
