#include <string>
#include <vector>

using namespace std;

string solution(int n) {
    string answer = "";
    string rev_answer;
    int r;
    do{
        r = n % 3;
        n = n / 3;
        
        if(r == 0){
            n--;
            r = 4;        
        }
        
        rev_answer += to_string(r);
    }while(n != 0);
    
    int len = rev_answer.size();
    for(int i=0; i<len; ++i)
        answer += rev_answer[len - 1 - i];
    return answer;
}
