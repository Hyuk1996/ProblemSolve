#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> nums)
{
    int answer = 0;
    
    int max_ans = nums.size() / 2;
    sort(nums.begin(), nums.end());
    
    int tmp = nums[0];
    answer++;
    for(int i=1; i<nums.size(); ++i){
        if(answer >= max_ans)
            break;
        
        if(nums[i] == tmp)
            continue;
        else{
            answer++;
            tmp = nums[i];
        }
    }
    return answer;
}

// 중복 제거에서 더 좋은 풀이.
#include <vector>
#include <unordered_map>
using namespace std;

int solution(vector<int> nums)
{
    int answer = 0;
    
    unordered_map<int, int> um;
    for(int i=0; i<nums.size(); ++i)
        um[nums[i]]++;
    
    answer = min(um.size(), nums.size() / 2);
    return answer;
}
