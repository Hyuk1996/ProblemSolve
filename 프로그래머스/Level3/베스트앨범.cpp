// map 이용한 풀이.
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

// hash 이용한 풀이.
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;
bool cmp1(const pair<string, int>& a, const pair<string, int>& b){
    return a.second > b.second;
}
bool cmp2(const pair<int, int>& a, const pair<int, int>& b){
    if(a.second == b.second)
        return a.first < b.first;
    return a.second > b.second;
}
vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    
    unordered_map<string, int> m1; // 장르별 재생 횟수.
    unordered_map<string, vector<pair<int, int>>> m2; // 장르별 노래 고유번호, 재생 횟수.
    for(int i=0; i<genres.size(); i++){
        m1[genres[i]] += plays[i];
        m2[genres[i]].push_back(make_pair(i, plays[i]));
    }
    
    vector<pair<string, int>> genres_plays(m1.begin(), m1.end());
    // 많이 재생된 장르 기준으로 정렬.
    sort(genres_plays.begin(),genres_plays.end(), cmp1);
    for(int i=0; i<genres_plays.size(); i++){
        vector<pair<int, int>> v = m2[genres_plays[i].first];
        // 장르별 재생 횟수 기준으로 정렬.
        sort(v.begin(), v.end(), cmp2);
        
        // 가장 많이 재생된 노래 정답에 삽입.
        for(int j=0; j<v.size(); j++){
            if(j >= 2)
                break;
            answer.push_back(v[j].first);
        }
    }
    
    
    return answer;
}
