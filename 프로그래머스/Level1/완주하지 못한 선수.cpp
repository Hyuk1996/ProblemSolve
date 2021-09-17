#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    
    sort(participant.begin(), participant.end());
    sort(completion.begin(), completion.end());
    
    for(int i=0; i<completion.size(); ++i){
        if(participant[i] == completion[i])
            continue;
        else{
            answer = participant[i];
            break;
        }
    }
    if(answer == "")
        answer = participant.back();
    
    return answer;
}


// 원래 문제의 의도 (hash 사용)
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    unordered_map<string, int> um;
    string key;
    for(int i=0; i<completion.size(); ++i){
        key = completion[i];
        if(um.find(key) == um.end())
            um.insert(make_pair(key, 1));
        else
            um[key]++;
    }
    
    for(int i=0; i<participant.size(); ++i){
        key = participant[i];
        if(um.find(key) == um.end()){
            answer = key;
            break;
        }
        else{
            um[key]--;
            if(um[key] < 0){
                answer = key;
                break;
            }
        }
    }
    return answer;
}
