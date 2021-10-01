#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(string name) {
    int answer = 0;
    int name_len = name.size();
    string s;
    for(int i=0; i<name_len; i++)
        s+='A';
    
    int cur_idx = 0;
    while(true){
        // cur_idx가 바꿔야 하는 경우.
        if(name[cur_idx] != s[cur_idx]){
            s[cur_idx] = name[cur_idx];
            answer += min(abs(name[cur_idx] - 'A'), abs('Z' - name[cur_idx] + 1));
        }
        
        if(s == name) break;
        // 다음 커서 위치 찾기.
        
        // 커서 오른쪽으로 이동.
        int right = 0;
        int i = cur_idx + 1;
        while(i != cur_idx){
            right++;
            if(i == name_len)
                i = 0;
            
            if(s[i] != name[i])
                break;
            else
                i++;
        }
        
        // 커서 왼쪽으로 이동.
        int left = 0;
        int j = cur_idx -1;
        while(j != cur_idx){
            left++;
            if(j == -1)
                j = name_len - 1;
            
            if(s[j] != name[j])
                break;
            else
                j--;
        }
        
        if(right <= left){
            cur_idx = i;
            answer += right;
        }
        else{
            cur_idx = j;
            answer += left;
        }
        
        //cout << "right: " << right << ", left: " << left << '\n';
        //cout <<"cur_idx: " << cur_idx << "\n\n";
    }
    
    return answer;
}
