#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;
void DFS(vector<vector<int>>& graph, int start, vector<bool>& visit, int& cnt){
    visit[start] = true;
    cnt++;
    for(int i=0; i<graph[start].size(); i++){
        if(!visit[graph[start][i]])
            DFS(graph, graph[start][i], visit, cnt);
    }
}
int solution(int n, vector<vector<int>> wires) {
    int answer = 987654321;
    
    for(int i=0; i<wires.size(); i++){
        vector<vector<int>> graph(n+1, vector<int>());
        
        // 주어진 간선에서 하나의 간선을 제거한 graph.
        int start_1, start_2;
        for(int j=0; j<wires.size(); j++){
            if(j == i){
                start_1 = wires[j][0];
                start_2 = wires[j][1];
                continue;
            }
            graph[wires[j][0]].push_back(wires[j][1]);
            graph[wires[j][1]].push_back(wires[j][0]);
        }
        
        // DFS로 네트워크의 송전탑 개수 확인하기.
        vector<bool> visit(n+1, 0);
        int network_1 = 0;
        DFS(graph, start_1, visit, network_1);
        
        int network_2 = 0;
        DFS(graph, start_2, visit, network_2);
        
        // 송전탑 개수 차 구하기.
        int ans = abs(network_1 - network_2);
        if(answer > ans)
            answer = ans;
    }
    return answer;
}
