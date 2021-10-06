#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

vector<int> solution(vector<string> operations) {
    vector<int> answer;
    
    priority_queue<int> max_pq;
    for(int i=0; i<operations.size(); i++){
        char cmd = operations[i][0];
        int num = stoi(operations[i].substr(2));
        
        if(cmd == 'I')
            max_pq.push(num);
        else if(cmd == 'D'){
            if(num == 1){
                if(!max_pq.empty())
                    max_pq.pop();
            }
            else{
                if(!max_pq.empty()){
                    priority_queue<int, vector<int>, greater<int> > min_pq;
                    while(!max_pq.empty()){
                        min_pq.push(max_pq.top());
                        max_pq.pop();
                    }
                    min_pq.pop();
                
                    while(!min_pq.empty()){
                        max_pq.push(min_pq.top());
                        min_pq.pop();
                    }
                }
            }
        }
    }
    
    if(max_pq.size() > 0){
        int max_value = max_pq.top();
        while(max_pq.size() > 1){
            max_pq.pop();
        }
        int min_value = max_pq.top();
        
        answer.push_back(max_value);
        answer.push_back(min_value);
    }
    else{
        answer.push_back(0);
        answer.push_back(0);
    }
    return answer;
}
