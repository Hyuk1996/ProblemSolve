#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;
bool cmp(const pair<string, int>& a, const pair<string, int>& b){
    return a.second > b.second;
}
bool cmp2(const pair<int, int>& a, const pair<int, int>& b){
    if(a.second == b.second)
        return a.first < b.first;
    return a.second > b.second;
}
vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    
    // 장르별 재생 횟수.
    map<string, int> m;
    for(int i=0; i<genres.size(); i++){
        if(m.find(genres[i]) == m.end())
            m[genres[i]] = plays[i];
        else
            m[genres[i]] += plays[i];
    }
    
    // 많이 재생된 순서로 장르 정렬.
    vector<pair<string, int>> v(m.begin(), m.end());
    sort(v.begin(), v.end(), cmp);
    
    // 재생 목록에 추가하기.
    for(int i=0; i<v.size(); i++){
        vector<pair<int, int>> v2;
        
        for(int j=0; j<genres.size(); j++){
            if(genres[j] == v[i].first)
                v2.push_back(make_pair(j, plays[j]));
        }
        sort(v2.begin(), v2.end(), cmp2);
        
        for(int j=0; j<v2.size(); j++){
            if(j >= 2)
                break;
            answer.push_back(v2[j].first);
        }
    }
    
    return answer;
}
