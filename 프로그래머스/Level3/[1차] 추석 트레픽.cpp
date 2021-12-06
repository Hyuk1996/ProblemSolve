#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

void getInfo(string& line, vector<pair<int, int>>& tasks) {
    
    // line 문자열들의 요소들을 int표현.
    int idx;
    for(idx = 0; idx<line.size(); ++idx) {
        if(line[idx] == ' ') {
            ++idx;
            break;
        }
    }
    
    int hour = stoi(line.substr(idx, 2));
    idx += 3;
    int min = stoi(line.substr(idx, 2));
    idx += 3;
    int second = stoi(line.substr(idx, 2));
    idx += 3;
    int milesecond = stoi(line.substr(idx, 3));
    idx += 4;
    
    int T = stoi(line.substr(idx, 1));
    idx += 2;
    int tmp = 0;
    for(int i = idx; i<line.size(); ++i) {
        if(line[i] == 's'){
            tmp /= 10;
            break;
        }
        tmp += (line[i] - '0');
        tmp *= 10;
    }
    T = (T * 1000) + tmp;
    
    // 시작시간, 끝나는시간 계산.
    int endTime = second + (min * 60) + (hour * 3600);
    endTime = (endTime * 1000) + milesecond;
    
    int startTime = endTime - T + 1;
    
    // tasks 배열에 저장.
    tasks.push_back(make_pair(startTime, endTime));
    return;
}
int solution(vector<string> lines) {
    
    // lines를 다루기 쉽게 변형.
    vector<pair<int, int>> tasks;
    for(int i=0; i<lines.size(); ++i) {
        // 일의 시작시간과 종료시간 구해서 tasks에 저장하기.
        getInfo(lines[i], tasks);
    }
    
    sort(tasks.begin(), tasks.end());
    
    //초당 최대 처리량 구하기.
    int answer = -1;
    priority_queue<int, vector<int>, greater<int> > pq;
    for(int i=0; i<tasks.size(); ++i) {
        int startTime = tasks[i].first;
        int endTime = tasks[i].second;
        
        // startTime 1초전에 완료되는 작업들 제거.
        while(!pq.empty()) {
            if(pq.top() <= (startTime - 1000))
                pq.pop();
            else
                break;
        }
        
        // 새로운 작업 추가.
        pq.push(endTime);
        answer = max(answer, (int)pq.size());
    }
    
    return answer;
}
