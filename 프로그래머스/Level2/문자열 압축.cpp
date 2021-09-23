#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(string s) {
    int answer = s.size();
    
    for(int i=1; i<=s.size()/2; i++){
        string tmp, convert;
        
        tmp = s.substr(0, i);
        int cnt = 1;
        for(int j=i; j<s.size(); j+=i){
            if(tmp == s.substr(j, i))
                cnt++;
            else{
                if(cnt > 1)
                    convert += to_string(cnt);
                convert += tmp;
                cnt = 1;
                tmp = s.substr(j, i);
            }
        }
        
        if(cnt > 1)
            convert += to_string(cnt);
        convert += tmp;
        answer = min(answer, (int)convert.size());
    }
    return answer;
}
