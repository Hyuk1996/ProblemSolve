// 다시 풀어보기 ( 지금 풀이보다 더 간략하게)

#include <string>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

bool compare(const pair<int, int>& a, const pair<int, int>& b){
    if(a.second == b.second)
        return a.first < b.first;
    return a.second > b.second;
}

vector<int> solution(vector<int> answers) {
    vector<int> answer;
    
    vector<int> first_answer = {1, 2, 3, 4, 5};
    vector<int> second_answer = {2, 1, 2, 3, 2, 4, 2, 5};
    vector<int> third_answer = {3, 3, 1, 1, 2, 2, 4, 4, 5, 5};
    int first_cnt = 0;
    int second_cnt = 0;
    int third_cnt = 0;
    
    int first_idx = -1, second_idx = -1, third_idx = -1;
    for(int i=0; i<answers.size(); ++i){
        first_idx++;
        second_idx++;
        third_idx++;
        
        if(first_idx >= first_answer.size())
            first_idx = 0;
        if(answers[i] == first_answer[first_idx])
            first_cnt++;
        
        if(second_idx >= second_answer.size())
            second_idx = 0;
        if(answers[i] == second_answer[second_idx])
            second_cnt++;
        
        if(third_idx >= third_answer.size())
            third_idx = 0;
        if(answers[i] == third_answer[third_idx])
            third_cnt++;
    }
    
    vector<pair<int, int>> cnts;
    cnts.push_back(make_pair(1, first_cnt));
    cnts.push_back(make_pair(2, second_cnt));
    cnts.push_back(make_pair(3, third_cnt));
    sort(cnts.begin(), cnts.end(), compare);
    
    answer.push_back(cnts[0].first);
    for(int i=1; i<cnts.size(); ++i)
        if(cnts[0].second == cnts[i].second)
            answer.push_back(cnts[i].first);
    return answer;
}
