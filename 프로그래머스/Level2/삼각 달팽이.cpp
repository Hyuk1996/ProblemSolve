#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(int n) {
    vector<int> answer;
    
    // 비어 있는 삼각형 만들기.
    vector<vector<int>> triangle;
    for(int i=1; i<=n; i++){
        vector<int> v(i, -1);
        triangle.push_back(v);
    }
    
    // 반시계 방향으로 달팽이 채우기
    int cur_r = 0;
    int cur_c = 0;
    triangle[cur_r][cur_c] = 1;
    int num = 2;
    
    int dir = 0; // 0: 아래, 1: 오른쪽, 2: 왼쪽 대각선 위
    while(true){
        if(dir == 0){
            if(cur_r + 1 < triangle.size()){
                if(triangle[cur_r + 1][cur_c] == -1){
                    cur_r++;
                    triangle[cur_r][cur_c] = num;
                    num++;
                }
                else{
                    if(triangle[cur_r][cur_c + 1] != -1)
                        break;
                    else
                        dir = 1;
                }
            }
            else{
                if(cur_c + 1 < triangle[cur_r].size())
                    dir = 1;
                else
                    break;
            }
        }
        else if(dir == 1){
            if(cur_c + 1 < triangle[cur_r].size()){
                if(triangle[cur_r][cur_c + 1] == -1){
                    cur_c++;
                    triangle[cur_r][cur_c] = num;
                    num++;
                }
                else{
                    if(triangle[cur_r -1][cur_c-1] != -1)
                        break;
                    else
                        dir = 2;
                }
            }
            else{
                if(cur_r -1 >= 0 && cur_c-1 >= 0)
                    dir = 2;
                else
                    break;
            }
        }
        else{
            if(triangle[cur_r - 1][cur_c - 1] == -1){
                cur_r--;
                cur_c--;
                triangle[cur_r][cur_c] = num;
                num++;
            }
            else{
                if(cur_r + 1 < triangle.size()){
                    if(triangle[cur_r+1][cur_c] != -1)
                        break;
                    else
                        dir = 0;  
                }
                else
                    break;
            }
        }
    }
    
    
    for(int i=0; i<triangle.size(); i++){
        for(int j=0; j<triangle[i].size(); j++)
            answer.push_back(triangle[i][j]);
    }
    
    return answer;
}
