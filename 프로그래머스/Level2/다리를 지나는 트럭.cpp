#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    
    queue<int> q;
    for(int i=0; i<bridge_length; i++)
        q.push(-1);
    
    int finished_trucks_cnt = 0;
    int cur_weight = 0;
    int cur_time = 0;
    int idx = 0;
    while(finished_trucks_cnt < truck_weights.size()){
        // 다리 끝에 도착한 트럭.
        if(q.front() > 0){
            finished_trucks_cnt++;
            cur_weight -= q.front();
        }
        q.pop();
        
        // 다리에 진입 가능.
        if(cur_weight + truck_weights[idx] <= weight){
            q.push(truck_weights[idx]);
            cur_weight += truck_weights[idx];
            idx++;
        }
        else{ // 다리에 진입 불가능.
            q.push(-1);
        }
        
        cur_time++;
    }
    answer = cur_time;
    return answer;
}
