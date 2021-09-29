#include <string>
#include <vector>
#include <queue>

using namespace std;

bool BFS(vector<string>& matrix, int x, int y){
    bool check[5][5] = {0,};
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};
    
    int dist = 0;
    bool flag = true;
    queue<pair<int, int>> q;
    q.push(make_pair(x, y));
    check[y][x] = true;
    
    while(dist < 2 && flag){
        int len = q.size();
        for(int i=0; i<len; i++){
            int cur_x = q.front().first;
            int cur_y = q.front().second;
            q.pop();
            if(dist > 0){
                if(matrix[cur_y][cur_x] == 'P'){
                    flag = false;
                    break;
                }
            }
                
            for(int j=0; j<4; j++){
                int next_x = cur_x + dx[j];
                int next_y = cur_y + dy[j];
                if((0 <= next_x && next_x < 5) && (0 <= next_y && next_y < 5)){
                    if(!check[next_y][next_x] && matrix[next_y][next_x] != 'X'){
                        check[next_y][next_x] = true;
                        q.push(make_pair(next_x, next_y));
                    }
                }
            }
        }
        dist++;
    }
    if(flag){
        while(!q.empty()){
            int tmp_x = q.front().first;
            int tmp_y = q.front().second;
            q.pop();
            if(matrix[tmp_y][tmp_x] == 'P'){
                flag = false;
                break; 
            }
        }
    }
    return flag;
    
}

vector<int> solution(vector<vector<string>> places) {
    vector<int> answer;
    
    for(int i=0; i<places.size(); i++){
        bool flag = true;
        for(int j=0; j<places[i].size(); j++){
            if(!flag)
                break;
            for(int z=0; z<places[i][j].size(); z++){
                if(places[i][j][z] == 'P')
                    flag = BFS(places[i], z, j);
                if(!flag)
                    break;
            }
        }
        if(flag)
            answer.push_back(1);
        else
            answer.push_back(0);
    }
    return answer;
}
