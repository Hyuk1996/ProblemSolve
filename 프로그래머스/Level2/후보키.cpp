#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;
void getCombi(int idx, int candidate_size, string combi, vector<string>& combis, int column_size){
    if(combi.size() == candidate_size){
        combis.push_back(combi);
        return;
    }
    
    for(int i=idx; i<column_size; i++)
        getCombi(i + 1, candidate_size, combi + to_string(i), combis, column_size);
}
int solution(vector<vector<string>> relation) {
    int answer = 0;
    
    int candidate_size = 1;
    int column_size = relation[0].size();
    vector<string> candidates;
    while(candidate_size <= column_size){
        // 아직 candidate key가 아닌 컬럼들의 모든 조합 구하기.
        vector<string> combis;
        getCombi(0, candidate_size, "", combis, column_size);
        
        
        // 가능한 조합 중 유일성 확인하기.
       for(int i=0; i<combis.size(); i++){
           unordered_map<string, int> m;
           bool flag = true;
           for(int j=0; j<relation.size(); j++){
                string key = "";
                
               for(int k=0; k<combis[i].size(); k++)
                   key += relation[j][combis[i][k] - '0'];
               
               if(m.find(key) == m.end())
                   m[key] = 1;
               else{
                   flag = false;
                   break;
               }
           }
           
           if(flag){ // 최소성 조건 확인하기.
               bool flag_2 = true;
               for(int j=0; j<candidates.size(); j++){
                   int cnt = 0;
                   for(int k=0; k<candidates[j].size(); k++){
                       for(int z=0; z<combis[i].size(); z++){
                           if(combis[i][z] == candidates[j][k]){
                               cnt++;
                               break;
                           }
                       }
                   }
                   if(cnt == candidates[j].size()){
                       flag_2 = false;
                       break;
                   }
               }
               
               if(flag_2)
                   candidates.push_back(combis[i]);
           }
       }
        
        candidate_size++;
    }
    answer = candidates.size();
    return answer;
}
