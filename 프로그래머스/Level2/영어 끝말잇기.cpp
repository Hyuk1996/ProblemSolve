#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

vector<int> solution(int n, vector<string> words) {
    vector<int> answer;
    
    int out_time = -1;
    unordered_map<string, int> dict;
    for(int i=0; i<words.size(); i++){
        if(i==0){
            if(words[i].size() <= 1){
                out_time = i;
                break;
            }
            else{
                dict[words[i]] = 1;
            }
        }
        else{
            int start_word = words[i - 1][words[i-1].size() - 1];
            // 끝말잇기 룰 확인.
            bool check = true;
            if(start_word != words[i][0])
                check = false;
            if(words[i].size() <= 1)
                check = false;
            if(dict.find(words[i]) != dict.end())
                check = false;
            
            if(check)
                dict[words[i]] = 1;
            else{
                out_time = i;
                break;
            }
        }
    }

    if(out_time == -1){ // 탈락자 없는 경우.
        answer.push_back(0);
        answer.push_back(0);
    }
    else{
        answer.push_back((out_time % n) + 1);
        answer.push_back((out_time / n) + 1);
    }
        
    return answer;
}
