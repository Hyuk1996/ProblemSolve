#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

bool cmp(pair<string, int> a, pair<string, int> b){
    return a.second > b.second;
}
void getMenu(string &s, int idx, string menu, int cnt, map<string, int> &m){
    if(menu.size() == cnt){
        if(m.find(menu) == m.end())
            m[menu] = 1;
        else
            m[menu]++;
        return;
    }
    
    for(int i=idx; i<s.size(); ++i)
        getMenu(s, i+1, menu+s[i], cnt, m);
}

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    
    for(int i=0; i<orders.size(); ++i)
        sort(orders[i].begin(), orders[i].end());
    
    for(int i=0; i<course.size(); ++i){
        map<string, int> m;
        int cnt = course[i];
        for(int j=0; j<orders.size(); ++j)
            getMenu(orders[j], 0, "", cnt, m);
        
        vector<pair<string, int>> candidates(m.begin(), m.end());
        if(!candidates.empty()){
            sort(candidates.begin(), candidates.end(), cmp);
            
            int biggest = candidates[0].second;
            if(biggest >= 2){
                answer.push_back(candidates[0].first);
                for(int j=1; j<candidates.size(); ++j){
                    if(candidates[j].second == biggest)
                        answer.push_back(candidates[j].first);
                    else
                        break;
                }
            }
        }
    }
    sort(answer.begin(), answer.end());
    return answer;
}
