#include <string>
#include <vector>

using namespace std;

int solution(int left, int right) {
    int answer = 0;
    
    int factor_cnt;
    for(int i=left; i<=right; ++i){
        factor_cnt = 0;
        for(int j=1; j<=i; ++j)
            if(i % j == 0)
                factor_cnt++;
        if(factor_cnt % 2 == 0)
            answer += i;
        else
            answer -= i;
    }
    return answer;
}
