#include <string>
#include <vector>

using namespace std;

int solution(vector<int> numbers) {
    int answer = -1;
    
    bool check[10];
    fill_n(check, 10, 1);
    
    for(int i=0; i<numbers.size(); ++i)
        check[numbers[i]] = false;
    
    answer = 0;
    for(int i=0; i<10; ++i){
        if(check[i])
            answer += i;
    }
    return answer;
}
