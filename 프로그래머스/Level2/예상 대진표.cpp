#include <iostream>
#include <cmath>
using namespace std;

int solution(int n, int a, int b)
{
    int tmp;
    if( a > b){
        tmp = a;
        a = b;
        b = tmp;
    }
    
    int answer = 1;
    while(true){
        if( (b - a == 1) && (a % 2 == 1))
            break;
            
        
        if(a % 2 == 1)
            a++;
        a /= 2;
        
        if(b % 2 == 1)
            b++;
        b /= 2;
        
        answer++;
    }
    return answer;
}
