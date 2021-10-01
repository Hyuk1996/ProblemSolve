#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool visit[501][501][4];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

int getCycleLen(vector<string>& grid, int x, int y, int dir, int len){
    if(visit[y][x][dir] == true) return len;
    
    visit[y][x][dir] = true;
    int next_dir;
    if(grid[y][x] == 'S'){
        next_dir = dir;
    }
    else if(grid[y][x] == 'L'){
        if(dir == 0) next_dir = 2;
        else if(dir == 1) next_dir = 3;
        else if(dir == 2) next_dir = 1;
        else next_dir = 0;
    }
    else{
        if(dir == 0) next_dir = 3;
        else if(dir == 1) next_dir = 2;
        else if(dir == 2) next_dir = 0;
        else next_dir = 1;
    }
    
    int next_x = x + dx[next_dir];
    int next_y = y + dy[next_dir];
    if(next_x == grid[0].size()) next_x = 0;
    if(next_x < 0) next_x = grid[0].size() - 1;
    if(next_y == grid.size()) next_y = 0;
    if(next_y < 0) next_y = grid.size() - 1;
    
    return getCycleLen(grid, next_x, next_y, next_dir, len + 1);
}
vector<int> solution(vector<string> grid) {
    vector<int> answer;
    
    for(int i=0; i<grid.size(); i++){
        for(int j=0; j<grid[i].size(); j++){
            for(int k=0; k<4; k++){
                int cycle_len = getCycleLen(grid, j, i, k, 0);
                if(cycle_len > 0) answer.push_back(cycle_len);
            }
        }
    }
    sort(answer.begin(), answer.end());
    return answer;
}
