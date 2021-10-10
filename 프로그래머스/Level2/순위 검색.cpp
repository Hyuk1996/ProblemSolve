#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>

using namespace std;
void insertToMap(unordered_map<string, vector<int>>& m, const vector<string>& v,const int& score){
    
    for(int i=0; i<2; i++){
        string key_1;
        if(i==0) key_1 = v[0];
        else key_1 = "-";
            for(int j=0; j<2; j++){
                string key_2;
                if(j==0) key_2 = v[1];
                else key_2 = "-";
                for(int k=0; k<2; k++){
                    string key_3;
                    if(k==0) key_3 = v[2];
                    else key_3 = "-";
                    for(int z=0; z<2; z++){
                        string key_4;
                        if(z==0) key_4 = v[3];
                        else key_4 = "-";
                        m[key_1 + key_2 + key_3 + key_4].push_back(score);
                    }
                }
            }
    }
}
vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;
    
    unordered_map<string, vector<int>> m; // 조건들의 조합을 Key로 해당하는 점수들을 저장하는 hash table.
    
    for(int i=0; i<info.size(); i++){
        // string 배열을 분리하기.
        string tmp;
        vector<string> v;
        for(int j=0; j<info[i].size(); j++){
            if(info[i][j] == ' '){
                v.push_back(tmp);
                tmp.clear();
            }
            else
                tmp += info[i][j];
        }
        int score = stoi(tmp);
        
        insertToMap(m, v, score);
    }
    
    // binary search를 위해 sort
    unordered_map<string, vector<int>>::iterator it;
    for(it=m.begin(); it!=m.end(); it++)
        sort(it->second.begin(), it->second.end(), greater<int>());

    
    
    for(int i=0; i<query.size(); i++){
        string tmp;
        string key; // 찾고 싶은 지원자 자격
        for(int j=0; j<query[i].size(); j++){
            if(query[i][j] == ' '){
                if(tmp != "and")
                    key += tmp;
                tmp.clear();
            }
            else
                tmp += query[i][j];
        }
        int score = stoi(tmp);
        
        int ans = 0;
        it = m.find(key);
        if(it != m.end()){ // 자격을 만족하는 지원자가 있음.
            vector<int> scores = it->second;
            
            int left = 0;
            int right = scores.size() - 1;
            int mid;
            while(left <= right){
                mid = (right - left) / 2;
                if(scores[mid] < score)
                    right = mid - 1;
                else
                    break;
            }
            ans = mid;
            for(int j=mid; j<scores.size(); j++){
                if(scores[j] >= score){
                    ans++;
                }
                else
                    break;
            }
        }
        
        answer.push_back(ans);
    }
    
    return answer;
}
