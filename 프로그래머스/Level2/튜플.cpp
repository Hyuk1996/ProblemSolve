// 첫 번째 풀이. 
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>

using namespace std;

bool cmp(pair<int, int> a, pair<int, int> b){
    return a.second < b.second;
}
vector<int> solution(string s) {
    vector<int> answer;
    
    // s를 사용하기 쉽게 변형.
    vector<vector<int>> v;
    vector<pair<int, int>> sizes;
    
    bool flag = false;
    vector<int> tmp_v;
    int tmp_size = 0;
    int tmp = 0;
    int idx = -1;
    for(int i=1; i<s.size()-1; i++){
        if(s[i] == '{'){
            tmp_v.clear();
            tmp_size = 0;
            flag = true;
            idx++;
        }
        else if(s[i] == '}'){
            tmp_v.push_back(tmp);
            tmp = 0;
            tmp_size++;
            
            v.push_back(tmp_v);
            sizes.push_back(make_pair(idx, tmp_size));
            flag = false;
        }
        else{
            if(flag){
                if('0' <= s[i] && s[i] <= '9'){
                    if(tmp == 0)
                        tmp = s[i] - '0';
                    else
                        tmp = (tmp*10) + (s[i] - '0');
                }
                else{
                    tmp_v.push_back(tmp);
                    tmp = 0;
                    tmp_size++;
                }
            }
        }
    }
    
    sort(sizes.begin(), sizes.end(), cmp);
    
    // s가 표현하는 튜플 구하기.
    unordered_map<int, int> m;
    for(int i=0; i<sizes.size(); i++){
        idx = sizes[i].first;
        
        for(int j=0; j<v[idx].size(); j++){
            if(m.find(v[idx][j]) == m.end()){
                m[v[idx][j]] = 1;
                answer.push_back(v[idx][j]);
            }
        }
    }
    
    return answer;
}
