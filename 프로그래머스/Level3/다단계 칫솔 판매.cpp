#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

void calBenefit(int benefit, string seller, unordered_map<string, int>& enroll_dict, vector<string>& referral, vector<int>& answer) {
    
    int boss_benefit = benefit * 0.1;
    int my_benefit = benefit - boss_benefit;
    answer[enroll_dict[seller]] += my_benefit;
    
    if(boss_benefit > 0 && referral[enroll_dict[seller]] != "-")
        calBenefit(boss_benefit, referral[enroll_dict[seller]], enroll_dict, referral, answer);
    return;
}
vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    
    // enroll의 index 정보를 빠르게 얻기 위해, hash 이용.
    unordered_map<string, int> enroll_dict;
    for(int i=0; i<enroll.size(); ++i)
        enroll_dict[enroll[i]] = i;
    
    // 이익 계산.
    vector<int> answer(enroll.size(), 0);
    for(int i=0; i<seller.size(); ++i) {
        // 재귀함수 이용해 이익 분배.
        calBenefit(amount[i] * 100, seller[i], enroll_dict, referral, answer);
    }
    
    return answer;
}
