#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int solution(vector<int> priorities, int location) {
    int answer = 0;
    
    queue<int> q;
    for(int i=0; i<priorities.size(); i++)
        q.push(priorities[i]);
    sort(priorities.begin(), priorities.end(), greater<int>());
    
    int cnt = 1;
    while(!q.empty()){
        if(q.front() == priorities[cnt - 1]){
            if(location == 0){
                answer = cnt;
                break;
            }
            else{
                q.pop();
                cnt++;
                location--;
            }
        }
        else{
            int tmp = q.front();
            q.pop();
            q.push(tmp);
            if(location == 0) location = q.size() - 1;
            else location--;
        }
    }
    
    return answer;
}
