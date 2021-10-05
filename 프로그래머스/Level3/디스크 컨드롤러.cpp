#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;
struct cmp{
  bool operator() (const pair<int, int>& a, const pair<int, int>& b){
     if(a.first == b.first)
         return a.second > b.second;
      return a.first > b.first;
  }  
};
struct cmp2{
  bool operator() (const pair<int, int>& a, const pair<int, int>& b){
      if(a.second == b.second)
          return a.first > b.first;
      return a.second > b.second;
  }  
};
int solution(vector<vector<int>> jobs) {
    int answer = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
    for(int i=0; i<jobs.size(); i++)
        pq.push(make_pair(jobs[i][0], jobs[i][1]));
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp2> pq2;
    int cur_time = 0;
    pair<int, int> tmp;
    while(true){
        // 작업 중 들어온 작업들을 작업 대기 리스트에 넣기.
        while(!pq.empty()){
            if(pq.top().first <= cur_time){
                tmp = pq.top();
                pq.pop();
                
                pq2.push(tmp);
            }
            else
                break;
        }
        
        // 작업 대기 리스트가 비어 있을 경우.
        if(pq2.empty()){
            if(!pq.empty()){
                tmp = pq.top();
                pq.pop();
                
                cur_time = tmp.first;
                pq2.push(tmp);
            }
            else
                break;
        }
        
        // 작업 대기 리스트에서 작업 선택.
        cur_time += pq2.top().second;
        answer += cur_time - pq2.top().first;
        pq2.pop();
    }
    
    answer /= jobs.size();
    return answer;
}
