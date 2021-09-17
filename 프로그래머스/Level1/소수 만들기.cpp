#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int num){
    bool ans = true;
    
    if(num == 1)
        ans = false;
    else{
        for(int i=2; i<=sqrt(num); ++i)
            if(num % i == 0){
                ans = false;
                break;
            }
    }
    return ans;
}

int solution(vector<int> nums) {
    int answer = 0;

    int sum;
   for(int i=0; i<(nums.size() - 2); ++i){
       for(int j=i+1; j < (nums.size() - 1); ++j){
           for(int z=j+1; z<nums.size(); ++z){
               sum = nums[i] + nums[j] + nums[z];
               if(isPrime(sum))
                    answer += 1;
           }
       }
   }

    return answer;
}
