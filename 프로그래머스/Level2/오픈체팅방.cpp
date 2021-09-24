#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct token{
    string command;
    string userid;
    string nickname;
};

token getToken(string s){
    token tk;
    
    int idx = 0;
    while(s[idx] != ' '){
        tk.command += s[idx];
        idx++;
    }
    
    idx++;
    if(tk.command != "Leave"){
        while(s[idx] != ' '){
            tk.userid += s[idx];
            idx++;
        }
        
        idx++;
        while(idx < s.size()){
            tk.nickname += s[idx];
            idx++;
        }
    }
    else{
        while(idx < s.size()){
            tk.userid += s[idx];
            idx++;
        }
        tk.nickname = "";
    }
    
    return tk;
}

vector<string> solution(vector<string> record) {
    vector<string> answer;
    unordered_map<string, string> user_info;
    
    for(int i=0; i<record.size(); ++i){
        token tk = getToken(record[i]);
        if(tk.command == "Enter")
            user_info[tk.userid] = tk.nickname;
        else if(tk.command == "Change")
            user_info[tk.userid] = tk.nickname;
        else
            continue;
    }
    
    
    for(int i=0; i<record.size(); ++i){
        string tmp;
        token tk;
        if(record[i][0] == 'E'){
            tk = getToken(record[i]);
            tmp += user_info[tk.userid];
            tmp += "님이 들어왔습니다.";
        }
        else if(record[i][0] == 'L'){
            tk = getToken(record[i]);
            tmp += user_info[tk.userid];
            tmp += "님이 나갔습니다.";
        }
        else
            continue;
        
        answer.push_back(tmp);
    }
    
    return answer;
}
