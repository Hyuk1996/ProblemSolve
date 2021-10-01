#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

bool solution(vector<string> phone_book) {
    bool answer = true;
    
    unordered_map<string, int> m;
    for(int i=0; i<phone_book.size(); i++)
        m[phone_book[i]] = 1;
    
    for(int i=0; i<phone_book.size(); i++){
        string tmp_s = "";
        for(int j=0; j<phone_book[i].size()-1; j++){
            tmp_s += phone_book[i][j];
            if(m.find(tmp_s) != m.end()){
                answer = false;
                break;
            }
        }
        if(!answer) break;
    }
    
    return answer;
}
