#include <string>
#include <vector>

using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
    int answer = 0;
    
    vector<int> total;
    total.push_back(-1);
    for(int i=1; i<=n; ++i)
        total.push_back(1);
    
    for(int i=0; i<lost.size(); ++i)
        total[lost[i]]--;
    for(int i=0; i<reserve.size(); ++i)
        total[reserve[i]]++;
    
    for(int i=1; i<=n; ++i){
        if(total[i] == 0){
            if(i != 1){
                if(total[i-1] == 2){
                    total[i-1]--;
                    total[i]++;
                    continue;
                }
            }
            
            if(i != n){
                if(total[i+1] == 2){
                    total[i+1]--;
                    total[i]++;
                    continue;
                }
            }
        }
    }
    for(int i=1; i<=n; ++i)
        if(total[i] != 0)
            answer++;
    return answer;
}
