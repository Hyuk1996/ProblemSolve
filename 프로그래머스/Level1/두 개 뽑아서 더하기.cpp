#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool result[201];
vector<int> solution(vector<int> numbers) {
    vector<int> answer;
    for(int i=0; i<numbers.size(); ++i)
        for(int j=i+1; j<numbers.size(); ++j)
            result[numbers[i] + numbers[j]] = true;
    for(int i=0; i<=200; ++i)
        if(result[i] == true)
            answer.push_back(i);
    return answer;
}
