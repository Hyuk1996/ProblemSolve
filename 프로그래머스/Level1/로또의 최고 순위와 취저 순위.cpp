#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> lottos, vector<int> win_nums) {
    vector<int> answer;
    int random_count = 0;
    for(int i=0; i<lottos.size(); ++i){
        if(lottos[i] == 0){
            random_count++;
            lottos[i] = -1;
        }
    }
    
    int match_count = 0;
    for(int i=0; i<win_nums.size(); ++i){
        for(int j=0; j<lottos.size(); ++j){
            if(win_nums[i] == lottos[j]){
                match_count++;
                lottos[j] = -1;
                break;
            }
        }
    }
    
    int min_answer;
    if(match_count == 6)
        min_answer = 1;
    else if(match_count == 5)
        min_answer = 2;
    else if(match_count == 4)
        min_answer = 3;
    else if(match_count == 3)
        min_answer = 4;
    else if(match_count == 2)
        min_answer = 5;
    else
        min_answer = 6;
    
    match_count += random_count;
    int max_answer;
    if(match_count == 6)
        max_answer = 1;
    else if(match_count == 5)
        max_answer = 2;
    else if(match_count == 4)
        max_answer = 3;
    else if(match_count == 3)
        max_answer = 4;
    else if(match_count == 2)
        max_answer = 5;
    else
        max_answer = 6;
    
    answer.push_back(max_answer);
    answer.push_back(min_answer);
    return answer;
}
