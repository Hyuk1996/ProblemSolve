#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> scoville, int K) {
    int answer = 0;
    
    priority_queue<int, vector<int>, greater<int> > pq (scoville.begin(), scoville.end());
    
    while(!pq.empty()){
        if(pq.top() >= K)
            break;
        else{
            if(pq.size() == 1){
                answer = -1;
                break;
            }
            else{
                int food_1 = pq.top();
                pq.pop();
                int food_2 = pq.top();
                pq.pop();
                
                int new_food = food_1 + (food_2 * 2);
                pq.push(new_food);
                answer++;
            }
        }
    }
    return answer;
}
