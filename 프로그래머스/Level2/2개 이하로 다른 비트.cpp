#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<long long> solution(vector<long long> numbers) {
    vector<long long> answer;
    for(int i=0; i<numbers.size(); i++){
        if(numbers[i] % 2 == 0)
            answer.push_back(numbers[i] + 1);
        else{
            long long check = 1;
            while(true){
                if((numbers[i] & check) == 0)
                    break;
                check *= 2;
            }
            check /= 2;
            
            answer.push_back(numbers[i] + check);
        }
    }
    return answer;
}
