#include<vector>
#include <queue>
#include <iostream>
using namespace std;

int solution(vector<vector<int> > maps)
{
    int answer = 0;
    
    int n = maps.size();
    int m = maps[0].size();
    
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};
    vector<vector<bool>> check(n, vector<bool>(m, 0));
    queue<pair<int, int>> q;
    
    q.push(make_pair(0, 0));
    
    // BFS 이용 최단거리 구하기.
    int distance = 1;
    while(!q.empty()){
        int q_len = q.size();
        for(int i=0; i<q_len; i++){
            int cur_x = q.front().first;
            int cur_y = q.front().second;
            q.pop();
            
            // 원하는 목적지에 도달.
            if(cur_x == m-1 && cur_y == n-1)
                return distance;
            
            for(int j=0; j<4; j++){
                int next_x = cur_x + dx[j];
                int next_y = cur_y + dy[j];
                if((0 <= next_x && next_x < m) && (0 <= next_y && next_y < n)){
                    if(maps[next_y][next_x] == 1 && check[next_y][next_x] == false){
                        check[next_y][next_x] = true;
                        q.push(make_pair(next_x, next_y));
                    }
                }
            }
        }
        distance++;
    }
    answer = -1;
    return answer;
}
