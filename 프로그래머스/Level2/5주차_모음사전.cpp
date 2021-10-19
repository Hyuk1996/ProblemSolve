#include <string>
#include <vector>
#include <algorithm>

using namespace std;
void dfs(vector<char>& alpa, string w, int len, vector<string>& dict){
    if(w.size() == len){
        dict.push_back(w);
        return;
    }
    
    for(int i=0; i<alpa.size(); i++)
        dfs(alpa, w + alpa[i], len, dict);
}
int solution(string word) {
    int answer = 0;
    
    // 모든 경우의 수 구하기.
    vector<string> dict;
    vector<char> alpa = {'A', 'E', 'I', 'O', 'U'};
    for(int i=1; i<=5; i++){
        dfs(alpa, "", i, dict);
    }
    
    // 모든 경우의 수 사전순으로 정렬.
    sort(dict.begin(), dict.end());
    
    for(int i=0; i<dict.size(); i++){
        if(word == dict[i]){
            answer = i + 1;
            break;
        }
    }
    return answer;
}
