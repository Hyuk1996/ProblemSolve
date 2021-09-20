#include <string>
#include <vector>
#include <cmath>

using namespace std;

int solution(int n) {
    int answer = 0;
    
    vector<int> trit;
    int q = n;
    int r;
    while(q != 0){
        r = q % 3;
        q = q / 3;
        trit.push_back(r);
    }
    
    
    for(int i=0; i<trit.size(); ++i)
        answer += trit[trit.size() - i - 1] * pow(3, i);
    return answer;
}
