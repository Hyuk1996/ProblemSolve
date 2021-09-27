#include <string>
#include <vector>

using namespace std;

// 첫 번째 풀이.
vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    
    int total_finished = 0;
    int tmp_finished = 0;
    bool check[100] = {0,};
    int total_work_cnt = progresses.size();
    
    while(total_finished < total_work_cnt){
        tmp_finished = 0;
        
        for(int i=0; i<progresses.size(); ++i)    
            progresses[i] += speeds[i];
    
        for(int i=0; i<progresses.size(); ++i){
            if(progresses[i] >= 100){
                if(!check[i]){
                    if(i == 0){
                     check[i] = true;
                        tmp_finished++;
                    }
                    else{
                        if(check[i-1]){
                            check[i] = true;
                            tmp_finished++;
                        }
                    }
                }
            }
        }
    
        if(tmp_finished > 0){
            answer.push_back(tmp_finished);
            total_finished += tmp_finished;
        }
    }
    
    return answer;
}



// 두 번째 풀이.(첫 번째 보다 더 효율적)
vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    
    queue<int> work_days;
    for(int i=0; i<progresses.size(); ++i){
        int tmp = (100 - progresses[i]) % speeds[i];
        if(tmp == 0)
            work_days.push((100 - progresses[i]) / speeds[i]);
        else
            work_days.push(((100 - progresses[i]) / speeds[i]) + 1);
    }
    
    while(!work_days.empty()){
        int finished_work_cnt = 1;
        int cur = work_days.front();
        work_days.pop();
        while(!work_days.empty()){
            if(cur < work_days.front())
                break;
            finished_work_cnt++;
            work_days.pop();
        }
        answer.push_back(finished_work_cnt);
    }
    return answer;
}
               
