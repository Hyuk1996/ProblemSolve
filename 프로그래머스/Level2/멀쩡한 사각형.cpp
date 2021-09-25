#include <cmath>
using namespace std;

long long solution(int w,int h) {
    long long answer = 0;
    for(int i=1; i<=w; ++i){
        int except_block = ceil((long long)h * i / (double)w);
        int block = h - except_block;
        
        answer += block;
    }
    answer *= 2;
    return answer;
}
