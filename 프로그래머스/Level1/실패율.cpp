#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(const pair<int, float>& a, const pair<int, float>& b){
    if(a.second == b.second)
        return a.first < b.first;
    return a.second > b.second;
}

vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;
    
    vector<pair<int, float>> fail_rates;
    float pass_cnt;
    float not_pass_cnt;
    float fail_rate;
    for(int i=1; i<=N; ++i){
        pass_cnt = 0;
        not_pass_cnt = 0;
        for(int j=0; j<stages.size(); ++j){
            if(stages[j] >= i)
                pass_cnt++;
            
            if(stages[j] == i)
                not_pass_cnt++;
        }
        if(pass_cnt == 0)
            fail_rate = 0;
        else
            fail_rate = not_pass_cnt / pass_cnt;
        fail_rates.push_back(make_pair(i, fail_rate));
    }
    sort(fail_rates.begin(), fail_rates.end(), comp);
    for(int i=0; i<fail_rates.size(); ++i)
        answer.push_back(fail_rates[i].first);
    
    return answer;
}
