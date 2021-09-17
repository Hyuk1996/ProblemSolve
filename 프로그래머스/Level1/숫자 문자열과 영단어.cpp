#include <string>
#include <vector>

using namespace std;

int solution(string s) {
    int answer = 0;
    
    for(int i=0; i<s.size(); ++i){
        if('0'<= s[i] && s[i] <= '9'){
            answer += s[i] - '0';
        }
        else{
            int number;
            if(s[i] == 'z'){
                i += 3;
                number = 0;
            }
            else if(s[i] == 'o'){
                i += 2;
                number = 1;
            }
            else if(s[i] == 't' && s[i+1] == 'w'){
                i += 2;
                number = 2;
            }
            else if(s[i] == 't' && s[i+1] == 'h'){
                i += 4;
                number = 3;
            }
            else if(s[i] == 'f'  && s[i+1] == 'o'){
                i += 3;
                number = 4;
            }
            else if(s[i] == 'f' && s[i+1] == 'i'){
                i += 3;
                number = 5;
            }
            else if(s[i] == 's' && s[i+1] == 'i'){
                i += 2;
                number = 6;
            }
            else if(s[i] == 's' && s[i+1] == 'e'){
                i += 4;
                number = 7;
            }
            else if(s[i] == 'e'){
                i += 4;
                number = 8;
            }
            else{
                i += 3;
                number = 9;
            }
            answer += number;
        }
        
        if( i != s.size() -1)
            answer *= 10;
    }
    
    return answer;
}
