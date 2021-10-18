#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>

using namespace std;
bool cmp(const pair<long long, long long>& a, const pair<long long, long long>& b){
    if(a.second == b.second)
        return a.first < b.first;
    return a.second > b.second;
}
vector<string> solution(vector<vector<int>> line) {
    vector<string> answer;
    
    // 공식 이용해 교점 구하기.
    unordered_map<string, int> m;
    for(int i=0; i<line.size(); i++){
        for(int j=i+1; j<line.size(); j++){
            int x, y;
            
            long long ad = (long long)line[i][0] * (long long)line[j][1];
            long long bc = (long long)line[i][1] * (long long)line[j][0];
            long long ad_bc = ad - bc;
            if(ad_bc == 0) // 해가 없는 경우.
                continue;
            else{
                long long bf = (long long)line[i][1] * (long long)line[j][2];
                long long ed = (long long)line[i][2] * (long long)line[j][1];
                long long bf_ed = bf - ed;
                if(bf_ed % ad_bc != 0)
                    continue;
                else{
                    x = bf_ed / ad_bc;
                    long long ec = (long long)line[i][2] * (long long)line[j][0];
                    long long af = (long long)line[i][0] * (long long)line[j][2];
                    long long ec_af = ec - af;
                    if(ec_af % ad_bc != 0)
                        continue;
                    else{
                        y = ec_af / ad_bc;
                        
                        // 중복 제거를 위해 map 이용.
                        string s = to_string(x);
                        s += ',';
                        s += to_string(y);
                        if(m.find(s) == m.end())
                            m[s] = 1;
                    }
                }
            }
        }
    }
    // map -> vector
    unordered_map<string, int>::iterator it;
    vector<pair<long long, long long>> intersection;
    for(it = m.begin(); it != m.end(); it++){
        string s = it->first;
        int idx = 0;
        string x;
        while(s[idx] != ','){
            x += s[idx];
            idx++;
        }
        idx++;
        string y = s.substr(idx);
        intersection.push_back(make_pair(stol(x), stol(y)));
    }
    sort(intersection.begin(), intersection.end(), cmp);
    
    // 교점 정보 이용해서 격자판 그리기.
    long long max_y = intersection[0].second;
    long long min_y = intersection[intersection.size() - 1].second;
    long long max_x = intersection[0].first;
    long long min_x = intersection[0].first;
    for(int i=1; i < intersection.size(); i++){
        if(max_x < intersection[i].first)
            max_x = intersection[i].first;
        if(min_x > intersection[i].first)
            min_x = intersection[i].first;
    }
    
    int idx = 0;
    for(long long y = max_y; y >= min_y; y--){
        string s;
        for(long long x = min_x; x <= max_x; x++){
            if(idx < intersection.size()){
                if(intersection[idx].first == x && intersection[idx].second == y){
                    s += '*';
                    idx++;
                    continue;
                }
            }
            s += '.';
        }
        answer.push_back(s);
    }
    
    
    return answer;
}
